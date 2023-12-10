#ifndef PRIVATE_CHAT_HPP_
#define PRIVATE_CHAT_HPP_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class PrivateChat;
}
QT_END_NAMESPACE

class PrivateChat : public QWidget {
  Q_OBJECT
 public:
  static PrivateChat *getInstance();
  // 获得朋友名字
  const QString &getFriendName() const;
  // 设置朋友名字
  void setFriendName(const QString &friendName);
  // 更新消息
  void updateMessage(const QString &message);
  // 设置windows title
  void setPrivateChatWindowTitle(const QString &title);

 private:
  PrivateChat(QWidget *parent = nullptr);
  ~PrivateChat();
  PrivateChat(const PrivateChat &) = delete;
  PrivateChat &operator=(const PrivateChat &) = delete;

  Ui::PrivateChat *ui;
  // 私聊朋友的用户名
  QString m_friendName;

 private slots:
  // 点击发送按钮
  void sendBtnClicked();
};

#endif  // !PRIVATE_CHAT_HPP_
