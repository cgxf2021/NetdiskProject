#include "share_widget.hpp"

#include <QCheckBox>
#include <QList>
#include <QMessageBox>
#include <QVBoxLayout>

#include "../HomeWidget/home.hpp"
#include "../header/cloud_socket.hpp"
#include "../header/protocol.hpp"
#include "./ui_share_widget.h"

ShareWidget::ShareWidget(QWidget *parent) : QWidget(parent), ui(new Ui::Share) {
  ui->setupUi(this);
  m_buttonGroup = new QButtonGroup(ui->friendItemWidget);
  m_buttonGroup->setExclusive(false);

  /* =====  connect  ===== */
  QObject::connect(ui->selectAllBtn, &QPushButton::clicked, this,
                   &ShareWidget::selectAllBtnClicked);
  QObject::connect(ui->cancelSelectedBtn, &QPushButton::clicked, this,
                   &ShareWidget::cancelSelectedBtnClicked);
  QObject::connect(ui->confirmBtn, &QPushButton::clicked, this,
                   &ShareWidget::confirmBtnClicked);
  QObject::connect(ui->cancelBtn, &QPushButton::clicked, this,
                   &ShareWidget::cancelBtnClicked);
}

ShareWidget::~ShareWidget() { delete ui; }

ShareWidget *ShareWidget::getInstance() {
  static ShareWidget shareWidget;
  return &shareWidget;
}

// 更新好友列表
void ShareWidget::updateFriendItem() {
  // 移除之前的按钮选项
  QList<QAbstractButton *> preFriendCheckBtnList = m_buttonGroup->buttons();
  for (auto preFriendCheckBtn : preFriendCheckBtnList) {
    m_buttonGroup->removeButton(preFriendCheckBtn);
    preFriendCheckBtn->deleteLater();
  }
  QStringList onlineFriendList =
      Home::getInstance()->getChatWidget()->getOnlienFriendList();
  for (auto onlineFriend : onlineFriendList) {
    QCheckBox *onlineFriendCheckBtn = new QCheckBox(onlineFriend);
    ui->friendItemVerticalLayout->addWidget(onlineFriendCheckBtn);
    m_buttonGroup->addButton(onlineFriendCheckBtn);
  }
}

// 获得分享者
const QStringList &ShareWidget::getShareFriendList() const {
  return m_shareFriendList;
}

// 设置分享者
void ShareWidget::setShareFriendList(const QStringList &shareFriendList) {
  m_shareFriendList = shareFriendList;
}

// 设置分享文件名
void ShareWidget::setSharedFileName(const QString &shareFileName) {
  m_sharedFileName = shareFileName;
}
// 获得分享文件名
const QString &ShareWidget::getShareFileName() const {
  return m_sharedFileName;
}

/* =====  槽函数  ===== */

// 点击全选按钮
void ShareWidget::selectAllBtnClicked() {
  QList<QAbstractButton *> friendCheckBtnList = m_buttonGroup->buttons();
  for (auto friendCheckBtn : friendCheckBtnList) {
    if (!friendCheckBtn->isChecked()) {
      friendCheckBtn->setChecked(true);
    }
  }
}

// 点击全部取消按钮
void ShareWidget::cancelSelectedBtnClicked() {
  QList<QAbstractButton *> friendCheckBtnList = m_buttonGroup->buttons();
  for (auto friendCheckBtn : friendCheckBtnList) {
    if (friendCheckBtn->isChecked()) {
      friendCheckBtn->setChecked(false);
    }
  }
}

// 点击确定按钮
void ShareWidget::confirmBtnClicked() {
  QList<QAbstractButton *> friendCheckBtnList = m_buttonGroup->buttons();
  for (auto friendCheckBtn : friendCheckBtnList) {
    if (friendCheckBtn->isChecked()) {
      m_shareFriendList.push_back(friendCheckBtn->text());
    }
  }
  if (m_shareFriendList.isEmpty()) {
    QMessageBox::warning(this, "分享文件", "未选择分享的对象");
    return;
  }
  QString sharerName = CloudSocket::getInstance()->getUsername();
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  // 拼接路径
  QString shareFilePath = currentDirectory + '/' + m_sharedFileName;
  // 数据包长度
  int count = m_shareFriendList.size();
  unsigned int length = shareFilePath.toUtf8().size() + (count * 32);
  // 创建数据包
  Protocol *protocol = createProtocol(length);
  protocol->type = SHARE_FILE_REQUEST;
  // 分享着
  std::strcpy(protocol->data, sharerName.toStdString().c_str());
  // 被分享者个数
  std::memcpy(protocol->data + 32, (char *)&count, sizeof(int));
  // 被分享者
  for (int i{0}; i < count; i++) {
    std::strcpy(protocol->message + i * 32,
                m_shareFriendList.at(i).toStdString().c_str());
  }
  // 文件路径
  std::strcpy(protocol->message + count * 32,
              shareFilePath.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
  hide();
}

// 点击取消按钮
void ShareWidget::cancelBtnClicked() {
  hide();
}
