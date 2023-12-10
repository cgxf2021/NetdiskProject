#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "./header/log.hpp"
#include "./header/protocol.hpp"
#include "./header/cloud_socket.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private:
  Ui::Widget *ui;
  // 服务器ip
  QString m_serverIP;
  // 服务器端口
  qint16 m_serverPort;
  // socket
  CloudSocket *m_socket;

  // 加载配置文件
  void loadConfig();
  // 初始化Socket
  void initializeSocket();
  // 初始化界面
  void initializeWidget();
  // 保存文件函数
  void saveFileFromDisk();

  // 处理注册响应
  void handleRegisterResponse(Protocol *protocol);
  // 处理登陆响应
  void handleLoginResponse(Protocol *protocol);
  // 处理注销响应
  void handleLogoutResponse(Protocol *protocol);
  // 处理显示在线用户响应
  void handleShowOnlineUsersResponse(Protocol *protocol);
  // 处理搜索用户响应
  void handleSearchUserResponse(Protocol *protocol);
  // 处理添加好友响应
  void handleAddFriendResponse(Protocol *protocol);
  // 处理添加好友请求
  void handleAddFriendRequest(Protocol *protocol);
  // 处理添加好友同意响应
  void handleAddFriendAgree(Protocol *protocol);
  // 处理添加好友拒绝响应
  void handleAddFriendRefuse(Protocol *protocol);
  // 处理刷新好友列表响应
  void handleRefreshFriendResponse(Protocol *protocol);
  // 处理删除好友响应
  void handleDeleteFriendResponse(Protocol *protocol);
  // 处理删除好友请求
  void handleDeleteFriendRequest(Protocol *protocol);
  // 处理私聊请求
  void handlePrivateChatRequest(Protocol *protocol);
  // 处理群聊请求
  void handleGroupChatRequest(Protocol *protocol);
  // 处理创建目录响应
  void handleCreateDirectoryResponse(Protocol *protocol);
  // 处理刷新文件响应
  void handleRefreshFileResponse(Protocol *protocol);
  // 处理删除目录响应
  void handleDeleteDirectoryResponse(Protocol *protocol);
  // 处理重命名响应
  void handleRenameFileResponse(Protocol *protocol);
  // 处理进入目录响应
  void handleEnterDirectoryResponse(Protocol *protocol);
  // 处理返回上一级响应
  void handleBackToPreviousResponse(Protocol *protocol);
  // 处理上传文件响应
  void handleUploadFileResponse(Protocol *protocol);
  // 处理删除文件响应
  void handleDeleteFileResponse(Protocol *protocol);
  // 处理下载文件响应
  void handleDownloadFileResponse(Protocol *protocol);
  // 处理分享文件响应
  void handleShareFileResponse(Protocol *protocol);
  // 处理接收分享文件请求
  void handleShareFileSendRequest(Protocol *protocol);
  // 处理移动文件响应
  void handleMoveFileResponse(Protocol *protocol);

 private slots:
  // 点击发送按钮
  // void sendBtnClicked();
  // 连接服务器成功
  void connectSuccessed();
  // 客户端接收服务器数据
  void receiveMessage();
  // 点击登陆按钮
  void loginBtnClicked();
  // 点击注册按钮
  void registerBtnClicked();
  // 点击注销按钮
  void logoutBtnClicked();
};

#endif  // WIDGET_H
