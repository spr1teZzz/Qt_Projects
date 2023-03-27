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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetClass
{
public:
    QTextEdit *textEdit_Send;
    QTextEdit *textEdit_Recv;
    QLabel *label;
    QLabel *label_2;
    QPushButton *Btn_ClearRecv;
    QPushButton *Btn_SendMsg;
    QListView *listView_User;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_IP;
    QLabel *label_6;
    QLineEdit *lineEdit_Port;
    QLabel *label_7;
    QSpinBox *spinBox;
    QComboBox *comboBox;
    QLabel *label_8;
    QPushButton *Btn_Disconnect;
    QPushButton *Btn_Start;
    QPushButton *Btn_ClearSend;

    void setupUi(QWidget *WidgetClass)
    {
        if (WidgetClass->objectName().isEmpty())
            WidgetClass->setObjectName(QStringLiteral("WidgetClass"));
        WidgetClass->resize(797, 700);
        textEdit_Send = new QTextEdit(WidgetClass);
        textEdit_Send->setObjectName(QStringLiteral("textEdit_Send"));
        textEdit_Send->setGeometry(QRect(270, 420, 531, 211));
        textEdit_Recv = new QTextEdit(WidgetClass);
        textEdit_Recv->setObjectName(QStringLiteral("textEdit_Recv"));
        textEdit_Recv->setGeometry(QRect(260, 30, 531, 271));
        label = new QLabel(WidgetClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(270, 400, 91, 16));
        label_2 = new QLabel(WidgetClass);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 10, 54, 12));
        Btn_ClearRecv = new QPushButton(WidgetClass);
        Btn_ClearRecv->setObjectName(QStringLiteral("Btn_ClearRecv"));
        Btn_ClearRecv->setGeometry(QRect(710, 310, 81, 31));
        Btn_SendMsg = new QPushButton(WidgetClass);
        Btn_SendMsg->setObjectName(QStringLiteral("Btn_SendMsg"));
        Btn_SendMsg->setGeometry(QRect(700, 650, 75, 31));
        listView_User = new QListView(WidgetClass);
        listView_User->setObjectName(QStringLiteral("listView_User"));
        listView_User->setGeometry(QRect(10, 30, 231, 271));
        label_3 = new QLabel(WidgetClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 81, 16));
        label_4 = new QLabel(WidgetClass);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 380, 54, 12));
        label_5 = new QLabel(WidgetClass);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 410, 54, 21));
        lineEdit_IP = new QLineEdit(WidgetClass);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(100, 410, 131, 20));
        label_6 = new QLabel(WidgetClass);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 460, 61, 21));
        lineEdit_Port = new QLineEdit(WidgetClass);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setGeometry(QRect(100, 460, 131, 20));
        label_7 = new QLabel(WidgetClass);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(40, 510, 91, 21));
        spinBox = new QSpinBox(WidgetClass);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(130, 510, 42, 22));
        spinBox->setMinimum(1);
        spinBox->setValue(5);
        comboBox = new QComboBox(WidgetClass);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(330, 340, 261, 31));
        comboBox->setMaxVisibleItems(10);
        label_8 = new QLabel(WidgetClass);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(270, 340, 51, 31));
        Btn_Disconnect = new QPushButton(WidgetClass);
        Btn_Disconnect->setObjectName(QStringLiteral("Btn_Disconnect"));
        Btn_Disconnect->setGeometry(QRect(710, 360, 81, 31));
        Btn_Start = new QPushButton(WidgetClass);
        Btn_Start->setObjectName(QStringLiteral("Btn_Start"));
        Btn_Start->setGeometry(QRect(40, 570, 181, 31));
        Btn_ClearSend = new QPushButton(WidgetClass);
        Btn_ClearSend->setObjectName(QStringLiteral("Btn_ClearSend"));
        Btn_ClearSend->setGeometry(QRect(620, 650, 75, 31));

        retranslateUi(WidgetClass);

        comboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WidgetClass);
    } // setupUi

    void retranslateUi(QWidget *WidgetClass)
    {
        WidgetClass->setWindowTitle(QApplication::translate("WidgetClass", "Widget", 0));
        label->setText(QApplication::translate("WidgetClass", "\346\266\210\346\201\257\345\217\221\351\200\201\357\274\232", 0));
        label_2->setText(QApplication::translate("WidgetClass", "\346\216\245\346\224\266\347\253\257\357\274\232", 0));
        Btn_ClearRecv->setText(QApplication::translate("WidgetClass", "\346\270\205\347\251\272\346\216\245\346\224\266", 0));
        Btn_SendMsg->setText(QApplication::translate("WidgetClass", "\345\217\221\351\200\201", 0));
        label_3->setText(QApplication::translate("WidgetClass", "\350\277\236\346\216\245\347\224\250\346\210\267\344\277\241\346\201\257\357\274\232", 0));
        label_4->setText(QApplication::translate("WidgetClass", "\350\256\276\347\275\256\357\274\232", 0));
        label_5->setText(QApplication::translate("WidgetClass", "\344\270\273\346\234\272IP\357\274\232", 0));
        label_6->setText(QApplication::translate("WidgetClass", "\346\234\254\345\234\260\347\253\257\345\217\243\357\274\232", 0));
        label_7->setText(QApplication::translate("WidgetClass", "\350\256\276\347\275\256\347\272\277\347\250\213\346\225\260\357\274\232", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("WidgetClass", "\346\211\200\346\234\211\350\277\236\346\216\245", 0)
        );
        comboBox->setCurrentText(QApplication::translate("WidgetClass", "\346\211\200\346\234\211\350\277\236\346\216\245", 0));
        label_8->setText(QApplication::translate("WidgetClass", "\346\216\245\346\224\266\347\253\257\357\274\232", 0));
        Btn_Disconnect->setText(QApplication::translate("WidgetClass", "\346\226\255\345\274\200\350\277\236\346\216\245", 0));
        Btn_Start->setText(QApplication::translate("WidgetClass", "\345\274\200\345\220\257", 0));
        Btn_ClearSend->setText(QApplication::translate("WidgetClass", "\346\270\205\347\251\272\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class WidgetClass: public Ui_WidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
