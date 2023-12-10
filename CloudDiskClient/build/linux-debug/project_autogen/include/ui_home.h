/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *homeListWidget;
    QStackedWidget *stackedWidget;

    void setupUi(QWidget *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName("Home");
        Home->resize(800, 600);
        horizontalLayout = new QHBoxLayout(Home);
        horizontalLayout->setSpacing(9);
        horizontalLayout->setObjectName("horizontalLayout");
        homeListWidget = new QListWidget(Home);
        homeListWidget->setObjectName("homeListWidget");

        horizontalLayout->addWidget(homeListWidget);

        stackedWidget = new QStackedWidget(Home);
        stackedWidget->setObjectName("stackedWidget");

        horizontalLayout->addWidget(stackedWidget);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);

        retranslateUi(Home);

        stackedWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QWidget *Home)
    {
        Home->setWindowTitle(QCoreApplication::translate("Home", "home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
