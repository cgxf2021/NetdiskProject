#ifndef ONLINE_HPP_
#define ONLINE_HPP_

#include <QListWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Online;
}
QT_END_NAMESPACE

class Online : public QWidget {
  Q_OBJECT

 public:
  Online(QWidget *parent = nullptr);
  ~Online();

  // 获得在线用户列表组件
  QListWidget *getOnlineUserList();

 private:
  Ui::Online *ui;

 private slots:
  // 点击添加好友
  void addFriendBtnClicked();
};

#endif  // !ONLINE_HPP_
