#ifndef BOOK_WIDGET_HPP_
#define BOOK_WIDGET_HPP_

#include <QFile>
#include <QListWidgetItem>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "../header/protocol.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Book;
}
QT_END_NAMESPACE

class BookWidget : public QWidget {
  Q_OBJECT
 public:
  BookWidget(QWidget *parent = nullptr);
  ~BookWidget();
  // 更新表中数据
  void updateFileListData(Protocol *protocol);
  // 获得刷新按钮
  QPushButton *getRefreshFileBtn();
  // 设置下载标志
  void setDownloadSign(bool downloadSign);
  // 获得下载标志
  bool getDownloadSign() const;
  // 获得保存路径
  const QString &getDownloadFilePath() const;
  // 设置文件大小
  void setFileSize(qint64 fileSize);
  // 获得文件大小
  qint64 getFileSize() const;
  // 设置接收文件大小
  void setReceiveSize(qint64 receiveSize);
  // 获得接收文件大小
  qint64 getReceiveSize() const;
  // 打开文件
  void openDownloadFile();
  // 保存文件函数
  void saveFileFromDisk();

 private:
  Ui::Book *ui;
  // 定时器
  QTimer *m_timer;
  // 上传的文件
  QString m_uploadFilePath;
  // 下载文件路径
  QString m_downloadFilePath;
  // 下载标志
  bool m_downloadSign;
  // 文件大小
  qint64 m_fileSize;
  // 接收文件的大小
  qint64 m_receiveSize;
  // 文件
  QFile m_file;
  // 移动文件路径
  QString m_moveFilePath;
  // 目标目录路径
  QString m_targetDirectoryPath;

 private slots:
  // 点击创建目录按钮
  void createDirectoryBtnClicked();
  // 点击刷新文件按钮
  void refreshFileBtnClicked();
  // 点击删除目录按钮
  void deleteDirectoryBtnClicked();
  // 点击文件重命名按钮
  void renameFileBtnClicked();
  // 双击文件列表
  void fileListWidgetDoubleClicked(QListWidgetItem *item);
  // 点击返回上一级按钮
  void backBtnClicked();
  // 点击上传文件按钮
  void uploadFileBtnClicked();
  // 点击删除文件按钮
  void deleteFileBtnClicked();
  // 点击下载文件按钮
  void downloadFileBtnClicked();
  // 点击分享文件按钮
  void shareFileBtnClicked();
  // 点击移动文件按钮
  void moveFileBtnClicked();
  // 点击目标目录按钮
  void targetDirectoryBtnClicked();
  // 上传文件
  void uploadFileWhenTimeout();
};

#endif  // !BOOK_WIDGET_HPP_
