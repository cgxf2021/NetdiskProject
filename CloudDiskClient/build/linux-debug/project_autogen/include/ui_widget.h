/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *userLineEdit;
    QLineEdit *passwordLineEdit;
    QLabel *userLabel;
    QLabel *passwordLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *logoutBtn;
    QPushButton *registerBtn;
    QPushButton *loginBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(300, 150);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        userLineEdit = new QLineEdit(Widget);
        userLineEdit->setObjectName("userLineEdit");

        gridLayout->addWidget(userLineEdit, 0, 1, 1, 1);

        passwordLineEdit = new QLineEdit(Widget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwordLineEdit, 1, 1, 1, 1);

        userLabel = new QLabel(Widget);
        userLabel->setObjectName("userLabel");
        userLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(userLabel, 0, 0, 1, 1);

        passwordLabel = new QLabel(Widget);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(passwordLabel, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        logoutBtn = new QPushButton(Widget);
        logoutBtn->setObjectName("logoutBtn");

        horizontalLayout->addWidget(logoutBtn);

        registerBtn = new QPushButton(Widget);
        registerBtn->setObjectName("registerBtn");

        horizontalLayout->addWidget(registerBtn);

        loginBtn = new QPushButton(Widget);
        loginBtn->setObjectName("loginBtn");

        horizontalLayout->addWidget(loginBtn);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        userLabel->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215: ", nullptr));
        passwordLabel->setText(QCoreApplication::translate("Widget", "\345\257\206\347\240\201: ", nullptr));
        logoutBtn->setText(QCoreApplication::translate("Widget", "\346\263\250\351\224\200", nullptr));
        registerBtn->setText(QCoreApplication::translate("Widget", "\346\263\250\345\206\214", nullptr));
        loginBtn->setText(QCoreApplication::translate("Widget", "\347\231\273\351\231\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
