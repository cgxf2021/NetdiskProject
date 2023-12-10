#include <QApplication>

#include "widget.h"
#include "./header/database_operator.hpp"

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);
  // DatabaseOperator::getInstance()->selectUser();
  Widget widget;
  widget.show();
  return application.exec();
}
