/********************************************************************************
** Form generated from reading UI file 'share_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHARE_WIDGET_H
#define UI_SHARE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Share
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *selectAllBtn;
    QPushButton *cancelSelectedBtn;
    QSpacerItem *horizontalSpacer;
    QScrollArea *showFriendScrollArea;
    QWidget *friendItemWidget;
    QVBoxLayout *friendItemVerticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

    void setupUi(QWidget *Share)
    {
        if (Share->objectName().isEmpty())
            Share->setObjectName("Share");
        Share->resize(450, 350);
        verticalLayout_2 = new QVBoxLayout(Share);
        verticalLayout_2->setSpacing(8);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(9, 9, 9, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        selectAllBtn = new QPushButton(Share);
        selectAllBtn->setObjectName("selectAllBtn");

        horizontalLayout->addWidget(selectAllBtn);

        cancelSelectedBtn = new QPushButton(Share);
        cancelSelectedBtn->setObjectName("cancelSelectedBtn");

        horizontalLayout->addWidget(cancelSelectedBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        showFriendScrollArea = new QScrollArea(Share);
        showFriendScrollArea->setObjectName("showFriendScrollArea");
        showFriendScrollArea->setWidgetResizable(true);
        friendItemWidget = new QWidget();
        friendItemWidget->setObjectName("friendItemWidget");
        friendItemWidget->setGeometry(QRect(0, 0, 430, 250));
        friendItemVerticalLayout = new QVBoxLayout(friendItemWidget);
        friendItemVerticalLayout->setObjectName("friendItemVerticalLayout");
        friendItemVerticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        showFriendScrollArea->setWidget(friendItemWidget);

        verticalLayout_2->addWidget(showFriendScrollArea);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        confirmBtn = new QPushButton(Share);
        confirmBtn->setObjectName("confirmBtn");

        horizontalLayout_2->addWidget(confirmBtn);

        cancelBtn = new QPushButton(Share);
        cancelBtn->setObjectName("cancelBtn");

        horizontalLayout_2->addWidget(cancelBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(Share);

        QMetaObject::connectSlotsByName(Share);
    } // setupUi

    void retranslateUi(QWidget *Share)
    {
        Share->setWindowTitle(QCoreApplication::translate("Share", "share", nullptr));
        selectAllBtn->setText(QCoreApplication::translate("Share", "\345\205\250\351\200\211", nullptr));
        cancelSelectedBtn->setText(QCoreApplication::translate("Share", "\345\217\226\346\266\210\345\205\250\351\200\211", nullptr));
        confirmBtn->setText(QCoreApplication::translate("Share", "\347\241\256\345\256\232", nullptr));
        cancelBtn->setText(QCoreApplication::translate("Share", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Share: public Ui_Share {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHARE_WIDGET_H
