#include "../header/cloud_socket.hpp"

#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QStringList>

#include "../header/cloud_server.hpp"
#include "../header/database_operator.hpp"

CloudSocket::CloudSocket(QObject *parent) : QTcpSocket(parent) {
  m_uploadSign = false;
  m_timer = new QTimer(this);

  /* =====  connect  ===== */

  // 收到数据 --> 解析数据
  QObject::connect(this, &CloudSocket::readyRead, this,
                   &CloudSocket::receiveMessage);
  // 客户端断开连接 --> 修改数据库登陆状态
  QObject::connect(this, &CloudSocket::disconnected, this,
                   &CloudSocket::handleOffline);
  // 定时器到点 --> 发送文件数据
  QObject::connect(m_timer, &QTimer::timeout, this,
                   &CloudSocket::downloadFileWhenTimeout);
}

CloudSocket::~CloudSocket() {}

// 用户名
const QString &CloudSocket::getUsername() const { return m_username; }

/* =====  槽函数  ===== */

// 接收消息
void CloudSocket::receiveMessage() {
  if (m_uploadSign) {
    receiveFile();
  } else {
    // LOG << bytesAvailable();
    // 数据包总长度
    unsigned int length = 0;
    // 读取数据包总长度
    read((char *)&length, sizeof(unsigned int));
    // 消息长度
    unsigned int messageLength = length - sizeof(Protocol);
    // 创建一个协议接收数据
    Protocol *protocol = createProtocol(messageLength);
    // 接收剩余数据
    read((char *)protocol + sizeof(unsigned int),
         length - sizeof(unsigned int));
    // LOG << "[port: " << peerPort() << "] >> " << protocol->type;
    // 发送转发消息信号
    QString sendMessage = QString("[port: %1]    >>>>>    ").arg(peerPort());
    sendMessage += getMessageTypeString((MESSAGE_TYPE)protocol->type);
    emit CloudServer::getInstance()->sendMessageSignal(sendMessage);
    // 根据消息类型进行处理
    switch (protocol->type) {
      case REGISTER_REQUEST:
        handleRegisterRequest(protocol);
        break;
      case LOGIN_REQUEST:
        handleLoginRequest(protocol);
        break;
      case ALL_ONLINE_USER_REQUEST:
        handleAllOnlineUsersRequest();
        break;
      case SEARCH_USER_REQUEST:
        handleSearchUserRequest(protocol);
        break;
      case ADD_FRIEND_REQUEST:
        handleAddFriendRequest(protocol);
        break;
      case ADD_FRIEND_AGREE:
        handleAgreeAddFriend(protocol);
        break;
      case ADD_FRIEND_REFUSE:
        handleRefuseAddFriend(protocol);
        break;
      case REFRESH_FRIEND_REQUEST:
        handleRefreshFriendRequest(protocol);
        break;
      case DELETE_FRIEND_REQUEST:
        handleDeleteFriendRequest(protocol);
        break;
      case PRIVATE_CHAT_REQUEST:
        handlePrivateChatRequest(protocol);
        break;
      case GROUP_CHAT_REQUEST:
        handleGroupChatRequest(protocol);
        break;
      case CREATE_DIRECTORY_REQUEST:
        handleCreateDirectoryRequest(protocol);
        break;
      case REFRESH_FILE_REQUEST:
        handleRefreshFileRequest(protocol);
        break;
      case DELETE_DIRECTORY_REQUEST:
        handleDeleteDirectoryRequest(protocol);
        break;
      case RENAME_FILE_REQUEST:
        handleRenameFileRequest(protocol);
        break;
      case ENTER_DIRECTORY_REQUEST:
        handleEnterDirectoryRequest(protocol);
        break;
      case BACK_TO_PREVIOUS_REQUEST:
        handleBackToPreviousRequest(protocol);
        break;
      case UPLOAD_FILE_REQUEST:
        handleUploadFileRequest(protocol);
        break;
      case DELETE_FILE_REQUEST:
        handleDeleteFileRequest(protocol);
        break;
      case DOWNLOAD_FILE_REQUEST:
        handleDownloadFileRequest(protocol);
        break;
      case SHARE_FILE_REQUEST:
        handleShareFileRequest(protocol);
        break;
      case SHARE_FILE_SEND_RESPONSE:
        handleShareFileSendResponse(protocol);
        break;
      case MOVE_FILE_REQUEST:
        handleMoveFileRequest(protocol);
        break;
      case LOGOUT_REQUEST:
        handleLogoutRequest(protocol);
        break;
      default:
        break;
    }
    freeProtocol(protocol);
  }
}

// 接收文件
void CloudSocket::receiveFile() {
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = UPLOAD_FILE_RESPONSE;
  QByteArray buffer = readAll();
  m_file.write(buffer);
  m_receivedSize += buffer.size();
  if (m_receivedSize == m_fileSize) {
    std::strcpy(responseProtocol->data, CODE.value(212).toStdString().c_str());
    write((char *)responseProtocol, responseProtocol->length);
    freeProtocol(responseProtocol);
    m_file.close();
    m_uploadSign = false;
  } else if (m_receivedSize > m_fileSize) {
    std::strcpy(responseProtocol->data, CODE.value(412).toStdString().c_str());
    write((char *)responseProtocol, responseProtocol->length);
    freeProtocol(responseProtocol);
    m_file.close();
    m_uploadSign = false;
  }
}

// 拷贝目录
void CloudSocket::copyDirectory(const QString &current, const QString &target) {
  QDir dir;
  dir.mkdir(target);
  dir.setPath(current);
  QFileInfoList fileInfoList = dir.entryInfoList();
  for (auto fileInfo : fileInfoList) {
    if (fileInfo.fileName() == "." || fileInfo.fileName() == "..") {
      continue;
    }
    if (fileInfo.isDir()) {
      copyDirectory(current + '/' + fileInfo.fileName(),
                    target + '/' + fileInfo.fileName());
    } else if (fileInfo.isFile()) {
      QFile::copy(current + '/' + fileInfo.fileName(),
                  target + '/' + fileInfo.fileName());
    }
  }
}

// 处理客户端下线
void CloudSocket::handleOffline() {
  DatabaseOperator::getInstance()->updateOfflineInformation(m_username);
  emit offlineSignal(m_username);
}

// 发送文件
void CloudSocket::downloadFileWhenTimeout() {
  m_timer->stop();
  const int readSize = 4096;
  char *p_buffer = new char[readSize];
  qint64 ret = 0;
  while (true) {
    std::memset(p_buffer, 0, readSize);
    ret = m_file.read(p_buffer, readSize);
    if (ret > 0 && ret <= readSize) {
      write(p_buffer, ret);
    } else if (ret == 0) {
      LOG << "send file completed !";
      break;
    } else {
      LOG << "send file to client failed !";
      break;
    }
  }
  delete[] p_buffer;
  m_file.close();
}

/* =====  private  ===== */

// 处理注册请求
void CloudSocket::handleRegisterRequest(Protocol *protocol) {
  // 用户名
  QString username(protocol->data);
  // 密码
  QString password(protocol->data + 32);
  // 响应数据包
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = REGISTER_RESPONSE;
  bool ret = DatabaseOperator::getInstance()->insertRegisterInformation(
      username, password);
  if (!ret) {
    std::strcpy(responseProtocol->data, CODE.value(401).toStdString().c_str());
  } else {
    std::strcpy(responseProtocol->data, CODE.value(201).toStdString().c_str());
    QDir dir;
    dir.mkpath("./home/" + username);
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理登陆请求
void CloudSocket::handleLoginRequest(Protocol *protocol) {
  // 用户名
  QString username(protocol->data);
  // 密码
  QString password(protocol->data + 32);
  // 响应数据包
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = LOGIN_RESPONSE;
  bool ret = DatabaseOperator::getInstance()->selectLoginInformation(username,
                                                                     password);
  if (!ret) {
    std::strcpy(responseProtocol->data, CODE.value(402).toStdString().c_str());
  } else {
    // 记录登陆用户
    m_username = username;
    m_currentDirectory = QString("home/") + username;
    std::strcpy(responseProtocol->data, CODE.value(202).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理查询所有在线用户请求
void CloudSocket::handleAllOnlineUsersRequest() {
  QStringList onlineUsers =
      DatabaseOperator::getInstance()->selectAllOnlineUsers();
  // 消息长度 = 32 * size
  Protocol *responseProtocol = createProtocol(onlineUsers.size() * 32);
  responseProtocol->type = ALL_ONLINE_USER_RESPONSE;
  for (int i{0}; i < onlineUsers.size(); i++) {
    std::strcpy(responseProtocol->message + i * 32,
                onlineUsers.at(i).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理查询用户请求
void CloudSocket::handleSearchUserRequest(Protocol *protocol) {
  QString username(protocol->data);
  // 响应数据包
  Protocol *responseProtocol = createProtocol(username.size());
  responseProtocol->type = SEARCH_USER_RESPONSE;
  std::strcpy(responseProtocol->message, username.toStdString().c_str());
  int ret = DatabaseOperator::getInstance()->selectUserStateByName(username);
  if (ret == 1) {
    std::strcpy(responseProtocol->data, CODE.value(205).toStdString().c_str());
  } else if (ret == 0) {
    std::strcpy(responseProtocol->data, CODE.value(305).toStdString().c_str());
  } else {
    std::strcpy(responseProtocol->data, CODE.value(405).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理加好友请求
void CloudSocket::handleAddFriendRequest(Protocol *protocol) {
  QString username(protocol->data);
  QString friendUsername(protocol->data + 32);
  // 响应数据包
  Protocol *responseProtocol = createProtocol(friendUsername.size());
  std::strcpy(responseProtocol->message, friendUsername.toStdString().c_str());
  responseProtocol->type = ADD_FRIEND_RESPONSE;
  // 不在线
  int ret =
      DatabaseOperator::getInstance()->selectUserStateByName(friendUsername);
  if (ret == -1) {
    std::strcpy(responseProtocol->data, CODE.value(405).toStdString().c_str());
    write((char *)responseProtocol, responseProtocol->length);
  } else if (ret == 0) {
    std::strcpy(responseProtocol->data, CODE.value(305).toStdString().c_str());
    write((char *)responseProtocol, responseProtocol->length);
  } else {
    // 已经是朋友
    if (DatabaseOperator::getInstance()->selectIsFriend(username,
                                                        friendUsername)) {
      std::strcpy(responseProtocol->data,
                  CODE.value(306).toStdString().c_str());
      write((char *)responseProtocol, responseProtocol->length);
    } else {
      CloudServer::getInstance()->sendFriendMessageToClient(friendUsername,
                                                            protocol);
    }
  }
  freeProtocol(responseProtocol);
}

// 处理同意添加好友
void CloudSocket::handleAgreeAddFriend(Protocol *protocol) {
  QString requestUsername(protocol->data);
  QString responseUsername(getUsername());
  // 插入数据
  bool ret = DatabaseOperator::getInstance()->insertFriendRecord(
      requestUsername, responseUsername);
  Protocol *responseProtocol = createProtocol(responseUsername.size());
  responseProtocol->type = ADD_FRIEND_AGREE;
  std::strcpy(responseProtocol->message,
              responseUsername.toStdString().c_str());
  if (ret) {
    std::strcpy(responseProtocol->data, CODE.value(206).toStdString().c_str());
    // write((char *)responseProtocol, responseProtocol->length);
    CloudServer::getInstance()->sendFriendMessageToClient(requestUsername,
                                                          responseProtocol);
  } else {
    std::strcpy(responseProtocol->data, CODE.value(307).toStdString().c_str());
    // write((char *)responseProtocol, responseProtocol->length);
    CloudServer::getInstance()->sendFriendMessageToClient(requestUsername,
                                                          responseProtocol);
  }
  freeProtocol(responseProtocol);
}

// 处理拒绝添加好友
void CloudSocket::handleRefuseAddFriend(Protocol *protocol) {
  QString requestUsername(protocol->data);
  QString responseUsername(getUsername());
  Protocol *responseProtocol = createProtocol(responseUsername.size());
  responseProtocol->type = ADD_FRIEND_REFUSE;
  std::strcpy(responseProtocol->message,
              responseUsername.toStdString().c_str());
  std::strcpy(responseProtocol->data, CODE.value(406).toStdString().c_str());
  // write((char *)responseProtocol, responseProtocol->length);
  CloudServer::getInstance()->sendFriendMessageToClient(requestUsername,
                                                        responseProtocol);
  freeProtocol(responseProtocol);
}

// 处理刷新好友请求
void CloudSocket::handleRefreshFriendRequest(Protocol *protocol) {
  QString username(protocol->data);
  QStringList friendList =
      DatabaseOperator::getInstance()->selectFriendList(username);
  // 数据包
  Protocol *responseProtocol = createProtocol(friendList.size() * 32);
  responseProtocol->type = REFRESH_FRIEND_RESPONSE;
  for (int i{0}; i < friendList.size(); i++) {
    std::strcpy(responseProtocol->message + i * 32,
                friendList.at(i).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理删除好友请求
void CloudSocket::handleDeleteFriendRequest(Protocol *protocol) {
  QString username(protocol->data);
  QString friendName(protocol->data + 32);
  bool ret = DatabaseOperator::getInstance()->deleteFriendRelation(username,
                                                                   friendName);
  Protocol *responseProtocol = createProtocol(friendName.size());
  responseProtocol->type = DELETE_FRIEND_RESPONSE;
  std::strcpy(responseProtocol->message, friendName.toStdString().c_str());
  if (ret) {
    std::strcpy(responseProtocol->data, CODE.value(207).toStdString().c_str());
    CloudServer::getInstance()->sendFriendMessageToClient(friendName, protocol);
  } else {
    std::strcpy(responseProtocol->data, CODE.value(407).toStdString().c_str());
  }
  freeProtocol(responseProtocol);
}

// 处理好友私聊请求
void CloudSocket::handlePrivateChatRequest(Protocol *protocol) {
  QString friendName(protocol->data + 32);
  CloudServer::getInstance()->sendFriendMessageToClient(friendName, protocol);
}

// 处理群聊请求
void CloudSocket::handleGroupChatRequest(Protocol *protocol) {
  QString username(protocol->data);
  QString message(protocol->message);
  QStringList friendList =
      DatabaseOperator::getInstance()->selectFriendList(username);
  for (auto friendName : friendList) {
    CloudServer::getInstance()->sendFriendMessageToClient(friendName, protocol);
  }
}

// 处理创建目录请求
void CloudSocket::handleCreateDirectoryRequest(Protocol *protocol) {
  QString currentDirectory(protocol->message);
  // 响应数据包
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = CREATE_DIRECTORY_RESPONSE;
  // 判断目录是否存在
  QDir dir;
  if (dir.exists(currentDirectory)) {
    QString newDirectory(protocol->data + 32);
    QString newPath = currentDirectory + '/' + newDirectory;
    if (dir.exists(newPath)) {
      // 目录已存在
      std::strcpy(responseProtocol->data,
                  CODE.value(308).toStdString().c_str());
    } else {
      // 目录不存在
      if (dir.mkdir(newPath)) {
        std::strcpy(responseProtocol->data,
                    CODE.value(208).toStdString().c_str());

      } else {
        std::strcpy(responseProtocol->data,
                    CODE.value(408).toStdString().c_str());
      }
    }
  } else {
    std::strcpy(responseProtocol->data, CODE.value(408).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理刷新文件请求
void CloudSocket::handleRefreshFileRequest(Protocol *protocol) {
  QDir dir(QString(protocol->message));
  QFileInfoList fileInfoList = dir.entryInfoList();
  // 文件信息个数
  int fileCount = fileInfoList.size() - 2;
  // 数据包
  Protocol *responseProtocol = createProtocol(fileCount * sizeof(FileInfo));
  responseProtocol->type = REFRESH_FILE_RESPONSE;
  FileInfo *p_fileInfo = nullptr;
  // 记录偏移个数
  int offestCount = 0;
  for (int i{0}; i < fileInfoList.size(); i++) {
    QString fileName = fileInfoList.at(i).fileName();
    if (fileName == "." || fileName == "..") {
      continue;
    }
    p_fileInfo = (FileInfo *)(responseProtocol->message) + (offestCount++);
    std::strcpy(p_fileInfo->name, fileName.toStdString().c_str());
    // 类型
    if (fileInfoList.at(i).isDir()) {
      p_fileInfo->type = DIRECTORY;
    } else if (fileInfoList.at(i).isFile()) {
      p_fileInfo->type = NORMAL_FILE;
    }
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理删除目录请求
void CloudSocket::handleDeleteDirectoryRequest(Protocol *protocol) {
  QString deletePath =
      QString(protocol->message) + '/' + QString(protocol->data);
  QFileInfo fileInfo(deletePath);
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = DELETE_DIRECTORY_RESPONSE;
  if (fileInfo.isDir()) {
    QDir dir;
    dir.setPath(deletePath);
    if (dir.removeRecursively()) {
      std::strcpy(responseProtocol->data,
                  CODE.value(209).toStdString().c_str());
    } else {
      std::strcpy(responseProtocol->data,
                  CODE.value(409).toStdString().c_str());
    }
  } else if (fileInfo.isFile()) {
    std::strcpy(responseProtocol->data, CODE.value(309).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理重命名请求
void CloudSocket::handleRenameFileRequest(Protocol *protocol) {
  QString oldFilePath =
      QString(protocol->message) + '/' + QString(protocol->data);
  QString newFilePath =
      QString(protocol->message) + '/' + QString(protocol->data + 32);
  QDir dir;
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = RENAME_FILE_RESPONSE;
  if (dir.rename(oldFilePath, newFilePath)) {
    std::strcpy(responseProtocol->data, CODE.value(210).toStdString().c_str());
  } else {
    std::strcpy(responseProtocol->data, CODE.value(210).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
}

// 处理进入目录请求
void CloudSocket::handleEnterDirectoryRequest(Protocol *protocol) {
  QString enterPath =
      QString(protocol->message) + '/' + QString(protocol->data);
  QFileInfo fileInfo(enterPath);
  if (fileInfo.isDir()) {
    Protocol *responseProtocol = createProtocol(enterPath.toUtf8().length());
    responseProtocol->type = ENTER_DIRECTORY_RESPONSE;
    std::strcpy(responseProtocol->data, CODE.value(211).toStdString().c_str());
    std::strcpy(responseProtocol->message, enterPath.toStdString().c_str());
    write((char *)responseProtocol, responseProtocol->length);
    freeProtocol(responseProtocol);
    m_currentDirectory = enterPath;
  } else if (fileInfo.isFile()) {
    Protocol *responseProtocol = createProtocol(0);
    responseProtocol->type = ENTER_DIRECTORY_RESPONSE;
    std::strcpy(responseProtocol->data, CODE.value(309).toStdString().c_str());
    write((char *)responseProtocol, responseProtocol->length);
    freeProtocol(responseProtocol);
  }
}

// 处理返回上一级请求
void CloudSocket::handleBackToPreviousRequest(Protocol *protocol) {
  QString currentDirectory(protocol->message);
  QDir dir(currentDirectory);
  dir.cdUp();
  currentDirectory = dir.path();
  Protocol *responseProtocol = createProtocol(currentDirectory.toUtf8().size());
  responseProtocol->type = BACK_TO_PREVIOUS_RESPONSE;
  std::strcpy(responseProtocol->message,
              currentDirectory.toStdString().c_str());
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理上传文件请求
void CloudSocket::handleUploadFileRequest(Protocol *protocol) {
  QString fileName(protocol->data);
  std::memcpy((char *)&m_fileSize, protocol->data + 32, sizeof(qint64));
  m_currentDirectory = QString(protocol->message);
  QString filePath = m_currentDirectory + '/' + fileName;
  m_file.setFileName(filePath);
  if (m_file.open(QIODevice::WriteOnly)) {
    m_uploadSign = true;
    m_receivedSize = 0;
  }
}

// 处理删除文件请求
void CloudSocket::handleDeleteFileRequest(Protocol *protocol) {
  QString deletePath =
      QString(protocol->message) + '/' + QString(protocol->data);
  QFileInfo fileInfo(deletePath);
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = DELETE_FILE_RESPONSE;
  if (fileInfo.isFile()) {
    QDir dir;
    if (dir.remove(deletePath)) {
      std::strcpy(responseProtocol->data,
                  CODE.value(213).toStdString().c_str());
    } else {
      std::strcpy(responseProtocol->data,
                  CODE.value(413).toStdString().c_str());
    }
  } else if (fileInfo.isDir()) {
    std::strcpy(responseProtocol->data, CODE.value(313).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理下载文件请求
void CloudSocket::handleDownloadFileRequest(Protocol *protocol) {
  QFileInfo fileInfo(QString(protocol->message) + '/' +
                     QString(protocol->data));
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = DOWNLOAD_FILE_RESPONSE;
  // 不是文件
  if (fileInfo.isDir()) {
    std::strcpy(responseProtocol->data, CODE.value(313).toStdString().c_str());
    write((char *)responseProtocol, responseProtocol->length);
    freeProtocol(responseProtocol);
    return;
  }
  // 如果是文件
  m_file.setFileName(QString(protocol->message) + '/' +
                     QString(protocol->data));
  if (!m_file.open(QIODevice::ReadOnly)) {
    std::strcpy(responseProtocol->data, CODE.value(310).toStdString().c_str());
    write((char *)responseProtocol, responseProtocol->length);
    freeProtocol(responseProtocol);
  } else {
    qint64 fileSize = fileInfo.size();
    std::strcpy(responseProtocol->data, protocol->data);
    std::memcpy(responseProtocol->data + 32, (char *)&fileSize, sizeof(qint64));
    write((char *)responseProtocol, responseProtocol->length);
    freeProtocol(responseProtocol);
    // 开启定时器
    m_timer->start(1000);
  }
}

// 处理分享文件请求
void CloudSocket::handleShareFileRequest(Protocol *protocol) {
  // 分享者
  QString sharerName(protocol->data);
  // 接收者个数
  int count = 0;
  std::memcpy((char *)&count, protocol->data + 32, sizeof(int));
  QString sharedFilePath(protocol->message + count * 32);
  // 响应数据包
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = SHARE_FILE_RESPONSE;
  // 检查是否为文件, 不为文件直接响应不进行转发消息
  // QFileInfo fileInfo(sharedFilePath);
  // if (!fileInfo.isFile()) {
  //   std::strcpy(responseProtocol->data,
  //   CODE.value(313).toStdString().c_str()); write((char *)responseProtocol,
  //   responseProtocol->length); freeProtocol(responseProtocol); return;
  // }
  // 转发数据包
  Protocol *resendProtocol = createProtocol(sharedFilePath.toUtf8().size());
  resendProtocol->type = SHARE_FILE_SEND_REQUEST;
  std::strcpy(resendProtocol->data, sharerName.toStdString().c_str());
  std::strcpy(resendProtocol->message, sharedFilePath.toStdString().c_str());
  for (int i{0}; i < count; i++) {
    CloudServer::getInstance()->sendFriendMessageToClient(
        QString(protocol->message + i * 32), resendProtocol);
  }
  freeProtocol(resendProtocol);
  std::strcpy(responseProtocol->data, CODE.value(214).toStdString().c_str());
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理分享文件转发响应
void CloudSocket::handleShareFileSendResponse(Protocol *protocol) {
  QString sharedPath(protocol->message);
  QString receiverName(protocol->data);
  QFileInfo fileInfo(sharedPath);
  QString receivePath =
      QString("home/") + receiverName + '/' + fileInfo.fileName();
  if (fileInfo.isFile()) {
    QFile::copy(sharedPath, receivePath);
  } else {
    copyDirectory(sharedPath, receivePath);
  }
}

// 处理移动文件请求
void CloudSocket::handleMoveFileRequest(Protocol *protocol) {
  unsigned int moveFilePathSize = 0;
  unsigned int targetDirectoryPathSize = 0;
  std::memcpy((char *)&moveFilePathSize, protocol->data, sizeof(unsigned int));
  std::memcpy((char *)&targetDirectoryPathSize, protocol->data + 32,
              sizeof(unsigned int));
  QString targetDirectoryPath(protocol->message);
  QString moveFilePath = targetDirectoryPath.left(moveFilePathSize);
  targetDirectoryPath.remove(0, moveFilePathSize);
  QFileInfo moveFileInfo(moveFilePath);
  QFileInfo targetDirectoryInfo(targetDirectoryPath);
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = MOVE_FILE_RESPONSE;
  if (moveFileInfo.isFile() && targetDirectoryInfo.isDir()) {
    bool ret = QFile::rename(
        moveFilePath, targetDirectoryPath + '/' + moveFileInfo.fileName());
    if (ret) {
      std::strcpy(responseProtocol->data,
                  CODE.value(215).toStdString().c_str());
    } else {
      std::strcpy(responseProtocol->data,
                  CODE.value(315).toStdString().c_str());
    }
  } else {
    std::strcpy(responseProtocol->data, CODE.value(415).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}

// 处理注销请求
void CloudSocket::handleLogoutRequest(Protocol *protocol) {
  QString username(protocol->data);
  QString password(protocol->data + 32);
  // 清除数据库数据
  bool ret = DatabaseOperator::getInstance()->deleteLogoutInformation(username,
                                                                      password);
  // 回应数据包
  Protocol *responseProtocol = createProtocol(0);
  responseProtocol->type = LOGOUT_RESPONSE;
  if (ret) {
    // 清空资源目录
    QDir dir;
    dir.setPath(QString("home/") + username);
    dir.removeRecursively();
    std::strcpy(responseProtocol->data, CODE.value(203).toStdString().c_str());
  } else {
    std::strcpy(responseProtocol->data, CODE.value(403).toStdString().c_str());
  }
  write((char *)responseProtocol, responseProtocol->length);
  freeProtocol(responseProtocol);
}
