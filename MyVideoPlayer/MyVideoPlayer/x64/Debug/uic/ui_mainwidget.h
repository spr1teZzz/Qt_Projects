/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include <qvideowidget.h>
#include "playerslider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWidgetClass
{
public:
    QWidget *centralWidget;
    QPushButton *Btn_Last;
    QPushButton *Btn_StartAndStop;
    QPushButton *Btn_Next;
    PlayerSlider *slider_video;
    QPushButton *Btn_voiceIcon;
    QLabel *label_curTime;
    QPushButton *Btn_speed1;
    QPushButton *Btn_speed2;
    QPushButton *Btn_speed3;
    QPushButton *Btn_speed4;
    QLabel *label_maxTime;
    QLabel *label_3;
    QPushButton *Btn_speed5;
    QPushButton *Btn_Min;
    QPushButton *Btn_Max;
    QPushButton *Btn_Close;
    QVideoWidget *widget_video;
    QPushButton *Btn_loadFile;
    QSlider *slider_voice;
    QListWidget *listWidget;

    void setupUi(QMainWindow *MainWidgetClass)
    {
        if (MainWidgetClass->objectName().isEmpty())
            MainWidgetClass->setObjectName(QStringLiteral("MainWidgetClass"));
        MainWidgetClass->resize(900, 500);
        MainWidgetClass->setMinimumSize(QSize(900, 500));
        centralWidget = new QWidget(MainWidgetClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Btn_Last = new QPushButton(centralWidget);
        Btn_Last->setObjectName(QStringLiteral("Btn_Last"));
        Btn_Last->setGeometry(QRect(160, 460, 40, 40));
        Btn_StartAndStop = new QPushButton(centralWidget);
        Btn_StartAndStop->setObjectName(QStringLiteral("Btn_StartAndStop"));
        Btn_StartAndStop->setGeometry(QRect(200, 460, 40, 40));
        Btn_Next = new QPushButton(centralWidget);
        Btn_Next->setObjectName(QStringLiteral("Btn_Next"));
        Btn_Next->setGeometry(QRect(240, 460, 40, 40));
        slider_video = new PlayerSlider(centralWidget);
        slider_video->setObjectName(QStringLiteral("slider_video"));
        slider_video->setGeometry(QRect(10, 440, 390, 20));
        slider_video->setMouseTracking(true);
        slider_video->setOrientation(Qt::Horizontal);
        Btn_voiceIcon = new QPushButton(centralWidget);
        Btn_voiceIcon->setObjectName(QStringLiteral("Btn_voiceIcon"));
        Btn_voiceIcon->setGeometry(QRect(530, 440, 20, 20));
        label_curTime = new QLabel(centralWidget);
        label_curTime->setObjectName(QStringLiteral("label_curTime"));
        label_curTime->setGeometry(QRect(410, 440, 50, 20));
        Btn_speed1 = new QPushButton(centralWidget);
        Btn_speed1->setObjectName(QStringLiteral("Btn_speed1"));
        Btn_speed1->setGeometry(QRect(410, 470, 50, 20));
        Btn_speed2 = new QPushButton(centralWidget);
        Btn_speed2->setObjectName(QStringLiteral("Btn_speed2"));
        Btn_speed2->setGeometry(QRect(460, 470, 50, 20));
        Btn_speed3 = new QPushButton(centralWidget);
        Btn_speed3->setObjectName(QStringLiteral("Btn_speed3"));
        Btn_speed3->setGeometry(QRect(510, 470, 50, 20));
        Btn_speed4 = new QPushButton(centralWidget);
        Btn_speed4->setObjectName(QStringLiteral("Btn_speed4"));
        Btn_speed4->setGeometry(QRect(560, 470, 50, 20));
        label_maxTime = new QLabel(centralWidget);
        label_maxTime->setObjectName(QStringLiteral("label_maxTime"));
        label_maxTime->setGeometry(QRect(470, 440, 50, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(460, 440, 5, 20));
        Btn_speed5 = new QPushButton(centralWidget);
        Btn_speed5->setObjectName(QStringLiteral("Btn_speed5"));
        Btn_speed5->setGeometry(QRect(610, 470, 50, 20));
        Btn_Min = new QPushButton(centralWidget);
        Btn_Min->setObjectName(QStringLiteral("Btn_Min"));
        Btn_Min->setGeometry(QRect(810, 0, 30, 30));
        Btn_Max = new QPushButton(centralWidget);
        Btn_Max->setObjectName(QStringLiteral("Btn_Max"));
        Btn_Max->setGeometry(QRect(840, 0, 30, 30));
        Btn_Close = new QPushButton(centralWidget);
        Btn_Close->setObjectName(QStringLiteral("Btn_Close"));
        Btn_Close->setGeometry(QRect(870, 0, 30, 30));
        widget_video = new QVideoWidget(centralWidget);
        widget_video->setObjectName(QStringLiteral("widget_video"));
        widget_video->setGeometry(QRect(10, 30, 650, 400));
        Btn_loadFile = new QPushButton(centralWidget);
        Btn_loadFile->setObjectName(QStringLiteral("Btn_loadFile"));
        Btn_loadFile->setGeometry(QRect(280, 460, 40, 40));
        slider_voice = new QSlider(centralWidget);
        slider_voice->setObjectName(QStringLiteral("slider_voice"));
        slider_voice->setEnabled(true);
        slider_voice->setGeometry(QRect(560, 440, 100, 20));
        slider_voice->setMouseTracking(true);
        slider_voice->setOrientation(Qt::Horizontal);
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(660, 30, 240, 430));
        MainWidgetClass->setCentralWidget(centralWidget);

        retranslateUi(MainWidgetClass);

        QMetaObject::connectSlotsByName(MainWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWidgetClass)
    {
        MainWidgetClass->setWindowTitle(QApplication::translate("MainWidgetClass", "MainWidget", 0));
        Btn_Last->setText(QString());
        Btn_StartAndStop->setText(QString());
        Btn_Next->setText(QString());
        Btn_voiceIcon->setText(QString());
        label_curTime->setText(QApplication::translate("MainWidgetClass", "00:00:00", 0));
        Btn_speed1->setText(QApplication::translate("MainWidgetClass", "\303\227 0.5", 0));
        Btn_speed2->setText(QApplication::translate("MainWidgetClass", "\303\227 1.0", 0));
        Btn_speed3->setText(QApplication::translate("MainWidgetClass", "\303\227 1.2", 0));
        Btn_speed4->setText(QApplication::translate("MainWidgetClass", "\303\227 1.5", 0));
        label_maxTime->setText(QApplication::translate("MainWidgetClass", "00:00:00", 0));
        label_3->setText(QApplication::translate("MainWidgetClass", "/", 0));
        Btn_speed5->setText(QApplication::translate("MainWidgetClass", "\303\2272.0", 0));
        Btn_Min->setText(QString());
        Btn_Max->setText(QString());
        Btn_Close->setText(QString());
        Btn_loadFile->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWidgetClass: public Ui_MainWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
