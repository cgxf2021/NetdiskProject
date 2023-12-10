#include "../header/database_operator.hpp"

#include <qurl.h>

#include <QSqlQuery>
#include <QUrl>

DatabaseOperator::DatabaseOperator(QObject *parent) : QObject(parent) {
  initializeDatabase();
}

DatabaseOperator::~DatabaseOperator() {
  close();
  QSqlDatabase::removeDatabase(m_connection.connectionName());
}

// 初始化数据库
void DatabaseOperator::initializeDatabase() {
  // 数据库类型
  QString databaseType = "QSQLITE";
  // 连接名
  QString connectName = "cloud_connection";
  // 数据库名
  QString databaseName =
      "/home/smxrfx/TrainClass/LanguageCPP/CloudDisk/CloudDiskServer/cloud.db";
  // LOG << "database name: " << databaseName;
  m_connection = QSqlDatabase::addDatabase(databaseType, connectName);
  if (!m_connection.isValid()) {
    LOG << "数据库连接失败";
  }
  m_connection.setDatabaseName(databaseName);
  if (!open()) {
    LOG << "数据库打开失败";
  }
}

// 打开数据库
bool DatabaseOperator::open() {
  m_connection.open();
  return m_connection.isOpen();
}

// 关闭数据库
void DatabaseOperator::close() { m_connection.close(); }

// 创建实例
DatabaseOperator *DatabaseOperator::getInstance() {
  static DatabaseOperator databaseOperator;
  return &databaseOperator;
}

/* =====  数据库增删改查  ===== */

// 插入注册信息
bool DatabaseOperator::insertRegisterInformation(const QString &username,
                                                 const QString &password) {
  if (username.isEmpty() || password.isEmpty()) {
    return false;
  }
  QString sql =
      "INSERT INTO user(name, password)\n"
      "VALUES('" +
      username + "', '" + password + "');";
  QSqlQuery query(m_connection);
  return query.exec(sql);
}

// 查询登陆信息
bool DatabaseOperator::selectLoginInformation(const QString &username,
                                              const QString &password) {
  if (username.isEmpty() || password.isEmpty()) {
    return false;
  }
  QString sql =
      "SELECT name, password, state FROM user\n"
      "WHERE name = '" +
      username + "' AND password = '" + password + "' AND state = 0;";
  QSqlQuery query(m_connection);
  query.exec(sql);
  if (query.next()) {
    QString sql = "UPDATE user SET state = 1 WHERE name = '" + username + "';";
    return query.exec(sql);
  } else {
    return false;
  }
}

// 查询登陆信息
bool DatabaseOperator::deleteLogoutInformation(const QString &username,
                                               const QString &password) {
  if (username.isEmpty()) {
    return false;
  }
  QString sql = "DELETE FROM user WHERE name = '" + username +
                "' AND password = '" + password + "' AND state = 0;";
  QSqlQuery query(m_connection);
  query.exec("PRAGMA foreign_keys = ON;");
  bool ret = query.exec(sql);
  if ((query.numRowsAffected() == 0) || (!ret)) {
    return false;
  }
  return true;
}

// 更新下线信息
bool DatabaseOperator::updateOfflineInformation(const QString &username) {
  if (username.isEmpty()) {
    return false;
  }
  QString sql = "UPDATE user SET state = 0 WHERE name = '" + username + "';";
  QSqlQuery query(m_connection);
  bool ret = query.exec(sql);
  // 必有一条语句修改
  if ((query.numRowsAffected() == 0) || (!ret)) {
    return false;
  }
  return true;
}

// 查询所有在线用户
QStringList DatabaseOperator::selectAllOnlineUsers() {
  QString sql = "SELECT name FROM user WHERE state = 1;";
  QSqlQuery query(m_connection);
  query.exec(sql);
  QStringList onlineUsers;
  while (query.next()) {
    onlineUsers.push_back(query.value("name").toString());
  }
  return onlineUsers;
}

// 根据用户名查询用户状态
int DatabaseOperator::selectUserStateByName(const QString &username) {
  QString sql = "SELECT state FROM user WHERE name = '" + username + "';";
  QSqlQuery query(m_connection);
  query.exec(sql);
  if (query.next()) {
    return query.value("state").toInt();
  } else {
    return -1;
  }
}

// 查询是否为好友
bool DatabaseOperator::selectIsFriend(const QString &username,
                                      const QString &otherName) {
  QString sql =
      "SELECT * FROM friend \n"
      "WHERE id = (SELECT id FROM user WHERE name = '" +
      username +
      "')\n"
      "AND friend_id = (SELECT id FROM user WHERE name = '" +
      otherName + "');";
  QSqlQuery query(m_connection);
  query.exec(sql);
  return query.next();
}

// 插入好友记录
bool DatabaseOperator::insertFriendRecord(const QString &username,
                                          const QString &otherUsername) {
  QSqlQuery query(m_connection);
  // 查询id, friend_id
  QString sql = "SELECT id FROM user WHERE name = '" + username + "';";
  query.exec(sql);
  if (!query.next()) {
    return false;
  }
  int id = query.value("id").toInt();
  sql = "SELECT id FROM user WHERE name = '" + otherUsername + "';";
  query.exec(sql);
  if (!query.next()) {
    return false;
  }
  int friendId = query.value("id").toInt();
  sql = QString("INSERT INTO friend(id, friend_id) VALUES(%1, %2), (%3, %4);")
            .arg(id)
            .arg(friendId)
            .arg(friendId)
            .arg(id);
  return query.exec(sql);
}

// 查询好友列表
QStringList DatabaseOperator::selectFriendList(const QString username) {
  // 查询username的在线好友
  QString sql =
      "SELECT username, u2.name AS friend_name FROM (\n"
      "SELECT u1.name AS username, friend_id FROM friend AS f1\n"
      "LEFT JOIN user AS u1 ON f1.id = u1.id) AS f2 LEFT JOIN\n"
      "user as u2 on f2.friend_id = u2.id\n"
      "WHERE username = '" +
      username + "' AND state = 1";
  QSqlQuery query(m_connection);
  query.exec(sql);
  QStringList friendList;
  while (query.next()) {
    friendList.push_back(query.value("friend_name").toString());
  }

  return friendList;
}

// 删除好友关系数据
bool DatabaseOperator::deleteFriendRelation(const QString username,
                                            const QString &otherUsername) {
  if (username.isEmpty() || otherUsername.isEmpty()) {
    return false;
  }
  QSqlQuery query(m_connection);
  // 查询id, friend_id
  QString sql = "SELECT id FROM user WHERE name = '" + username + "';";
  query.exec(sql);
  if (!query.next()) {
    return false;
  }
  int id = query.value("id").toInt();
  sql = "SELECT id FROM user WHERE name = '" + otherUsername + "';";
  query.exec(sql);
  if (!query.next()) {
    return false;
  }
  int friendId = query.value("id").toInt();
  // 删除记录
  sql = QString("DELETE FROM friend WHERE id = %1 AND friend_id = %2")
            .arg(id)
            .arg(friendId);
  if (!query.exec(sql)) {
    return false;
  }
  sql = QString("DELETE FROM friend WHERE id = %1 AND friend_id = %2")
            .arg(friendId)
            .arg(id);
  return query.exec(sql);
}

// 查询表
void DatabaseOperator::selectUser() {
  if (!m_connection.isOpen()) {
    LOG << "连接还未打开";
    return;
  }
  QString sql = "SELECT * FROM user";
  QSqlQuery query(m_connection);
  bool sign = query.exec(sql);
  if (!sign) {
    LOG << "查询失败";
    return;
  }
  while (query.next()) {
    LOG << query.value("id") << ' ' << query.value("name") << ' '
        << query.value("password") << ' ' << query.value("state");
  }
}
