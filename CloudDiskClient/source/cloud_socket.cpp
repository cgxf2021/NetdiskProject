#include "../header/cloud_socket.hpp"

CloudSocket::CloudSocket(QObject *parent) : QTcpSocket(parent) {}

CloudSocket::~CloudSocket() {}

CloudSocket *CloudSocket::getInstance() {
  static CloudSocket cloudSocket;
  return &cloudSocket;
}

// 获得用户名
const QString &CloudSocket::getUsername() const { return m_username; }

// 设置用户名
void CloudSocket::setUsername(const QString &username) {
  m_username = username;
}

// 获得当前目录
const QString &CloudSocket::getCurrentDirectory() { return m_currentDirectory; }

// 返回当前目录
void CloudSocket::setCurrentDirectory(const QString &currentDirectory) {
  m_currentDirectory = currentDirectory;
}
