/********************************************************************************
** Form generated from reading UI file 'MainWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidgetClass
{
public:
    QPushButton *Btn_start;
    QPushButton *Btn_start_hide;

    void setupUi(QWidget *MainWidgetClass)
    {
        if (MainWidgetClass->objectName().isEmpty())
            MainWidgetClass->setObjectName(QStringLiteral("MainWidgetClass"));
        MainWidgetClass->resize(214, 127);
        Btn_start = new QPushButton(MainWidgetClass);
        Btn_start->setObjectName(QStringLiteral("Btn_start"));
        Btn_start->setGeometry(QRect(10, 30, 91, 51));
        Btn_start_hide = new QPushButton(MainWidgetClass);
        Btn_start_hide->setObjectName(QStringLiteral("Btn_start_hide"));
        Btn_start_hide->setGeometry(QRect(110, 30, 91, 51));

        retranslateUi(MainWidgetClass);

        QMetaObject::connectSlotsByName(MainWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *MainWidgetClass)
    {
        MainWidgetClass->setWindowTitle(QApplication::translate("MainWidgetClass", "MainWidget", 0));
        Btn_start->setText(QApplication::translate("MainWidgetClass", "\346\210\252\345\233\276", 0));
        Btn_start_hide->setText(QApplication::translate("MainWidgetClass", "\351\232\220\350\227\217\347\252\227\345\217\243\346\210\252\345\233\276", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWidgetClass: public Ui_MainWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
