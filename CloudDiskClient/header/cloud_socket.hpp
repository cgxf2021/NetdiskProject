#ifndef CLOUD_SOCKET_HPP_
#define CLOUD_SOCKET_HPP_

#include <QTcpSocket>

class CloudSocket : public QTcpSocket {
  Q_OBJECT
 public:
  static CloudSocket *getInstance();
  // 获得用户名
  const QString &getUsername() const;
  // 设置用户名
  void setUsername(const QString &username);
  // 获得当前目录
  const QString &getCurrentDirectory();
  // 返回当前目录
  void setCurrentDirectory(const QString &currentDirectory);

 private:
  CloudSocket(QObject *parent = nullptr);
  ~CloudSocket();
  CloudSocket(const CloudSocket &) = delete;
  CloudSocket &operator=(const CloudSocket &) = delete;

  // 用户名
  QString m_username;
  // 当前路径
  QString m_currentDirectory;
};

#endif  // !CLOUD_SOCKET_HPP_
