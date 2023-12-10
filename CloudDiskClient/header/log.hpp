#ifndef LOG_HPP_
#define LOG_HPP_

#include <QDebug>

// 输出调用处的函数名
#define LOG (qDebug() << "[" << __PRETTY_FUNCTION__ << "] ")

#endif  // !LOG_HPP_
