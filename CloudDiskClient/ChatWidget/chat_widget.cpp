#include "chat_widget.hpp"

#include <QInputDialog>
#include <QListWidgetItem>
#include <QPushButton>
#include <QString>
#include <cstring>

#include "../header/cloud_socket.hpp"
#include "./ui_chat_widget.h"
#include "private_chat.hpp"

ChatWidget::ChatWidget(QWidget *parent) : QWidget(parent), ui(new Ui::Chat) {
  ui->setupUi(this);
  initializeChatWidget();

  /* =====  connect  ===== */
  QObject::connect(ui->showOnlineUserBtn, &QPushButton::clicked, this,
                   &ChatWidget::showOnlineUserBtnClicked);
  QObject::connect(ui->searchUserBtn, &QPushButton::clicked, this,
                   &ChatWidget::searchUserBtnClicked);
  QObject::connect(ui->refreshFriendBtn, &QPushButton::clicked, this,
                   &ChatWidget::refreshFriendBtnClicked);
  QObject::connect(ui->deleteFriendBtn, &QPushButton::clicked, this,
                   &ChatWidget::deleteFriendBtnClicked);
  QObject::connect(ui->privateChatBtn, &QPushButton::clicked, this,
                   &ChatWidget::privateChatBtnClicked);
  QObject::connect(ui->sendBtn, &QPushButton::clicked, this,
                   &ChatWidget::sendBtnClicked);
}

ChatWidget::~ChatWidget() { delete ui; }

// 初始化组件
void ChatWidget::initializeChatWidget() {
  // 显示在线用户界面
  m_online = new Online(this);
  ui->chatVerticalLayout->addWidget(m_online);
  m_online->hide();
  // 设置text edit 只读
  ui->chatTextEdit->setReadOnly(true);
}

// 解析数据显示在线用户
void ChatWidget::showOnlineUser(Protocol *protocol) {
  if (protocol == nullptr) {
    return;
  }
  int userCount = protocol->messageLength / 32;
  for (int i{0}; i < userCount; i++) {
    m_online->getOnlineUserList()->addItem(QString(protocol->message + i * 32));
  }
}

// 解析数据显示在线好友
void ChatWidget::showOnlineFriend(Protocol *protocol) {
  if (protocol == nullptr) {
    return;
  }
  ui->friendListWidget->clear();
  int friendCount = protocol->messageLength / 32;
  for (int i{0}; i < friendCount; i++) {
    ui->friendListWidget->addItem(QString(protocol->message + i * 32));
  }
}

// 更新群聊信息
void ChatWidget::updateGroupMessage(const QString &message) {
  ui->chatTextEdit->append(message);
}

// 获得在线好友列表
QStringList ChatWidget::getOnlienFriendList() {
  QStringList friendList;
  for (int i{0}; i < ui->friendListWidget->count(); i++) {
    friendList.push_back(ui->friendListWidget->item(i)->text());
  }
  return friendList;
}
/* =====  槽函数  ===== */

// 点击显示在线用户按钮
void ChatWidget::showOnlineUserBtnClicked() {
  if (m_online->isHidden()) {
    ui->chatVerticalLayout->setStretch(0, 3);
    ui->chatVerticalLayout->setStretch(1, 0);
    ui->chatVerticalLayout->setStretch(2, 2);
    // 生成数据包
    Protocol *protocol = createProtocol(0);
    protocol->type = ALL_ONLINE_USER_REQUEST;
    CloudSocket::getInstance()->write((char *)protocol, protocol->length);
    m_online->show();
    freeProtocol(protocol);
  } else {
    ui->chatVerticalLayout->setStretch(0, 0);
    ui->chatVerticalLayout->setStretch(1, 0);
    m_online->hide();
    // 清空在线用户列表
    m_online->getOnlineUserList()->clear();
  }
}

// 点击查找用户按钮
void ChatWidget::searchUserBtnClicked() {
  QString searchText = QInputDialog::getText(this, "搜索用户", "用户名");
  if (!searchText.isEmpty()) {
    Protocol *protocol = createProtocol(0);
    protocol->type = SEARCH_USER_REQUEST;
    std::strcpy(protocol->data, searchText.toStdString().c_str());
    CloudSocket::getInstance()->write((char *)protocol, protocol->length);
    freeProtocol(protocol);
  }
}

// 点击刷新好友列表按钮
void ChatWidget::refreshFriendBtnClicked() {
  QString username = CloudSocket::getInstance()->getUsername();
  Protocol *protocol = createProtocol(0);
  protocol->type = REFRESH_FRIEND_REQUEST;
  std::strcpy(protocol->data, username.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击删除好友按钮
void ChatWidget::deleteFriendBtnClicked() {
  QListWidgetItem *currentItem = ui->friendListWidget->currentItem();
  if (!currentItem) {
    return;
  }
  QString username = CloudSocket::getInstance()->getUsername();
  QString friendName = currentItem->text();
  Protocol *protocol = createProtocol(0);
  protocol->type = DELETE_FRIEND_REQUEST;
  std::strcpy(protocol->data, username.toStdString().c_str());
  std::strcpy(protocol->data + 32, friendName.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击私聊按钮
void ChatWidget::privateChatBtnClicked() {
  QListWidgetItem *currentItem = ui->friendListWidget->currentItem();
  if (!currentItem) {
    return;
  }
  PrivateChat::getInstance()->setFriendName(currentItem->text());
  PrivateChat::getInstance()->setWindowTitle(
      CloudSocket::getInstance()->getUsername() + " >> " + currentItem->text());
  if (PrivateChat::getInstance()->isHidden()) {
    PrivateChat::getInstance()->show();
  }
}

// 点击发送按钮
void ChatWidget::sendBtnClicked() {
  QString message = ui->chatLineEdit->text();
  if (message.isEmpty()) {
    return;
  }
  QString username = CloudSocket::getInstance()->getUsername();
  Protocol *protocol = createProtocol(message.toUtf8().size());
  protocol->type = GROUP_CHAT_REQUEST;
  std::strcpy(protocol->data, username.toStdString().c_str());
  std::strcpy(protocol->message, message.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
  ui->chatTextEdit->append(username + ":\n\t" + message);
  ui->chatLineEdit->clear();
}
