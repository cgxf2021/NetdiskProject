#include "book_widget.hpp"

#include <qtimer.h>

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QInputDialog>
#include <QMessageBox>

#include "../ShareWidget/share_widget.hpp"
#include "../header/cloud_socket.hpp"
#include "../header/log.hpp"
#include "./ui_book_widget.h"

BookWidget::BookWidget(QWidget *parent) : QWidget(parent), ui(new Ui::Book) {
  ui->setupUi(this);

  /* ===== initialize  ===== */
  // 初始化定时器
  m_timer = new QTimer(this);
  // 下载标志
  m_downloadSign = false;
  // 设置目标目录按钮不可用
  ui->targetDirectoryBtn->setEnabled(false);

  /* =====  connect  ===== */
  QObject::connect(ui->createDirectoryBtn, &QPushButton::clicked, this,
                   &BookWidget::createDirectoryBtnClicked);
  QObject::connect(ui->refreshFileBtn, &QPushButton::clicked, this,
                   &BookWidget::refreshFileBtnClicked);
  QObject::connect(ui->deleteDirectoryBtn, &QPushButton::clicked, this,
                   &BookWidget::deleteDirectoryBtnClicked);
  QObject::connect(ui->renameFileBtn, &QPushButton::clicked, this,
                   &BookWidget::renameFileBtnClicked);
  QObject::connect(ui->fileListWidget, &QListWidget::itemDoubleClicked, this,
                   &BookWidget::fileListWidgetDoubleClicked);
  QObject::connect(ui->deleteFileBtn, &QPushButton::clicked, this,
                   &BookWidget::deleteFileBtnClicked);
  QObject::connect(ui->backBtn, &QPushButton::clicked, this,
                   &BookWidget::backBtnClicked);
  QObject::connect(ui->uploadFileBtn, &QPushButton::clicked, this,
                   &BookWidget::uploadFileBtnClicked);
  QObject::connect(ui->downloadFileBtn, &QPushButton::clicked, this,
                   &BookWidget::downloadFileBtnClicked);
  QObject::connect(ui->shareFileBtn, &QPushButton::clicked, this,
                   &BookWidget::shareFileBtnClicked);
  QObject::connect(ui->moveFileBtn, &QPushButton::clicked, this,
                   &BookWidget::moveFileBtnClicked);
  QObject::connect(ui->targetDirectoryBtn, &QPushButton::clicked, this,
                   &BookWidget::targetDirectoryBtnClicked);
  QObject::connect(m_timer, &QTimer::timeout, this,
                   &BookWidget::uploadFileWhenTimeout);
}

BookWidget::~BookWidget() { delete ui; }

// 更新表中数据
void BookWidget::updateFileListData(Protocol *protocol) {
  if (protocol == nullptr) {
    return;
  }
  ui->fileListWidget->clear();
  // 文件个数
  int fileCount = protocol->messageLength / sizeof(FileInfo);
  FileInfo *p_fileInfo = nullptr;
  for (int i{0}; i < fileCount; i++) {
    p_fileInfo = (FileInfo *)protocol->message + i;
    QListWidgetItem *item = new QListWidgetItem();
    if (p_fileInfo->type == DIRECTORY) {
      item->setIcon(QIcon(QPixmap(":/icon/images/folder_icon.png")));
    } else if (p_fileInfo->type == NORMAL_FILE) {
      item->setIcon(QIcon(QPixmap(":/icon/images/file_icon.png")));
    }
    item->setText(QString(p_fileInfo->name));
    ui->fileListWidget->addItem(item);
  }
}

// 获得刷新按钮
QPushButton *BookWidget::getRefreshFileBtn() { return ui->refreshFileBtn; }

// 获得保存路径
const QString &BookWidget::getDownloadFilePath() const {
  return m_downloadFilePath;
}

// 设置下载标志
void BookWidget::setDownloadSign(bool downloadSign) {
  m_downloadSign = downloadSign;
}

// 获得下载标志
bool BookWidget::getDownloadSign() const { return m_downloadSign; }

// 设置文件大小
void BookWidget::setFileSize(qint64 fileSize) { m_fileSize = fileSize; }

// 获得文件大小
qint64 BookWidget::getFileSize() const { return m_fileSize; }

// 设置接收文件大小
void BookWidget::setReceiveSize(qint64 receiveSize) {
  m_receiveSize = receiveSize;
}

// 获得接收文件大小
qint64 BookWidget::getReceiveSize() const { return m_receiveSize; }

// 打开文件
void BookWidget::openDownloadFile() {
  m_file.setFileName(m_downloadFilePath);
  if (!m_file.open(QIODevice::WriteOnly)) {
    QMessageBox::warning(this, "下载文件", "打开文件失败");
  }
}

// 保存文件函数
void BookWidget::saveFileFromDisk() {
  if (m_file.isOpen()) {
    QByteArray buffer = CloudSocket::getInstance()->readAll();
    m_file.write(buffer);
    m_receiveSize += buffer.size();
    if (m_receiveSize == m_fileSize) {
      QMessageBox::information(this, "下载文件", "下载并保存文件成功");
      m_file.close();
      m_downloadSign = false;
    } else if (m_receiveSize > m_fileSize) {
      QMessageBox::warning(this, "下载文件", "下载并保存文件失败");
      m_file.close();
      m_downloadSign = false;
    }
  }
}

/* =====  槽函数  ===== */

// 点击创建目录按钮
void BookWidget::createDirectoryBtnClicked() {
  QString newDirectory = QInputDialog::getText(this, "新建目录", "目录名称");
  if (newDirectory.isEmpty()) {
    QMessageBox::warning(this, "新建目录", "目录名不能为空");
    return;
  } else if (newDirectory.size() > 30) {
    QMessageBox::warning(this, "新建目录", "目录长度超过30");
    return;
  }
  QString username = CloudSocket::getInstance()->getUsername();
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  // 创建协议数据包
  Protocol *protocol = createProtocol(currentDirectory.toUtf8().size());
  protocol->type = CREATE_DIRECTORY_REQUEST;
  std::strcpy(protocol->data, username.toStdString().c_str());
  std::strcpy(protocol->data + 32, newDirectory.toStdString().c_str());
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击刷新文件按钮
void BookWidget::refreshFileBtnClicked() {
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  Protocol *protocol = createProtocol(currentDirectory.toStdString().size());
  protocol->type = REFRESH_FILE_REQUEST;
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击删除目录按钮
void BookWidget::deleteDirectoryBtnClicked() {
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  QListWidgetItem *currentItem = ui->fileListWidget->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "删除目录", "选择一个要删除的目录");
    return;
  }
  QString directoryName = currentItem->text();
  Protocol *protocol = createProtocol(currentDirectory.toUtf8().size());
  protocol->type = DELETE_DIRECTORY_REQUEST;
  std::strcpy(protocol->data, directoryName.toStdString().c_str());
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击文件重命名按钮
void BookWidget::renameFileBtnClicked() {
  QListWidgetItem *currentItem = ui->fileListWidget->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "重命名文件", "选择一个要重命名的文件");
    return;
  }
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  QString oldFileName = currentItem->text();
  QString newFileName = QInputDialog::getText(this, "文件重命名", "文件名");
  if (newFileName.isEmpty()) {
    QMessageBox::warning(this, "文件重命名", "文件名不能为空");
    return;
  }
  Protocol *protocol = createProtocol(currentDirectory.toUtf8().size());
  protocol->type = RENAME_FILE_REQUEST;
  std::strcpy(protocol->data, oldFileName.toStdString().c_str());
  std::strcpy(protocol->data + 32, newFileName.toStdString().c_str());
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 双击文件列表
void BookWidget::fileListWidgetDoubleClicked(QListWidgetItem *item) {
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  QString directoryName = item->text();
  Protocol *protocol = createProtocol(currentDirectory.toUtf8().size());
  protocol->type = ENTER_DIRECTORY_REQUEST;
  std::strcpy(protocol->data, directoryName.toStdString().c_str());
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击返回上一级按钮
void BookWidget::backBtnClicked() {
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  QString rootDirectory =
      QString("home/") + CloudSocket::getInstance()->getUsername();
  if (rootDirectory == currentDirectory) {
    QMessageBox::warning(this, "返回", "当前目录为根目录");
    return;
  }
  Protocol *protocol = createProtocol(currentDirectory.toUtf8().size());
  protocol->type = BACK_TO_PREVIOUS_REQUEST;
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击上传文件按钮
void BookWidget::uploadFileBtnClicked() {
  QString uploadFilePath =
      QFileDialog::getOpenFileName(this, "上传文件", QDir::currentPath());
  if (uploadFilePath.isEmpty()) {
    return;
  }
  QString fileName = QFileInfo(uploadFilePath).fileName();
  qint64 fileSize = QFileInfo(uploadFilePath).size();
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  Protocol *protocol = createProtocol(currentDirectory.toUtf8().size());
  protocol->type = UPLOAD_FILE_REQUEST;
  std::strcpy(protocol->data, fileName.toStdString().c_str());
  std::memcpy(protocol->data + 32, (char *)&fileSize, sizeof(qint64));
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
  // 启动定时器
  m_uploadFilePath = uploadFilePath;
  m_timer->start(1000);
}

// 上传文件
void BookWidget::uploadFileWhenTimeout() {
  m_timer->stop();
  QFile file(m_uploadFilePath);
  if (file.open(QIODevice::ReadOnly)) {
    const int readSize = 4096;
    char *p_buffer = new char[readSize];
    qint64 ret = 0;
    while (true) {
      std::memset(p_buffer, 0, readSize);
      ret = file.read(p_buffer, readSize);
      if (ret > 0 && ret <= readSize) {
        CloudSocket::getInstance()->write(p_buffer, ret);
      } else if (ret == 0) {
        break;
      } else {
        QMessageBox::warning(this, "上传文件", "上传文件失败");
        break;
      }
    }
    delete[] p_buffer;
    file.close();
  } else {
    QMessageBox::warning(this, "打开文件", "打开文件失败");
  }
}

// 点击删除文件按钮
void BookWidget::deleteFileBtnClicked() {
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  QListWidgetItem *currentItem = ui->fileListWidget->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "删除文件", "选择一个要删除的文件");
    return;
  }
  QString directoryName = currentItem->text();
  Protocol *protocol = createProtocol(currentDirectory.toUtf8().size());
  protocol->type = DELETE_FILE_REQUEST;
  std::strcpy(protocol->data, directoryName.toStdString().c_str());
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击下载文件按钮
void BookWidget::downloadFileBtnClicked() {
  QListWidgetItem *currentItem = ui->fileListWidget->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "下载文件", "选择一个要下载的文件");
    return;
  }
  m_downloadFilePath =
      QFileDialog::getSaveFileName(this, "保存文件", QDir::currentPath());
  if (m_downloadFilePath.isEmpty()) {
    QMessageBox::warning(this, "下载文件", "保存路径为空");
    return;
  }
  QString currentDirectory = CloudSocket::getInstance()->getCurrentDirectory();
  Protocol *protocol = createProtocol(currentDirectory.toUtf8().size());
  protocol->type = DOWNLOAD_FILE_REQUEST;
  std::strcpy(protocol->data, currentItem->text().toStdString().c_str());
  std::strcpy(protocol->message, currentDirectory.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
}

// 点击分享文件按钮
void BookWidget::shareFileBtnClicked() {
  QListWidgetItem *currentItem = ui->fileListWidget->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "分享文件", "选择一个要分享的文件");
    return;
  }
  if (ShareWidget::getInstance()->isHidden()) {
    ShareWidget::getInstance()->show();
  }
  ShareWidget::getInstance()->updateFriendItem();
  ShareWidget::getInstance()->setSharedFileName(currentItem->text());
}

// 点击移动文件按钮
void BookWidget::moveFileBtnClicked() {
  QListWidgetItem *currentItem = ui->fileListWidget->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "移动文件", "选择一个要移动的文件");
    return;
  }
  m_moveFilePath = CloudSocket::getInstance()->getCurrentDirectory() + '/' +
                   currentItem->text();
  ui->targetDirectoryBtn->setEnabled(true);
}

// 点击目标目录按钮
void BookWidget::targetDirectoryBtnClicked() {
  QListWidgetItem *currentItem = ui->fileListWidget->currentItem();
  if (!currentItem) {
    QMessageBox::warning(this, "目标目录", "选择一个存放移动文件的目录");
    return;
  }
  m_targetDirectoryPath = CloudSocket::getInstance()->getCurrentDirectory() +
                          '/' + currentItem->text();
  unsigned int moveFilePathSize = m_moveFilePath.toUtf8().size();
  unsigned int targetDirectoryPathSize = m_targetDirectoryPath.toUtf8().size();
  Protocol *protocol =
      createProtocol(moveFilePathSize + targetDirectoryPathSize);
  protocol->type = MOVE_FILE_REQUEST;
  std::memcpy(protocol->data, (char *)&moveFilePathSize, sizeof(unsigned int));
  std::memcpy(protocol->data + 32, (char *)&targetDirectoryPathSize,
              sizeof(unsigned int));
  std::strcpy(protocol->message, m_moveFilePath.toStdString().c_str());
  std::strcpy(protocol->message + moveFilePathSize,
              m_targetDirectoryPath.toStdString().c_str());
  CloudSocket::getInstance()->write((char *)protocol, protocol->length);
  freeProtocol(protocol);
  ui->targetDirectoryBtn->setEnabled(false);
}
