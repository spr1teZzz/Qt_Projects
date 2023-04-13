/********************************************************************************
** Form generated from reading UI file 'chatFrom.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATFROM_H
#define UI_CHATFROM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatFromClass
{
public:
    QLabel *label_image;
    QLabel *label_name;
    QLabel *label_msg;
    QLabel *label_date;
    QLabel *label_uid;

    void setupUi(QWidget *chatFromClass)
    {
        if (chatFromClass->objectName().isEmpty())
            chatFromClass->setObjectName(QStringLiteral("chatFromClass"));
        chatFromClass->resize(240, 70);
        label_image = new QLabel(chatFromClass);
        label_image->setObjectName(QStringLiteral("label_image"));
        label_image->setGeometry(QRect(15, 15, 40, 40));
        label_name = new QLabel(chatFromClass);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setGeometry(QRect(70, 17, 110, 15));
        label_msg = new QLabel(chatFromClass);
        label_msg->setObjectName(QStringLiteral("label_msg"));
        label_msg->setGeometry(QRect(70, 40, 120, 15));
        label_date = new QLabel(chatFromClass);
        label_date->setObjectName(QStringLiteral("label_date"));
        label_date->setGeometry(QRect(190, 10, 50, 15));
        label_uid = new QLabel(chatFromClass);
        label_uid->setObjectName(QStringLiteral("label_uid"));
        label_uid->setGeometry(QRect(190, 40, 55, 12));

        retranslateUi(chatFromClass);

        QMetaObject::connectSlotsByName(chatFromClass);
    } // setupUi

    void retranslateUi(QWidget *chatFromClass)
    {
        chatFromClass->setWindowTitle(QApplication::translate("chatFromClass", "chatFrom", 0));
        label_image->setText(QString());
        label_name->setText(QString());
        label_msg->setText(QString());
        label_date->setText(QString());
        label_uid->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class chatFromClass: public Ui_chatFromClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATFROM_H
