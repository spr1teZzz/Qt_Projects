/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetClass
{
public:
    QPushButton *pushButtonBegin;
    QLineEdit *lineEditPort;
    QWidget *widgetUserInfo;
    QTextEdit *textEdit;

    void setupUi(QWidget *WidgetClass)
    {
        if (WidgetClass->objectName().isEmpty())
            WidgetClass->setObjectName(QStringLiteral("WidgetClass"));
        WidgetClass->resize(800, 600);
        pushButtonBegin = new QPushButton(WidgetClass);
        pushButtonBegin->setObjectName(QStringLiteral("pushButtonBegin"));
        pushButtonBegin->setGeometry(QRect(300, 530, 75, 41));
        lineEditPort = new QLineEdit(WidgetClass);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));
        lineEditPort->setGeometry(QRect(90, 530, 140, 40));
        widgetUserInfo = new QWidget(WidgetClass);
        widgetUserInfo->setObjectName(QStringLiteral("widgetUserInfo"));
        widgetUserInfo->setGeometry(QRect(0, 0, 450, 530));
        textEdit = new QTextEdit(WidgetClass);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(450, 0, 350, 600));

        retranslateUi(WidgetClass);

        QMetaObject::connectSlotsByName(WidgetClass);
    } // setupUi

    void retranslateUi(QWidget *WidgetClass)
    {
        WidgetClass->setWindowTitle(QApplication::translate("WidgetClass", "Widget", 0));
        pushButtonBegin->setText(QApplication::translate("WidgetClass", "\345\220\257\345\212\250\346\234\215\345\212\241", 0));
    } // retranslateUi

};

namespace Ui {
    class WidgetClass: public Ui_WidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
