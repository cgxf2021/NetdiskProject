#include "private_chat.hpp"

#include "../header/cloud_socket.hpp"
#include "../header/protocol.hpp"
#include "./ui_private_chat.h"

PrivateChat::PrivateChat(QWidget *parent)
    : QWidget(parent), ui(new Ui::PrivateChat) {
  ui->setupUi(this);
  // 设置text readonly
  ui->chatTextEdit->setReadOnly(true);
  // window size
  setFixedSize(500, 350);

  /* =====  connect  ===== */
  QObject::connect(ui->sendBtn, &QPushButton::clicked, this,
                   &PrivateChat::sendBtnClicked);
}

PrivateChat::~PrivateChat() { delete ui; }

PrivateChat *PrivateChat::getInstance() {
  static PrivateChat privateChat;
  return &privateChat;
}

// 获得朋友名字
const QString &PrivateChat::getFriendName() const { return m_friendName; }

// 设置朋友名字
void PrivateChat::setFriendName(const QString &friendName) {
  m_friendName = friendName;
}

// 更新消息
void PrivateChat::updateMessage(const QString &message) {
  ui->chatTextEdit->append(message);
}

// 设置windows title
void PrivateChat::setPrivateChatWindowTitle(const QString &title) {
  setWindowTitle(title);
}

/* =====  槽函数  ===== */

// 点击发送按钮
void PrivateChat::sendBtnClicked() {
  // 用户名
  QString username = CloudSocket::getInstance()->getUsername();
  // 获取输入数据
  QString message = ui->sendLineEdit->text();
  if (!message.isEmpty()) {
    Protocol *protocol = createProtocol(message.toUtf8().size());
    protocol->type = PRIVATE_CHAT_REQUEST;
    std::strcpy(protocol->data, username.toStdString().c_str());
    std::strcpy(protocol->data + 32, m_friendName.toStdString().c_str());
    std::strcpy(protocol->message, message.toStdString().c_str());
    CloudSocket::getInstance()->write((char *)protocol, protocol->length);
    freeProtocol(protocol);
    ui->chatTextEdit->append(username + ":\n\t" + message);
    ui->sendLineEdit->clear();
  }
}
