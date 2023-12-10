#ifndef HOME_HPP_
#define HOME_HPP_

#include <QWidget>

#include "../BookWidget/book_widget.hpp"
#include "../ChatWidget/chat_widget.hpp"
#include "../header/log.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Home;
}
QT_END_NAMESPACE

class Home : public QWidget {
  Q_OBJECT

 public:
  static Home *getInstance();
  // 初始化home界面
  void initializeHomeWidget();
  // 获得聊天界面
  ChatWidget *getChatWidget();
  // 获得图书界面
  BookWidget *getBookWidget();
  // 设置title
  void setHomeTitle(const QString &username);

 private:
  Home(QWidget *parent = nullptr);
  ~Home();
  Home(const Home &) = delete;
  Home &operator=(const Home &) = delete;

  Ui::Home *ui;
  // 聊天界面
  ChatWidget *m_chatWidget;
  // 图书界面
  BookWidget *m_bookWidget;

 private slots:
};

#endif  // !HOME_HPP_
