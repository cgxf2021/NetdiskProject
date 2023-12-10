#include "home.hpp"

#include "./ui_home.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  initializeHomeWidget();
}

Home::~Home() { delete ui; }

Home *Home::getInstance() {
  static Home home;
  return &home;
}

// 初始化home界面
void Home::initializeHomeWidget() {
  // 聊天界面
  m_chatWidget = new ChatWidget(this);
  // 图书界面
  m_bookWidget = new BookWidget(this);
  // 添加到stacklist
  ui->stackedWidget->addWidget(m_chatWidget);
  ui->stackedWidget->addWidget(m_bookWidget);
  // 列表item
  ui->homeListWidget->addItem("聊天");
  ui->homeListWidget->addItem("图书");

  /* =====  connect  ===== */
  QObject::connect(ui->homeListWidget, &QListWidget::currentRowChanged,
                   ui->stackedWidget, &QStackedWidget::setCurrentIndex);
}

// 获得聊天界面
ChatWidget *Home::getChatWidget() { return m_chatWidget; }

// 获得图书界面
BookWidget *Home::getBookWidget() { return m_bookWidget; }

// 设置title
void Home::setHomeTitle(const QString &username) {
  setWindowTitle(username + QString(" netdisk"));
}
