#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <QMap>

// 消息类型
enum MESSAGE_TYPE {
  MESSAGE_TYPE_MIN = 0,
  REGISTER_REQUEST,
  REGISTER_RESPONSE,
  LOGIN_REQUEST,
  LOGIN_RESPONSE,
  LOGOUT_REQUEST,
  LOGOUT_RESPONSE,
  ALL_ONLINE_USER_REQUEST,
  ALL_ONLINE_USER_RESPONSE,
  SEARCH_USER_REQUEST,
  SEARCH_USER_RESPONSE,
  ADD_FRIEND_REQUEST,
  ADD_FRIEND_RESPONSE,
  ADD_FRIEND_AGREE,
  ADD_FRIEND_REFUSE,
  REFRESH_FRIEND_REQUEST,
  REFRESH_FRIEND_RESPONSE,
  DELETE_FRIEND_REQUEST,
  DELETE_FRIEND_RESPONSE,
  PRIVATE_CHAT_REQUEST,
  PRIVATE_CHAT_RESPONSE,
  GROUP_CHAT_REQUEST,
  GROUP_CHAT_RESPONSE,
  CREATE_DIRECTORY_REQUEST,
  CREATE_DIRECTORY_RESPONSE,
  REFRESH_FILE_REQUEST,
  REFRESH_FILE_RESPONSE,
  DELETE_DIRECTORY_REQUEST,
  DELETE_DIRECTORY_RESPONSE,
  RENAME_FILE_REQUEST,
  RENAME_FILE_RESPONSE,
  ENTER_DIRECTORY_REQUEST,
  ENTER_DIRECTORY_RESPONSE,
  BACK_TO_PREVIOUS_REQUEST,
  BACK_TO_PREVIOUS_RESPONSE,
  UPLOAD_FILE_REQUEST,
  UPLOAD_FILE_RESPONSE,
  DELETE_FILE_REQUEST,
  DELETE_FILE_RESPONSE,
  DOWNLOAD_FILE_REQUEST,
  DOWNLOAD_FILE_RESPONSE,
  SHARE_FILE_REQUEST,
  SHARE_FILE_RESPONSE,
  SHARE_FILE_SEND_REQUEST,
  SHARE_FILE_SEND_RESPONSE,
  MOVE_FILE_REQUEST,
  MOVE_FILE_RESPONSE,
  // REQUEST,
  // RESPONSE,
  MESSAGE_TYPE_MAX = 0x00ffffff
};

// 响应代码
const QMap<int, QString> CODE{
    {201, "register succeed !"},
    {202, "login succeed !"},
    {203, "logout succeed !"},
    {204, "get all online users succeed !"},
    {205, "state: online !"},
    {206, "agree to add friend !"},
    {207, "delete friend succeed !"},
    {208, "create directory succeed !"},
    {209, "delete directory succeed !"},
    {210, "rename file succeed !"},
    {211, "enter directory succeed !"},
    {212, "upload file succeed !"},
    {213, "delete file succeed !"},
    {214, "share file completed!"},
    {215, "move file succeed !"},
    {305, "state: offline !"},
    {306, "friend existed !"},
    {307, "insert friend records failed !"},
    {308, "directory has existed !"},
    {309, "not a directory !"},
    {310, "fail to open the file !"},
    {313, "not a file !"},
    {313, "moved file has existed !"},
    {401, "register failed !"},
    {402, "login failed !"},
    {403, "logout failed !"},
    {404, "get all online users failed !"},
    {405, "not exist !"},
    {406, "refuse to add friend !"},
    {407, "delete friend failed !"},
    {408, "create directory failed !"},
    {409, "delete directory failed !"},
    {410, "rename file failed !"},
    {412, "upload file failed !"},
    {413, "delete file failed !"},
    {414, "share file failed !"},
    {415, "move file failed !"},
};

// 协议
struct Protocol {
  // 协议长度
  unsigned int length;
  // 协议类型
  unsigned int type;
  // 协议内容
  char data[64];
  // 消息长度
  unsigned int messageLength;
  // 消息
  char message[];
};

// 创建协议数据包
Protocol *createProtocol(unsigned int length);
// 释放协议数据包
void freeProtocol(Protocol *protocol);
// 协议类型信息
QString getMessageTypeString(MESSAGE_TYPE type);

// 文件信息结构体
struct FileInfo {
  char name[32];
  int type;
};

// 文件类型
enum FILE_TYPE {
  DIRECTORY,
  NORMAL_FILE,
};

#endif  // !PROTOCOL_HPP_
