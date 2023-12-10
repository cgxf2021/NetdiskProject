#ifndef CLOUD_SOCKET_HPP_
#define CLOUD_SOCKET_HPP_

#include <QFile>
#include <QTcpSocket>
#include <QTimer>

#include "log.hpp"
#include "protocol.hpp"

class CloudSocket : public QTcpSocket {
  Q_OBJECT
 public:
  explicit CloudSocket(QObject *parent = nullptr);
  ~CloudSocket();
  // 用户名
  const QString &getUsername() const;

 signals:
  void offlineSignal(const QString &username);

 public slots:
  // 接收消息
  void receiveMessage();
  // 处理客户端下线
  void handleOffline();
  // 发送文件
  void downloadFileWhenTimeout();

 private:
  // 用户名
  QString m_username;
  // 当前目录
  QString m_currentDirectory;
  // 文件
  QFile m_file;
  // 上传的文件大小
  qint64 m_fileSize;
  // 已经接收的大小
  qint64 m_receivedSize;
  // 上传文件标志
  bool m_uploadSign;
  // 定时器
  QTimer *m_timer;

  // 接收文件
  void receiveFile();
  // 拷贝目录
  void copyDirectory(const QString &current, const QString &target);
  // 处理注册请求
  void handleRegisterRequest(Protocol *protocol);
  // 处理登陆请求
  void handleLoginRequest(Protocol *protocol);
  // 处理查询所有在线用户请求
  void handleAllOnlineUsersRequest();
  // 处理查询用户请求
  void handleSearchUserRequest(Protocol *protocol);
  // 处理加好友请求
  void handleAddFriendRequest(Protocol *protocol);
  // 处理同意添加好友
  void handleAgreeAddFriend(Protocol *protocol);
  // 处理拒绝添加好友
  void handleRefuseAddFriend(Protocol *protocol);
  // 处理刷新好友请求
  void handleRefreshFriendRequest(Protocol *protocol);
  // 处理删除好友请求
  void handleDeleteFriendRequest(Protocol *protocol);
  // 处理好友私聊请求
  void handlePrivateChatRequest(Protocol *protocol);
  // 处理群聊请求
  void handleGroupChatRequest(Protocol *protocol);
  // 处理创建目录请求
  void handleCreateDirectoryRequest(Protocol *protocol);
  // 处理刷新文件请求
  void handleRefreshFileRequest(Protocol *protocol);
  // 处理删除目录请求
  void handleDeleteDirectoryRequest(Protocol *protocol);
  // 处理重命名请求
  void handleRenameFileRequest(Protocol *protocol);
  // 处理进入目录请求
  void handleEnterDirectoryRequest(Protocol *protocol);
  // 处理返回上一级请求
  void handleBackToPreviousRequest(Protocol *protocol);
  // 处理上传文件请求
  void handleUploadFileRequest(Protocol *protocol);
  // 处理删除文件请求
  void handleDeleteFileRequest(Protocol *protocol);
  // 处理下载文件请求
  void handleDownloadFileRequest(Protocol *protocol);
  // 处理分享文件请求
  void handleShareFileRequest(Protocol *protocol);
  // 处理分享文件转发响应
  void handleShareFileSendResponse(Protocol *protocol);
  // 处理移动文件请求
  void handleMoveFileRequest(Protocol *protocol);
  // 处理注销请求
  void handleLogoutRequest(Protocol *protocol);
};

#endif  // !CLOUD_SOCKET_HPP_
