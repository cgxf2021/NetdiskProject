#include "online.hpp"

#include <QListWidgetItem>
#include <QPushButton>
#include <QString>
#include <cstring>

#include "../header/cloud_socket.hpp"
#include "../header/protocol.hpp"
#include "./ui_online.h"

Online::Online(QWidget *parent) : QWidget(parent), ui(new Ui::Online) {
  ui->setupUi(this);

  /* =====  connect  ===== */
  QObject::connect(ui->addFriendBtn, &QPushButton::clicked, this,
                   &Online::addFriendBtnClicked);
}

Online::~Online() { delete ui; }

// 获得在线用户列表组件
QListWidget *Online::getOnlineUserList() { return ui->onlinePeopleListWidget; }

/* =====  槽函数  ===== */

// 点击添加好友
void Online::addFriendBtnClicked() {
  QListWidgetItem *currentItem = ui->onlinePeopleListWidget->currentItem();
  if (!currentItem) {
    return;
  }
  QString friendUsername = currentItem->text();
  if (friendUsername != CloudSocket::getInstance()->getUsername()) {
    Protocol *protocol = createProtocol(0);
    protocol->type = ADD_FRIEND_REQUEST;
    std::strcpy(
        protocol->data,
        CloudSocket::getInstance()->getUsername().toStdString().c_str());
    std::strcpy(protocol->data + 32, friendUsername.toStdString().c_str());
    CloudSocket::getInstance()->write((char *)protocol, protocol->length);
    freeProtocol(protocol);
  }
}
