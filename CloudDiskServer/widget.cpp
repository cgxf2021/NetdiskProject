#include "widget.h"

#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "./header/cloud_socket.hpp"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  loadConfig();
  initializeServe();
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

// 初始化Socket
void Widget::initializeServe() {
  // 创建服务器
  m_server = CloudServer::getInstance();
  // 开启监听
  m_server->listen(QHostAddress::AnyIPv4, m_serverPort);
  // messageTextEidt
  ui->messageTextEdit->setReadOnly(true);

  QObject::connect(CloudServer::getInstance(), &CloudServer::sendMessageSignal,
                   this, &Widget::addMessage);
}

/* =====  槽函数  ===== */

void Widget::addMessage(const QString &message) {
  ui->messageTextEdit->append(message);
}
