/********************************************************************************
** Form generated from reading UI file 'show_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_WIDGET_H
#define UI_SHOW_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Show
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *userInfoTableWidget;

    void setupUi(QWidget *Show)
    {
        if (Show->objectName().isEmpty())
            Show->setObjectName("Show");
        Show->resize(456, 255);
        verticalLayout = new QVBoxLayout(Show);
        verticalLayout->setObjectName("verticalLayout");
        userInfoTableWidget = new QTableWidget(Show);
        userInfoTableWidget->setObjectName("userInfoTableWidget");

        verticalLayout->addWidget(userInfoTableWidget);


        retranslateUi(Show);

        QMetaObject::connectSlotsByName(Show);
    } // setupUi

    void retranslateUi(QWidget *Show)
    {
        Show->setWindowTitle(QCoreApplication::translate("Show", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Show: public Ui_Show {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_WIDGET_H
