#include "../header/protocol.hpp"

#include <cstdlib>
#include <cstring>

// 创建协议数据包
Protocol *createProtocol(unsigned int messageLength) {
  Protocol *protocol =
      (Protocol *)std::malloc(sizeof(Protocol) + messageLength + 1);
  if (!protocol) {
    exit(EXIT_FAILURE);
  }
  std::memset(protocol->data, 0, sizeof(protocol->data));
  std::memset(protocol->message, 0, messageLength + 1);
  protocol->length = sizeof(Protocol) + messageLength + 1;
  protocol->messageLength = messageLength;

  return protocol;
}

// 释放协议数据包
void freeProtocol(Protocol *protocol) {
  if (protocol == nullptr) {
    return;
  }
  free(protocol);
  protocol = nullptr;
}

// 协议类型信息
QString getMessageTypeString(MESSAGE_TYPE type) {
  QString messageTypeString;
  switch (type) {
    case REGISTER_REQUEST:
      messageTypeString = "REGISTER_REQUEST";
      break;
    case REGISTER_RESPONSE:
      messageTypeString = "REGISTER_RESPONSE";
      break;
    case LOGIN_REQUEST:
      messageTypeString = "LOGIN_REQUEST";
      break;
    case LOGIN_RESPONSE:
      messageTypeString = "LOGOUT_RESPONSE";
      break;
    case LOGOUT_REQUEST:
      messageTypeString = "LOGIN_REQUEST";
      break;
    case LOGOUT_RESPONSE:
      messageTypeString = "LOGOUT_RESPONSE";
      break;
    case ALL_ONLINE_USER_REQUEST:
      messageTypeString = "ALL_ONLINE_USER_REQUEST";
      break;
    case ALL_ONLINE_USER_RESPONSE:
      messageTypeString = "ALL_ONLINE_USER_RESPONSE";
      break;
    case SEARCH_USER_REQUEST:
      messageTypeString = "SEARCH_USER_REQUEST";
      break;
    case SEARCH_USER_RESPONSE:
      messageTypeString = "SEARCH_USER_RESPONSE";
      break;
    case ADD_FRIEND_REQUEST:
      messageTypeString = "ADD_FRIEND_REQUEST";
      break;
    case ADD_FRIEND_RESPONSE:
      messageTypeString = "ADD_FRIEND_RESPONSE";
      break;
    case ADD_FRIEND_AGREE:
      messageTypeString = "ADD_FRIEND_AGREE";
      break;
    case ADD_FRIEND_REFUSE:
      messageTypeString = "ADD_FRIEND_REFUSE";
      break;
    case REFRESH_FRIEND_REQUEST:
      messageTypeString = "REFRESH_FRIEND_REQUEST";
      break;
    case REFRESH_FRIEND_RESPONSE:
      messageTypeString = "REFRESH_FRIEND_RESPONSE";
      break;
    case DELETE_FRIEND_REQUEST:
      messageTypeString = "DELETE_FRIEND_REQUEST";
      break;
    case DELETE_FRIEND_RESPONSE:
      messageTypeString = "DELETE_FRIEND_RESPONSE";
      break;
    case PRIVATE_CHAT_REQUEST:
      messageTypeString = "PRIVATE_CHAT_REQUEST";
      break;
    case PRIVATE_CHAT_RESPONSE:
      messageTypeString = "PRIVATE_CHAT_RESPONSE";
      break;
    case GROUP_CHAT_REQUEST:
      messageTypeString = "GROUP_CHAT_REQUEST";
      break;
    case GROUP_CHAT_RESPONSE:
      messageTypeString = "GROUP_CHAT_RESPONSE";
      break;
    case CREATE_DIRECTORY_REQUEST:
      messageTypeString = "CREATE_DIRECTORY_REQUEST";
      break;
    case CREATE_DIRECTORY_RESPONSE:
      messageTypeString = "CREATE_DIRECTORY_RESPONSE";
      break;
    case REFRESH_FILE_REQUEST:
      messageTypeString = "REFRESH_FILE_REQUEST";
      break;
    case REFRESH_FILE_RESPONSE:
      messageTypeString = "REFRESH_FILE_RESPONSE";
      break;
    case DELETE_DIRECTORY_REQUEST:
      messageTypeString = "DELETE_DIRECTORY_REQUEST";
      break;
    case DELETE_DIRECTORY_RESPONSE:
      messageTypeString = "DELETE_DIRECTORY_RESPONSE";
      break;
    case RENAME_FILE_REQUEST:
      messageTypeString = "RENAME_FILE_REQUEST";
      break;
    case RENAME_FILE_RESPONSE:
      messageTypeString = "RENAME_FILE_RESPONSE";
      break;
    case ENTER_DIRECTORY_REQUEST:
      messageTypeString = "ENTER_DIRECTORY_REQUEST";
      break;
    case ENTER_DIRECTORY_RESPONSE:
      messageTypeString = "ENTER_DIRECTORY_RESPONSE";
      break;
    case BACK_TO_PREVIOUS_REQUEST:
      messageTypeString = "BACK_TO_PREVIOUS_REQUEST";
      break;
    case BACK_TO_PREVIOUS_RESPONSE:
      messageTypeString = "BACK_TO_PREVIOUS_RESPONSE";
      break;
    case UPLOAD_FILE_REQUEST:
      messageTypeString = "UPLOAD_FILE_REQUEST";
      break;
    case UPLOAD_FILE_RESPONSE:
      messageTypeString = "UPLOAD_FILE_RESPONSE";
      break;
    case DELETE_FILE_REQUEST:
      messageTypeString = "DELETE_FILE_REQUEST";
      break;
    case DELETE_FILE_RESPONSE:
      messageTypeString = "DELETE_FILE_RESPONSE";
      break;
    case DOWNLOAD_FILE_REQUEST:
      messageTypeString = "DOWNLOAD_FILE_REQUEST";
      break;
    case DOWNLOAD_FILE_RESPONSE:
      messageTypeString = "DOWNLOAD_FILE_RESPONSE";
      break;
    case SHARE_FILE_REQUEST:
      messageTypeString = "SHARE_FILE_REQUEST";
      break;
    case SHARE_FILE_RESPONSE:
      messageTypeString = "SHARE_FILE_RESPONSE";
      break;
    case SHARE_FILE_SEND_REQUEST:
      messageTypeString = "SHARE_FILE_SEND_REQUEST";
      break;
    case SHARE_FILE_SEND_RESPONSE:
      messageTypeString = "SHARE_FILE_SEND_RESPONSE";
      break;
    case MOVE_FILE_REQUEST:
      messageTypeString = "MOVE_FILE_REQUEST";
      break;
    case MOVE_FILE_RESPONSE:
      messageTypeString = "MOVE_FILE_RESPONSE";
      break;
    default:
      break;
  }
  return messageTypeString;
}
