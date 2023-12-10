/********************************************************************************
** Form generated from reading UI file 'online.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINE_H
#define UI_ONLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Online
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *onlinePeopleListWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addFriendBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Online)
    {
        if (Online->objectName().isEmpty())
            Online->setObjectName("Online");
        Online->resize(368, 243);
        verticalLayout = new QVBoxLayout(Online);
        verticalLayout->setSpacing(8);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 5, 0, 0);
        onlinePeopleListWidget = new QListWidget(Online);
        onlinePeopleListWidget->setObjectName("onlinePeopleListWidget");

        verticalLayout->addWidget(onlinePeopleListWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addFriendBtn = new QPushButton(Online);
        addFriendBtn->setObjectName("addFriendBtn");

        horizontalLayout->addWidget(addFriendBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Online);

        QMetaObject::connectSlotsByName(Online);
    } // setupUi

    void retranslateUi(QWidget *Online)
    {
        Online->setWindowTitle(QCoreApplication::translate("Online", "online", nullptr));
        addFriendBtn->setText(QCoreApplication::translate("Online", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Online: public Ui_Online {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINE_H
