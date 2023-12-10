#ifndef CHAT_WIDGET_HPP_
#define CHAT_WIDGET_HPP_

#include <QWidget>

#include "../OnlineWidget/online.hpp"
#include "../header/log.hpp"
#include "../header/protocol.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Chat;
}
QT_END_NAMESPACE

class ChatWidget : public QWidget {
  Q_OBJECT

 public:
  ChatWidget(QWidget *parent = nullptr);
  ~ChatWidget();

  // 初始化组件
  void initializeChatWidget();
  // 解析数据显示在线用户
  void showOnlineUser(Protocol *protocol);
  // 解析数据显示在线好友
  void showOnlineFriend(Protocol *protocol);
  // 更新群聊信息
  void updateGroupMessage(const QString &message);
  // 获得在线好友列表
  QStringList getOnlienFriendList();

 private:
  Ui::Chat *ui;
  // 在线用户界面
  Online *m_online;

 private slots:
  // 点击显示在线用户按钮
  void showOnlineUserBtnClicked();
  // 点击查找用户按钮
  void searchUserBtnClicked();
  // 点击刷新好友列表按钮
  void refreshFriendBtnClicked();
  // 点击删除好友按钮
  void deleteFriendBtnClicked();
  // 点击私聊按钮
  void privateChatBtnClicked();
  // 点击发送按钮
  void sendBtnClicked();
};

#endif  // !CHAT_WIDGET_HPP_
