/********************************************************************************
** Form generated from reading UI file 'chat_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_WIDGET_H
#define UI_CHAT_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat
{
public:
    QVBoxLayout *chatVerticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *chatTextEdit;
    QListWidget *friendListWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *deleteFriendBtn;
    QPushButton *refreshFriendBtn;
    QPushButton *showOnlineUserBtn;
    QPushButton *searchUserBtn;
    QPushButton *privateChatBtn;
    QHBoxLayout *horizontalLayout;
    QLineEdit *chatLineEdit;
    QPushButton *sendBtn;

    void setupUi(QWidget *Chat)
    {
        if (Chat->objectName().isEmpty())
            Chat->setObjectName("Chat");
        Chat->resize(659, 485);
        chatVerticalLayout = new QVBoxLayout(Chat);
        chatVerticalLayout->setSpacing(8);
        chatVerticalLayout->setObjectName("chatVerticalLayout");
        chatVerticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        chatTextEdit = new QTextEdit(Chat);
        chatTextEdit->setObjectName("chatTextEdit");

        horizontalLayout_2->addWidget(chatTextEdit);

        friendListWidget = new QListWidget(Chat);
        friendListWidget->setObjectName("friendListWidget");

        horizontalLayout_2->addWidget(friendListWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        deleteFriendBtn = new QPushButton(Chat);
        deleteFriendBtn->setObjectName("deleteFriendBtn");

        verticalLayout->addWidget(deleteFriendBtn);

        refreshFriendBtn = new QPushButton(Chat);
        refreshFriendBtn->setObjectName("refreshFriendBtn");

        verticalLayout->addWidget(refreshFriendBtn);

        showOnlineUserBtn = new QPushButton(Chat);
        showOnlineUserBtn->setObjectName("showOnlineUserBtn");

        verticalLayout->addWidget(showOnlineUserBtn);

        searchUserBtn = new QPushButton(Chat);
        searchUserBtn->setObjectName("searchUserBtn");

        verticalLayout->addWidget(searchUserBtn);

        privateChatBtn = new QPushButton(Chat);
        privateChatBtn->setObjectName("privateChatBtn");

        verticalLayout->addWidget(privateChatBtn);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 4);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 1);

        chatVerticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        chatLineEdit = new QLineEdit(Chat);
        chatLineEdit->setObjectName("chatLineEdit");

        horizontalLayout->addWidget(chatLineEdit);

        sendBtn = new QPushButton(Chat);
        sendBtn->setObjectName("sendBtn");

        horizontalLayout->addWidget(sendBtn);


        chatVerticalLayout->addLayout(horizontalLayout);


        retranslateUi(Chat);

        QMetaObject::connectSlotsByName(Chat);
    } // setupUi

    void retranslateUi(QWidget *Chat)
    {
        Chat->setWindowTitle(QCoreApplication::translate("Chat", "Chat", nullptr));
        deleteFriendBtn->setText(QCoreApplication::translate("Chat", "\345\210\240\351\231\244\345\245\275\345\217\213", nullptr));
        refreshFriendBtn->setText(QCoreApplication::translate("Chat", "\345\210\267\346\226\260\345\245\275\345\217\213", nullptr));
        showOnlineUserBtn->setText(QCoreApplication::translate("Chat", "\346\230\276\347\244\272\345\234\250\347\272\277\347\224\250\346\210\267", nullptr));
        searchUserBtn->setText(QCoreApplication::translate("Chat", "\346\237\245\346\211\276\347\224\250\346\210\267", nullptr));
        privateChatBtn->setText(QCoreApplication::translate("Chat", "\347\247\201\350\201\212", nullptr));
        sendBtn->setText(QCoreApplication::translate("Chat", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chat: public Ui_Chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_WIDGET_H
