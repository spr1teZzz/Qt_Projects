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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidgetClass
{
public:
    QWidget *widget_left;
    QPushButton *pushButton_userImage;
    QToolButton *toolButtonChat;
    QToolButton *toolButtonAddressBook;
    QToolButton *toolButtonCollect;
    QToolButton *toolButtonFile;
    QToolButton *toolButtonFriends;
    QToolButton *toolButtonLook;
    QToolButton *toolButtonSearch;
    QToolButton *toolButtonSettings;
    QToolButton *toolButtonPhone;
    QToolButton *toolButtonProgram;
    QWidget *widget;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonMax;
    QPushButton *pushButtonMin;
    QWidget *widget_search;
    QLineEdit *lineEditSearch;
    QPushButton *pushButtonAdd;
    QLabel *labelSearchIcon;
    QLabel *label_uid;
    QPushButton *pushButtonTop;
    QPushButton *pushButtonName;
    QStackedWidget *stackedWidget;
    QWidget *pageChat;
    QWidget *widgetChat;
    QListWidget *listWidget;
    QWidget *widgetToolBar;
    QPushButton *pushButtonExpression;
    QPushButton *pushButtonFile;
    QPushButton *pushButtonShot;
    QPushButton *pushButtonRecords;
    QListWidget *listWidgetShow;
    QWidget *pageAddressBook;
    QListView *listView_2;
    QWidget *pageCollect;
    QWidget *pageFile;
    QWidget *pageFriends;
    QWidget *pageLook;
    QWidget *pageSearch;
    QWidget *pagePhone;

    void setupUi(QWidget *MainWidgetClass)
    {
        if (MainWidgetClass->objectName().isEmpty())
            MainWidgetClass->setObjectName(QStringLiteral("MainWidgetClass"));
        MainWidgetClass->resize(1332, 916);
        widget_left = new QWidget(MainWidgetClass);
        widget_left->setObjectName(QStringLiteral("widget_left"));
        widget_left->setGeometry(QRect(-5, 0, 55, 720));
        pushButton_userImage = new QPushButton(widget_left);
        pushButton_userImage->setObjectName(QStringLiteral("pushButton_userImage"));
        pushButton_userImage->setGeometry(QRect(0, 30, 40, 40));
        toolButtonChat = new QToolButton(widget_left);
        toolButtonChat->setObjectName(QStringLiteral("toolButtonChat"));
        toolButtonChat->setGeometry(QRect(0, 120, 55, 40));
        toolButtonAddressBook = new QToolButton(widget_left);
        toolButtonAddressBook->setObjectName(QStringLiteral("toolButtonAddressBook"));
        toolButtonAddressBook->setGeometry(QRect(0, 160, 55, 40));
        toolButtonCollect = new QToolButton(widget_left);
        toolButtonCollect->setObjectName(QStringLiteral("toolButtonCollect"));
        toolButtonCollect->setGeometry(QRect(0, 200, 55, 40));
        toolButtonFile = new QToolButton(widget_left);
        toolButtonFile->setObjectName(QStringLiteral("toolButtonFile"));
        toolButtonFile->setGeometry(QRect(0, 240, 55, 40));
        toolButtonFriends = new QToolButton(widget_left);
        toolButtonFriends->setObjectName(QStringLiteral("toolButtonFriends"));
        toolButtonFriends->setGeometry(QRect(0, 280, 55, 40));
        toolButtonLook = new QToolButton(widget_left);
        toolButtonLook->setObjectName(QStringLiteral("toolButtonLook"));
        toolButtonLook->setGeometry(QRect(0, 320, 55, 40));
        toolButtonSearch = new QToolButton(widget_left);
        toolButtonSearch->setObjectName(QStringLiteral("toolButtonSearch"));
        toolButtonSearch->setGeometry(QRect(0, 360, 55, 40));
        toolButtonSettings = new QToolButton(widget_left);
        toolButtonSettings->setObjectName(QStringLiteral("toolButtonSettings"));
        toolButtonSettings->setGeometry(QRect(0, 670, 55, 40));
        toolButtonPhone = new QToolButton(widget_left);
        toolButtonPhone->setObjectName(QStringLiteral("toolButtonPhone"));
        toolButtonPhone->setGeometry(QRect(0, 630, 55, 40));
        toolButtonProgram = new QToolButton(widget_left);
        toolButtonProgram->setObjectName(QStringLiteral("toolButtonProgram"));
        toolButtonProgram->setGeometry(QRect(0, 590, 55, 40));
        widget = new QWidget(MainWidgetClass);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 0, 885, 70));
        pushButtonClose = new QPushButton(widget);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(855, 0, 30, 25));
        pushButtonClose->setBaseSize(QSize(30, 25));
        pushButtonMax = new QPushButton(widget);
        pushButtonMax->setObjectName(QStringLiteral("pushButtonMax"));
        pushButtonMax->setGeometry(QRect(825, 0, 30, 25));
        pushButtonMax->setBaseSize(QSize(30, 25));
        pushButtonMin = new QPushButton(widget);
        pushButtonMin->setObjectName(QStringLiteral("pushButtonMin"));
        pushButtonMin->setGeometry(QRect(795, 0, 30, 25));
        pushButtonMin->setBaseSize(QSize(30, 25));
        widget_search = new QWidget(widget);
        widget_search->setObjectName(QStringLiteral("widget_search"));
        widget_search->setGeometry(QRect(0, 0, 250, 70));
        lineEditSearch = new QLineEdit(widget_search);
        lineEditSearch->setObjectName(QStringLiteral("lineEditSearch"));
        lineEditSearch->setGeometry(QRect(35, 25, 165, 24));
        pushButtonAdd = new QPushButton(widget_search);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));
        pushButtonAdd->setGeometry(QRect(215, 25, 25, 25));
        labelSearchIcon = new QLabel(widget_search);
        labelSearchIcon->setObjectName(QStringLiteral("labelSearchIcon"));
        labelSearchIcon->setGeometry(QRect(15, 25, 20, 25));
        label_uid = new QLabel(widget_search);
        label_uid->setObjectName(QStringLiteral("label_uid"));
        label_uid->setGeometry(QRect(50, 10, 54, 12));
        pushButtonTop = new QPushButton(widget);
        pushButtonTop->setObjectName(QStringLiteral("pushButtonTop"));
        pushButtonTop->setGeometry(QRect(765, 0, 30, 25));
        pushButtonTop->setBaseSize(QSize(30, 25));
        pushButtonName = new QPushButton(widget);
        pushButtonName->setObjectName(QStringLiteral("pushButtonName"));
        pushButtonName->setGeometry(QRect(280, 20, 200, 30));
        stackedWidget = new QStackedWidget(MainWidgetClass);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(50, 70, 885, 650));
        pageChat = new QWidget();
        pageChat->setObjectName(QStringLiteral("pageChat"));
        widgetChat = new QWidget(pageChat);
        widgetChat->setObjectName(QStringLiteral("widgetChat"));
        widgetChat->setGeometry(QRect(0, 0, 250, 650));
        listWidget = new QListWidget(widgetChat);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 250, 650));
        listWidget->setStyleSheet(QStringLiteral(""));
        widgetToolBar = new QWidget(pageChat);
        widgetToolBar->setObjectName(QStringLiteral("widgetToolBar"));
        widgetToolBar->setGeometry(QRect(250, 450, 635, 40));
        pushButtonExpression = new QPushButton(widgetToolBar);
        pushButtonExpression->setObjectName(QStringLiteral("pushButtonExpression"));
        pushButtonExpression->setGeometry(QRect(30, 15, 20, 20));
        pushButtonFile = new QPushButton(widgetToolBar);
        pushButtonFile->setObjectName(QStringLiteral("pushButtonFile"));
        pushButtonFile->setGeometry(QRect(60, 15, 20, 20));
        pushButtonShot = new QPushButton(widgetToolBar);
        pushButtonShot->setObjectName(QStringLiteral("pushButtonShot"));
        pushButtonShot->setGeometry(QRect(90, 15, 20, 20));
        pushButtonRecords = new QPushButton(widgetToolBar);
        pushButtonRecords->setObjectName(QStringLiteral("pushButtonRecords"));
        pushButtonRecords->setGeometry(QRect(120, 15, 20, 20));
        listWidgetShow = new QListWidget(pageChat);
        listWidgetShow->setObjectName(QStringLiteral("listWidgetShow"));
        listWidgetShow->setGeometry(QRect(250, 0, 630, 450));
        stackedWidget->addWidget(pageChat);
        pageAddressBook = new QWidget();
        pageAddressBook->setObjectName(QStringLiteral("pageAddressBook"));
        listView_2 = new QListView(pageAddressBook);
        listView_2->setObjectName(QStringLiteral("listView_2"));
        listView_2->setGeometry(QRect(0, 0, 341, 831));
        stackedWidget->addWidget(pageAddressBook);
        pageCollect = new QWidget();
        pageCollect->setObjectName(QStringLiteral("pageCollect"));
        stackedWidget->addWidget(pageCollect);
        pageFile = new QWidget();
        pageFile->setObjectName(QStringLiteral("pageFile"));
        stackedWidget->addWidget(pageFile);
        pageFriends = new QWidget();
        pageFriends->setObjectName(QStringLiteral("pageFriends"));
        stackedWidget->addWidget(pageFriends);
        pageLook = new QWidget();
        pageLook->setObjectName(QStringLiteral("pageLook"));
        stackedWidget->addWidget(pageLook);
        pageSearch = new QWidget();
        pageSearch->setObjectName(QStringLiteral("pageSearch"));
        stackedWidget->addWidget(pageSearch);
        pagePhone = new QWidget();
        pagePhone->setObjectName(QStringLiteral("pagePhone"));
        stackedWidget->addWidget(pagePhone);

        retranslateUi(MainWidgetClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *MainWidgetClass)
    {
        MainWidgetClass->setWindowTitle(QApplication::translate("MainWidgetClass", "MainWidget", 0));
        pushButton_userImage->setText(QString());
        toolButtonChat->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonAddressBook->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonCollect->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonFile->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonFriends->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonLook->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonSearch->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonSettings->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonPhone->setText(QApplication::translate("MainWidgetClass", "...", 0));
        toolButtonProgram->setText(QApplication::translate("MainWidgetClass", "...", 0));
        pushButtonClose->setText(QApplication::translate("MainWidgetClass", "X", 0));
        pushButtonMax->setText(QApplication::translate("MainWidgetClass", "\345\217\243", 0));
        pushButtonMin->setText(QApplication::translate("MainWidgetClass", "-", 0));
        lineEditSearch->setPlaceholderText(QApplication::translate("MainWidgetClass", "\346\220\234\347\264\242", 0));
        pushButtonAdd->setText(QApplication::translate("MainWidgetClass", "+", 0));
        labelSearchIcon->setText(QString());
        label_uid->setText(QString());
        pushButtonTop->setText(QString());
        pushButtonName->setText(QString());
        pushButtonExpression->setText(QString());
        pushButtonFile->setText(QString());
        pushButtonShot->setText(QString());
        pushButtonRecords->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWidgetClass: public Ui_MainWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
