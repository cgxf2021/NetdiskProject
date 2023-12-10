/********************************************************************************
** Form generated from reading UI file 'book_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOK_WIDGET_H
#define UI_BOOK_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Book
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *fileListWidget;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QPushButton *createDirectoryBtn;
    QPushButton *downloadFileBtn;
    QPushButton *shareFileBtn;
    QPushButton *uploadFileBtn;
    QPushButton *refreshFileBtn;
    QPushButton *deleteFileBtn;
    QPushButton *deleteDirectoryBtn;
    QPushButton *renameFileBtn;
    QPushButton *backBtn;
    QPushButton *targetDirectoryBtn;
    QPushButton *moveFileBtn;

    void setupUi(QWidget *Book)
    {
        if (Book->objectName().isEmpty())
            Book->setObjectName("Book");
        Book->resize(668, 496);
        horizontalLayout = new QHBoxLayout(Book);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        fileListWidget = new QListWidget(Book);
        fileListWidget->setObjectName("fileListWidget");

        horizontalLayout->addWidget(fileListWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        createDirectoryBtn = new QPushButton(Book);
        createDirectoryBtn->setObjectName("createDirectoryBtn");

        gridLayout->addWidget(createDirectoryBtn, 2, 0, 1, 1);

        downloadFileBtn = new QPushButton(Book);
        downloadFileBtn->setObjectName("downloadFileBtn");

        gridLayout->addWidget(downloadFileBtn, 3, 1, 1, 1);

        shareFileBtn = new QPushButton(Book);
        shareFileBtn->setObjectName("shareFileBtn");

        gridLayout->addWidget(shareFileBtn, 5, 1, 1, 1);

        uploadFileBtn = new QPushButton(Book);
        uploadFileBtn->setObjectName("uploadFileBtn");

        gridLayout->addWidget(uploadFileBtn, 2, 1, 1, 1);

        refreshFileBtn = new QPushButton(Book);
        refreshFileBtn->setObjectName("refreshFileBtn");

        gridLayout->addWidget(refreshFileBtn, 5, 0, 1, 1);

        deleteFileBtn = new QPushButton(Book);
        deleteFileBtn->setObjectName("deleteFileBtn");

        gridLayout->addWidget(deleteFileBtn, 4, 1, 1, 1);

        deleteDirectoryBtn = new QPushButton(Book);
        deleteDirectoryBtn->setObjectName("deleteDirectoryBtn");

        gridLayout->addWidget(deleteDirectoryBtn, 3, 0, 1, 1);

        renameFileBtn = new QPushButton(Book);
        renameFileBtn->setObjectName("renameFileBtn");

        gridLayout->addWidget(renameFileBtn, 4, 0, 1, 1);

        backBtn = new QPushButton(Book);
        backBtn->setObjectName("backBtn");

        gridLayout->addWidget(backBtn, 1, 0, 1, 1);

        targetDirectoryBtn = new QPushButton(Book);
        targetDirectoryBtn->setObjectName("targetDirectoryBtn");

        gridLayout->addWidget(targetDirectoryBtn, 1, 1, 1, 1);

        moveFileBtn = new QPushButton(Book);
        moveFileBtn->setObjectName("moveFileBtn");

        gridLayout->addWidget(moveFileBtn, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(2, 1);

        retranslateUi(Book);

        QMetaObject::connectSlotsByName(Book);
    } // setupUi

    void retranslateUi(QWidget *Book)
    {
        Book->setWindowTitle(QCoreApplication::translate("Book", "book", nullptr));
        createDirectoryBtn->setText(QCoreApplication::translate("Book", "\345\210\233\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
        downloadFileBtn->setText(QCoreApplication::translate("Book", "\344\270\213\350\275\275\346\226\207\344\273\266", nullptr));
        shareFileBtn->setText(QCoreApplication::translate("Book", "\345\205\261\344\272\253\346\226\207\344\273\266", nullptr));
        uploadFileBtn->setText(QCoreApplication::translate("Book", "\344\270\212\344\274\240\346\226\207\344\273\266", nullptr));
        refreshFileBtn->setText(QCoreApplication::translate("Book", "\345\210\267\346\226\260\346\226\207\344\273\266", nullptr));
        deleteFileBtn->setText(QCoreApplication::translate("Book", "\345\210\240\351\231\244\346\226\207\344\273\266", nullptr));
        deleteDirectoryBtn->setText(QCoreApplication::translate("Book", "\345\210\240\351\231\244\346\226\207\344\273\266\345\244\271", nullptr));
        renameFileBtn->setText(QCoreApplication::translate("Book", "\351\207\215\345\221\275\345\220\215\346\226\207\344\273\266", nullptr));
        backBtn->setText(QCoreApplication::translate("Book", "\350\277\224\345\233\236", nullptr));
        targetDirectoryBtn->setText(QCoreApplication::translate("Book", "\347\233\256\346\240\207\347\233\256\345\275\225", nullptr));
        moveFileBtn->setText(QCoreApplication::translate("Book", "\347\247\273\345\212\250\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Book: public Ui_Book {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOK_WIDGET_H
