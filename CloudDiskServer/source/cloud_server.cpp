#include "../header/cloud_server.hpp"

CloudServer::CloudServer(QObject *parent) : QTcpServer(parent) {}

CloudServer::~CloudServer() {
  // 服务器关闭时销毁socket对象
  // for (auto cloudSocket : m_cloudSocketList) {
  //   delete cloudSocket;
  // }
}

CloudServer *CloudServer::getInstance() {
  static CloudServer cloudServe;
  return &cloudServe;
}

// 转发添加好友请求给客户端
void CloudServer::sendFriendMessageToClient(const QString &username,
                                            Protocol *protocol) {
  if (username.isEmpty() || protocol == nullptr) {
    return;
  }
  for (auto socket : m_cloudSocketList) {
    if (socket->getUsername() == username) {
      socket->write((char *)protocol, protocol->length);
      break;
    }
  }
}

/* =====  槽函数  ===== */

// 用户下线删除socket
void CloudServer::deleteOfflineSocket(const QString &username) {
  LOG << m_cloudSocketList.size();
  for (auto it = m_cloudSocketList.begin(); it != m_cloudSocketList.end();
       it++) {
    if ((*it)->getUsername() == username) {
      // emit sendMessageSignal(username + " has offline !");
      (*it)->deleteLater();
      m_cloudSocketList.erase(it);
      break;
    }
  }
  LOG << m_cloudSocketList.size();
}

/* =====  重写  ===== */

// 重写与客户端建立连接时的操作
void CloudServer::incomingConnection(qintptr socketDescriptor) {
  CloudSocket *cloudSocket = new CloudSocket();
  cloudSocket->setSocketDescriptor(socketDescriptor);
  // 将通信socket添加到列表
  m_cloudSocketList.push_back(cloudSocket);

  QObject::connect(cloudSocket, &CloudSocket::offlineSignal, this,
                   &CloudServer::deleteOfflineSocket);
}
