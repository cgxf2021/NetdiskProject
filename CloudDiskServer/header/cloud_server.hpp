#ifndef CLOUD_SERVER_HPP_
#define CLOUD_SERVER_HPP_

#include <QList>
#include <QTcpServer>

#include "cloud_socket.hpp"
#include "protocol.hpp"

class CloudServer : public QTcpServer {
  Q_OBJECT
 private:
  explicit CloudServer(QObject *parent = nullptr);
  ~CloudServer();
  CloudServer(const CloudServer &) = delete;
  CloudServer &operator=(const CloudServer &) = delete;

  // 参与通信的socket
  QList<CloudSocket *> m_cloudSocketList;

 signals:
  void sendMessageSignal(const QString &message);

 private slots:
  // 用户下线删除socket
  void deleteOfflineSocket(const QString &username);

 protected:
  // 重写与客户端建立连接时的操作
  void incomingConnection(qintptr socketDescriptor) override;

 public:
  static CloudServer *getInstance();
  // 转发添加好友请求给客户端
  void sendFriendMessageToClient(const QString &username, Protocol *protocol);
};

#endif  // !CLOUD_SERVE_HPP_
