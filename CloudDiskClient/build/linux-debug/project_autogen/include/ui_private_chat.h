/********************************************************************************
** Form generated from reading UI file 'private_chat.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIVATE_CHAT_H
#define UI_PRIVATE_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrivateChat
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *chatTextEdit;
    QHBoxLayout *horizontalLayout;
    QLineEdit *sendLineEdit;
    QPushButton *sendBtn;

    void setupUi(QWidget *PrivateChat)
    {
        if (PrivateChat->objectName().isEmpty())
            PrivateChat->setObjectName("PrivateChat");
        PrivateChat->resize(500, 350);
        verticalLayout = new QVBoxLayout(PrivateChat);
        verticalLayout->setObjectName("verticalLayout");
        chatTextEdit = new QTextEdit(PrivateChat);
        chatTextEdit->setObjectName("chatTextEdit");

        verticalLayout->addWidget(chatTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        sendLineEdit = new QLineEdit(PrivateChat);
        sendLineEdit->setObjectName("sendLineEdit");

        horizontalLayout->addWidget(sendLineEdit);

        sendBtn = new QPushButton(PrivateChat);
        sendBtn->setObjectName("sendBtn");

        horizontalLayout->addWidget(sendBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PrivateChat);

        QMetaObject::connectSlotsByName(PrivateChat);
    } // setupUi

    void retranslateUi(QWidget *PrivateChat)
    {
        PrivateChat->setWindowTitle(QCoreApplication::translate("PrivateChat", "private chat", nullptr));
        sendBtn->setText(QCoreApplication::translate("PrivateChat", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrivateChat: public Ui_PrivateChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIVATE_CHAT_H
