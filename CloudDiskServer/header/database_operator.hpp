#ifndef DATABASE_OPERATOR_HPP_
#define DATABASE_OPERATOR_HPP_

#include <QObject>
#include <QSqlDatabase>
#include <QStringList>

#include "log.hpp"

class DatabaseOperator : public QObject {
  Q_OBJECT
 private:
  explicit DatabaseOperator(QObject *parent = nullptr);
  ~DatabaseOperator();
  DatabaseOperator(const DatabaseOperator &) = delete;
  DatabaseOperator &operator=(const DatabaseOperator &) = delete;
  // 数据库连接
  QSqlDatabase m_connection;
  // 初始化数据库
  void initializeDatabase();
  // 打开数据库
  bool open();
  // 关闭数据库
  void close();

 public:
  static DatabaseOperator *getInstance();
  // 插入注册信息
  bool insertRegisterInformation(const QString &username,
                                 const QString &password);
  // 查询登陆信息
  bool selectLoginInformation(const QString &username, const QString &password);
  // 查询登陆信息
  bool deleteLogoutInformation(const QString &username,
                               const QString &password);
  // 更新下线信息
  bool updateOfflineInformation(const QString &username);
  // 查询所有在线用户
  QStringList selectAllOnlineUsers();
  // 根据用户名查询用户状态
  int selectUserStateByName(const QString &username);
  // 查询是否为好友
  bool selectIsFriend(const QString &username, const QString &otherUsername);
  // 插入好友记录
  bool insertFriendRecord(const QString &username,
                          const QString &otherUsername);
  // 查询好友列表
  QStringList selectFriendList(const QString username);
  // 删除好友关系数据
  bool deleteFriendRelation(const QString username,
                            const QString &otherUsername);

  // 查询表
  void selectUser();
};

#endif  // !DATABASE_OPERATOR_HPP_
