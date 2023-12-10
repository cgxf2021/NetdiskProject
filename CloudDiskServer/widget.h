#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpServer>
#include <QWidget>

#include "./header/cloud_server.hpp"
#include "./header/log.hpp"

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
  // serve
  CloudServer *m_server;
  // socket
  // QTcpSocket *m_socket;

  // 加载配置文件
  void loadConfig();
  // 初始化serve
  void initializeServe();

 private slots:
  void addMessage(const QString &message);
};
#endif  // WIDGET_H
