#ifndef SHARE_WIDGET_HPP_
#define SHARE_WIDGET_HPP_

#include <QButtonGroup>
#include <QStringList>
#include <QWidget>

#include "../header/log.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Share;
}
QT_END_NAMESPACE

class ShareWidget : public QWidget {
  Q_OBJECT
 public:
  static ShareWidget *getInstance();
  // 更新好友列表
  void updateFriendItem();
  // 获得分享者
  const QStringList &getShareFriendList() const;
  // 设置分享者
  void setShareFriendList(const QStringList &shareFriendList);
  // 设置分享文件名
  void setSharedFileName(const QString &shareFileName);
  // 获得分享文件名
  const QString &getShareFileName() const;

 private:
  ShareWidget(QWidget *parent = nullptr);
  ~ShareWidget();
  ShareWidget(const ShareWidget &) = delete;
  ShareWidget &operator=(const ShareWidget &) = delete;

  Ui::Share *ui;
  // 按钮组
  QButtonGroup *m_buttonGroup;
  // 分享者
  QStringList m_shareFriendList;
  // 分享文件名
  QString m_sharedFileName;

 private slots:
  // 点击全选按钮
  void selectAllBtnClicked();
  // 点击全部取消按钮
  void cancelSelectedBtnClicked();
  // 点击确定按钮
  void confirmBtnClicked();
  // 点击取消按钮
  void cancelBtnClicked();
};

#endif  // !SHARE_WIDGET_HPP_
