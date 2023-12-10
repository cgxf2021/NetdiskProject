#include "widget.h"

#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <cstring>

#include "./ui_widget.h"
#include "ChatWidget/private_chat.hpp"
#include "HomeWidget/home.hpp"
#include "header/protocol.hpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  loadConfig();
  initializeSocket();
  initializeWidget();

  /* =====  connect  ===== */
}

Widget::~Widget() { delete ui; }

// 加载配置文件
void Widget::loadConfig() {
  QFile configFile(":/config/config.cfg");
  if (configFile.open(QIODevice::ReadOnly)) {
    QString config = QString(configFile.readAll());
    LOG << config;
    QRegularExpression re("ip: (.*?)\nport: (.*?)\n");
    QRegularExpressionMatch match = re.match(config);
    m_serverIP = match.captured(1);
    m_serverPort = match.captured(2).toShort();
    LOG << m_serverIP;
    LOG << m_serverPort;
  }
}

// 初始化界面
void Widget::initializeWidget() {
  setWindowTitle("客户端");
  setFixedSize(300, 150);
  // 设置lineEdit最大输入长度
  ui->userLineEdit->setMaxLength(16);
  ui->passwordLineEdit->setMaxLength(16);
}

// 初始化Socket
void Widget::initializeSocket() {
  m_socket = CloudSocket::getInstance();
  m_socket->connectToHost(m_serverIP, m_serverPort);

  // 连接服务器成功 --> 弹出消息框
  QObject::connect(m_socket, &QTcpSocket::connected, this,
                   &Widget::connectSuccessed);
  // 连接服务器失败 --> 弹出消息框
  // QObject::connect(m_socket, &QTcpSocket::errorOccurred, this,
  //                  [this](QAbstractSocket::SocketError socketError) -> void {
  //                    QMessageBox::warning(this, "连接服务器", "连接失败");
  //                  });
}

// 处理注册响应
void Widget::handleRegisterResponse(Protocol *protocol) {
  if (QString(protocol->data) == CODE.value(201)) {
    QMessageBox::information(this, "注册", CODE.value(201));
  } else {
    QMessageBox::warning(this, "注册", CODE.value(401));
  }
}

// 处理登陆响应
void Widget::handleLoginResponse(Protocol *protocol) {
  if (QString(protocol->data) == CODE.value(202)) {
    // QMessageBox::information(this, "登陆", CODE.value(202));
    // 设置用户名
    CloudSocket::getInstance()->setUsername(ui->userLineEdit->text());
    // 设置文件目录
    CloudSocket::getInstance()->setCurrentDirectory("home/" +
                                                    ui->userLineEdit->text());
    Home::getInstance()->show();
    Home::getInstance()->setHomeTitle(ui->userLineEdit->text());
    this->hide();
  } else {
    QMessageBox::warning(this, "登陆", CODE.value(402));
  }
  ui->userLineEdit->setReadOnly(false);
  ui->passwordLineEdit->setReadOnly(false);
}

// 处理注销响应
void Widget::handleLogoutResponse(Protocol *protocol) {
  if (QString(protocol->data) == CODE.value(203)) {
    QMessageBox::information(this, "注销", CODE.value(203));
  } else {
    QMessageBox::warning(this, "注销", CODE.value(403));
  }
  ui->userLineEdit->setReadOnly(false);
  ui->passwordLineEdit->setReadOnly(false);
  ui->loginBtn->setEnabled(true);
}

// 处理显示在线用户响应
void Widget::handleShowOnlineUsersResponse(Protocol *protocol) {
  Home::getInstance()->getChatWidget()->showOnlineUser(protocol);
}

// 处理搜索用户响应
void Widget::handleSearchUserResponse(Protocol *protocol) {
  QString showText = QString(protocol->message) + ' ' + QString(protocol->data);
  QMessageBox::information(this, "查询", showText);
}

// 处理添加好友响应
void Widget::handleAddFriendResponse(Protocol *protocol) {
  QString showText = QString(protocol->message) + ' ' + QString(protocol->data);
  QMessageBox::information(this, "添加好友", showText);
}

// 处理添加好友请求
void Widget::handleAddFriendRequest(Protocol *protocol) {
  QString username(protocol->data);
  QString showText = username + "请求添加好友";
  QMessageBox::StandardButton choose = QMessageBox::information(
      this, "添加好友", showText, QMessageBox::Yes, QMessageBox::No);
  // 创建协议数据包
  Protocol *responseProtocol = createProtocol(0);
  std::strcpy(responseProtocol->data, username.toStdString().c_str());
  if (choose == QMessageBox::Yes) {
    responseProtocol->type = ADD_FRIEND_AGREE;
  } else {
    responseProtocol->type = ADD_FRIEND_REFUSE;
  }
  CloudSocket::getInstance()->write((char *)responseProtocol,
                                    responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理添加好友同意响应
void Widget::handleAddFriendAgree(Protocol *protocol) {
  QString showText = QString(protocol->message) + ' ' + QString(protocol->data);
  QMessageBox::information(this, "添加好友", showText);
}

// 处理添加好友拒绝响应
void Widget::handleAddFriendRefuse(Protocol *protocol) {
  QString showText = QString(protocol->message) + ' ' + QString(protocol->data);
  QMessageBox::information(this, "添加好友", showText);
}

// 处理刷新好友列表响应
void Widget::handleRefreshFriendResponse(Protocol *protocol) {
  Home::getInstance()->getChatWidget()->showOnlineFriend(protocol);
}

// 处理删除好友响应
void Widget::handleDeleteFriendResponse(Protocol *protocol) {
  QString showText(protocol->data);
  if (showText == CODE.value(207)) {
    showText += " >> " + QString(protocol->message) + " has deleted !";
  }
  QMessageBox::information(this, "删除好友", showText);
}

// 处理删除好友请求
void Widget::handleDeleteFriendRequest(Protocol *protocol) {
  QString username(protocol->data);
  QString friendName(protocol->data + 32);
  QMessageBox::information(
      this, "删除好友", username + " has deleted you (" + friendName + ") !");
}

// 处理私聊请求
void Widget::handlePrivateChatRequest(Protocol *protocol) {
  QString username(protocol->data);
  QString friendName(protocol->data + 32);
  if (PrivateChat::getInstance()->isHidden()) {
    PrivateChat::getInstance()->setFriendName(username);
    PrivateChat::getInstance()->setWindowTitle(friendName + " >> " + username);
    PrivateChat::getInstance()->show();
  }
  QString message = username + ":\n\t" + QString(protocol->message);
  PrivateChat::getInstance()->updateMessage(message);
}

// 处理群聊请求
void Widget::handleGroupChatRequest(Protocol *protocol) {
  QString username(protocol->data);
  QString message = username + ":\n\t" + QString(protocol->message);
  Home::getInstance()->getChatWidget()->updateGroupMessage(message);
}

// 处理创建目录响应
void Widget::handleCreateDirectoryResponse(Protocol *protocol) {
  QString showText(protocol->data);
  QMessageBox::information(this, "创建目录", showText);
}

// 处理刷新文件响应
void Widget::handleRefreshFileResponse(Protocol *protocol) {
  Home::getInstance()->getBookWidget()->updateFileListData(protocol);
}

// 处理删除目录响应
void Widget::handleDeleteDirectoryResponse(Protocol *protocol) {
  QString showText(protocol->data);
  QMessageBox::information(this, "删除目录", showText);
  // 刷新列表
  Home::getInstance()->getBookWidget()->getRefreshFileBtn()->click();
}

// 处理重命名响应
void Widget::handleRenameFileResponse(Protocol *protocol) {
  QString showText(protocol->data);
  QMessageBox::information(this, "重命名文件", showText);
  // 刷新列表
  Home::getInstance()->getBookWidget()->getRefreshFileBtn()->click();
}

// 处理进入目录响应
void Widget::handleEnterDirectoryResponse(Protocol *protocol) {
  QString showText(protocol->data);
  if (showText == CODE.value(211)) {
    CloudSocket::getInstance()->setCurrentDirectory(QString(protocol->message));
    // 刷新列表
    Home::getInstance()->getBookWidget()->getRefreshFileBtn()->click();
  } else if (showText == CODE.value(309)) {
    QMessageBox::warning(this, "进入目录", showText);
  }
}

// 处理返回上一级响应
void Widget::handleBackToPreviousResponse(Protocol *protocol) {
  CloudSocket::getInstance()->setCurrentDirectory(QString(protocol->message));
  Home::getInstance()->getBookWidget()->getRefreshFileBtn()->click();
}

// 处理上传文件响应
void Widget::handleUploadFileResponse(Protocol *protocol) {
  QString showText(protocol->data);
  QMessageBox::information(this, "上传文件", showText);
  Home::getInstance()->getBookWidget()->getRefreshFileBtn()->click();
}

// 处理删除文件响应
void Widget::handleDeleteFileResponse(Protocol *protocol) {
  QString showText(protocol->data);
  QMessageBox::information(this, "删除文件", showText);
  Home::getInstance()->getBookWidget()->getRefreshFileBtn()->click();
}

// 处理下载文件响应
void Widget::handleDownloadFileResponse(Protocol *protocol) {
  if (QString(protocol->data) == CODE.value(310)) {
    QMessageBox::warning(this, "下载文件", CODE.value(310));
  } else if (QString(protocol->data) == CODE.value(313)) {
    QMessageBox::warning(this, "下载文件", CODE.value(313));
  } else {
    QString fileName(protocol->data);
    qint64 fileSize = 0;
    std::memcpy((char *)&fileSize, protocol->data + 32, sizeof(qint64));
    Home::getInstance()->getBookWidget()->setDownloadSign(true);
    Home::getInstance()->getBookWidget()->setFileSize(fileSize);
    Home::getInstance()->getBookWidget()->setReceiveSize(0);
    Home::getInstance()->getBookWidget()->openDownloadFile();
  }
}

// 处理分享文件响应
void Widget::handleShareFileResponse(Protocol *protocol) {
  QString showText(protocol->data);
  if (showText == CODE.value(313)) {
    QMessageBox::warning(this, "分享文件", showText);
  } else if (showText == CODE.value(214)) {
    QMessageBox::information(this, "分享文件", showText);
  }
}

// 处理接收分享文件请求
void Widget::handleShareFileSendRequest(Protocol *protocol) {
  QString fileName = *(QString(protocol->message).split('/').end() - 1);
  QString sharerName(protocol->data);
  QMessageBox::StandardButton button = QMessageBox::question(
      this, "分享文件", sharerName + QString(" 向您共享文件/目录 ") + fileName);
  if (button == QMessageBox::StandardButton::Yes) {
    Protocol *responseProtocol = createProtocol(protocol->messageLength);
    responseProtocol->type = SHARE_FILE_SEND_RESPONSE;
    std::strcpy(
        responseProtocol->data,
        CloudSocket::getInstance()->getUsername().toStdString().c_str());
    std::strcpy(responseProtocol->message, protocol->message);
    CloudSocket::getInstance()->write((char *)responseProtocol,
                                      responseProtocol->length);
    freeProtocol(responseProtocol);
  }
}

// 处理移动文件响应
void Widget::handleMoveFileResponse(Protocol *protocol) {
  QString showText(protocol->data);
  if (showText == CODE.value(215)) {
    QMessageBox::information(this, "移动文件", showText);
  } else {
    QMessageBox::warning(this, "移动文件", showText);
  }
}

/* =====  槽函数  ===== */

// 连接服务器成功
void Widget::connectSuccessed() {
  QMessageBox::information(this, "连接服务器", "连接成功");
  // 点击发送按钮 --> 发送消息
  // QObject::connect(ui->sendBtn, &QPushButton::clicked, this,
  // &Widget::sendBtnClicked);
  // 点击注册 --> 发送注册数据
  QObject::connect(ui->registerBtn, &QPushButton::clicked, this,
                   &Widget::registerBtnClicked);
  // 点击登陆 --> 发送登陆信息
  QObject::connect(ui->loginBtn, &QPushButton::clicked, this,
                   &Widget::loginBtnClicked);
  // 点击注销 --> 发送注销信息
  QObject::connect(ui->logoutBtn, &QPushButton::clicked, this,
                   &Widget::logoutBtnClicked);
  // 收到服务器消息 --> 接收消息
  QObject::connect(m_socket, &QTcpSocket::readyRead, this,
                   &Widget::receiveMessage);
}

// 客户端接收服务器数据
void Widget::receiveMessage() {
  if (Home::getInstance()->getBookWidget()->getDownloadSign()) {
    Home::getInstance()->getBookWidget()->saveFileFromDisk();
  } else {
    // LOG << m_socket->bytesAvailable();
    // 数据包总长度
    unsigned int length = 0;
    m_socket->read((char *)&length, sizeof(unsigned int));
    // 消息长度
    unsigned int messageLength = length - sizeof(Protocol);
    // 创建一个协议接收数据
    Protocol *protocol = createProtocol(messageLength);
    // 接收剩余数据
    m_socket->read((char *)protocol + sizeof(unsigned int),
                   length - sizeof(unsigned int));
    switch (protocol->type) {
      case REGISTER_RESPONSE:
        handleRegisterResponse(protocol);
        break;
      case LOGIN_RESPONSE:
        handleLoginResponse(protocol);
        break;
      case LOGOUT_RESPONSE:
        handleLogoutResponse(protocol);
        break;
      case ALL_ONLINE_USER_RESPONSE:
        handleShowOnlineUsersResponse(protocol);
        break;
      case SEARCH_USER_RESPONSE:
        handleSearchUserResponse(protocol);
        break;
      case ADD_FRIEND_REQUEST:
        handleAddFriendRequest(protocol);
        break;
      case ADD_FRIEND_RESPONSE:
        handleAddFriendResponse(protocol);
        break;
      case ADD_FRIEND_AGREE:
        handleAddFriendAgree(protocol);
        break;
      case ADD_FRIEND_REFUSE:
        handleAddFriendRefuse(protocol);
        break;
      case REFRESH_FRIEND_RESPONSE:
        handleRefreshFriendResponse(protocol);
        break;
      case DELETE_FRIEND_REQUEST:
        handleDeleteFriendRequest(protocol);
        break;
      case DELETE_FRIEND_RESPONSE:
        handleDeleteFriendResponse(protocol);
        break;
      case PRIVATE_CHAT_REQUEST:
        handlePrivateChatRequest(protocol);
        break;
      case GROUP_CHAT_REQUEST:
        handleGroupChatRequest(protocol);
        break;
      case CREATE_DIRECTORY_RESPONSE:
        handleCreateDirectoryResponse(protocol);
        break;
      case REFRESH_FILE_RESPONSE:
        handleRefreshFileResponse(protocol);
        break;
      case DELETE_DIRECTORY_RESPONSE:
        handleDeleteDirectoryResponse(protocol);
        break;
      case RENAME_FILE_RESPONSE:
        handleRenameFileResponse(protocol);
        break;
      case ENTER_DIRECTORY_RESPONSE:
        handleEnterDirectoryResponse(protocol);
        break;
      case BACK_TO_PREVIOUS_RESPONSE:
        handleBackToPreviousResponse(protocol);
        break;
      case UPLOAD_FILE_RESPONSE:
        handleUploadFileResponse(protocol);
        break;
      case DELETE_FILE_RESPONSE:
        handleDeleteFileResponse(protocol);
        break;
      case DOWNLOAD_FILE_RESPONSE:
        handleDownloadFileResponse(protocol);
        break;
      case SHARE_FILE_RESPONSE:
        handleShareFileResponse(protocol);
        break;
      case SHARE_FILE_SEND_REQUEST:
        handleShareFileSendRequest(protocol);
        break;
      case MOVE_FILE_RESPONSE:
        handleMoveFileResponse(protocol);
        break;
      default:
        break;
    }
    freeProtocol(protocol);
  }
}

// 点击注册按钮
void Widget::registerBtnClicked() {
  QString username = ui->userLineEdit->text();
  QString password = ui->passwordLineEdit->text();
  if (username.isEmpty() || password.isEmpty()) {
    QMessageBox::information(this, "注册", "用户名或密码不能为空");
  } else {
    Protocol *protocol = createProtocol(0);
    protocol->type = REGISTER_REQUEST;
    // 将用户名密码存入data
    std::memcpy(protocol->data, username.toStdString().c_str(), 32);
    std::memcpy(protocol->data + 32, password.toStdString().c_str(), 32);
    // 发送数据
    m_socket->write((char *)protocol, protocol->length);
    freeProtocol(protocol);
  }
}

// 点击登陆按钮
void Widget::loginBtnClicked() {
  QString username = ui->userLineEdit->text();
  QString password = ui->passwordLineEdit->text();
  if (username.isEmpty() || password.isEmpty()) {
    QMessageBox::information(this, "登陆", "用户名或密码不能为空");
  } else {
    Protocol *protocol = createProtocol(0);
    protocol->type = LOGIN_REQUEST;
    // 将用户名密码存入data
    std::memcpy(protocol->data, username.toStdString().c_str(), 32);
    std::memcpy(protocol->data + 32, password.toStdString().c_str(), 32);
    // 发送数据
    m_socket->write((char *)protocol, protocol->length);
    freeProtocol(protocol);
    // 防止用户修改用户名密码
    ui->userLineEdit->setReadOnly(true);
    ui->passwordLineEdit->setReadOnly(true);
  }
}

// 点击注销按钮
void Widget::logoutBtnClicked() {
  QString username = ui->userLineEdit->text();
  QString password = ui->passwordLineEdit->text();
  if (username.isEmpty() || password.isEmpty()) {
    QMessageBox::information(this, "注销", "用户名或密码不能为空");
  } else {
    Protocol *protocol = createProtocol(0);
    protocol->type = LOGOUT_REQUEST;
    // 将用户名密码存入data
    std::memcpy(protocol->data, username.toStdString().c_str(), 32);
    std::memcpy(protocol->data + 32, password.toStdString().c_str(), 32);
    // 发送数据
    m_socket->write((char *)protocol, protocol->length);
    freeProtocol(protocol);
    // 防止用户修改用户名密码
    ui->userLineEdit->setReadOnly(true);
    ui->passwordLineEdit->setReadOnly(true);
    // 禁止用户登陆
    ui->loginBtn->setEnabled(false);
  }
}

// 点击发送按钮
/*
void Widget::sendBtnClicked() {
  QString message = ui->messageLineEdit->text();
  if (!message.isEmpty()) {
    Protocol *protocol = createProtocol(message.size());
    std::memcpy(protocol->message, message.toStdString().c_str(),
message.size()); LOG << protocol->message; m_socket->write((char *)protocol,
protocol->length); freeProtocol(protocol); } else {
  QMessageBox::information(this, "提示", "消息不能为空");
  }
}
*/
