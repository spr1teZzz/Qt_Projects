/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidgetClass
{
public:
    QLabel *label_img;
    QLineEdit *LineEdit_username;
    QLineEdit *LineEdit_password;
    QLabel *label_userId;
    QLabel *label_password;
    QPushButton *btn_login;

    void setupUi(QWidget *LoginWidgetClass)
    {
        if (LoginWidgetClass->objectName().isEmpty())
            LoginWidgetClass->setObjectName(QStringLiteral("LoginWidgetClass"));
        LoginWidgetClass->resize(280, 340);
        label_img = new QLabel(LoginWidgetClass);
        label_img->setObjectName(QStringLiteral("label_img"));
        label_img->setGeometry(QRect(100, 60, 80, 80));
        LineEdit_username = new QLineEdit(LoginWidgetClass);
        LineEdit_username->setObjectName(QStringLiteral("LineEdit_username"));
        LineEdit_username->setGeometry(QRect(85, 190, 145, 25));
        LineEdit_password = new QLineEdit(LoginWidgetClass);
        LineEdit_password->setObjectName(QStringLiteral("LineEdit_password"));
        LineEdit_password->setGeometry(QRect(85, 220, 145, 25));
        label_userId = new QLabel(LoginWidgetClass);
        label_userId->setObjectName(QStringLiteral("label_userId"));
        label_userId->setGeometry(QRect(40, 187, 40, 30));
        label_password = new QLabel(LoginWidgetClass);
        label_password->setObjectName(QStringLiteral("label_password"));
        label_password->setGeometry(QRect(40, 217, 40, 30));
        btn_login = new QPushButton(LoginWidgetClass);
        btn_login->setObjectName(QStringLiteral("btn_login"));
        btn_login->setGeometry(QRect(40, 280, 200, 35));

        retranslateUi(LoginWidgetClass);

        QMetaObject::connectSlotsByName(LoginWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *LoginWidgetClass)
    {
        LoginWidgetClass->setWindowTitle(QApplication::translate("LoginWidgetClass", "LoginWidget", 0));
        label_img->setText(QString());
        label_userId->setText(QApplication::translate("LoginWidgetClass", "\350\264\246 \345\217\267", 0));
        label_password->setText(QApplication::translate("LoginWidgetClass", "\345\257\206 \347\240\201", 0));
        btn_login->setText(QApplication::translate("LoginWidgetClass", "\347\231\273 \345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginWidgetClass: public Ui_LoginWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
