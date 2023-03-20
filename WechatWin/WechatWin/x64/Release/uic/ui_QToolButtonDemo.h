/********************************************************************************
** Form generated from reading UI file 'QToolButtonDemo.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTOOLBUTTONDEMO_H
#define UI_QTOOLBUTTONDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QToolButtonDemoClass
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QToolButton *tlbChat;
    QToolButton *tlbDebug;
    QToolButton *tlbParam;
    QToolButton *tlbLog;
    QToolButton *tlbExtern;
    QToolButton *tlbSearch;
    QToolButton *tlbChat_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_9;
    QWidget *page_2;
    QLabel *label_8;
    QWidget *page_3;
    QLabel *label_7;
    QWidget *page_4;
    QLabel *label_6;
    QWidget *page_5;
    QLabel *label_5;

    void setupUi(QWidget *QToolButtonDemoClass)
    {
        if (QToolButtonDemoClass->objectName().isEmpty())
            QToolButtonDemoClass->setObjectName(QStringLiteral("QToolButtonDemoClass"));
        QToolButtonDemoClass->resize(752, 481);
        layoutWidget = new QWidget(QToolButtonDemoClass);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 41, 241));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tlbChat = new QToolButton(layoutWidget);
        tlbChat->setObjectName(QStringLiteral("tlbChat"));
        tlbChat->setEnabled(true);
        tlbChat->setMinimumSize(QSize(45, 45));
        tlbChat->setMaximumSize(QSize(45, 45));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        tlbChat->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Image/main_help.png"), QSize(), QIcon::Normal, QIcon::Off);
        tlbChat->setIcon(icon);
        tlbChat->setIconSize(QSize(45, 45));
        tlbChat->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tlbChat);

        tlbDebug = new QToolButton(layoutWidget);
        tlbDebug->setObjectName(QStringLiteral("tlbDebug"));
        tlbDebug->setMinimumSize(QSize(45, 45));
        tlbDebug->setMaximumSize(QSize(45, 45));
        tlbDebug->setFont(font);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Image/main_person.png"), QSize(), QIcon::Normal, QIcon::Off);
        tlbDebug->setIcon(icon1);
        tlbDebug->setIconSize(QSize(45, 45));
        tlbDebug->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tlbDebug);

        tlbParam = new QToolButton(layoutWidget);
        tlbParam->setObjectName(QStringLiteral("tlbParam"));
        tlbParam->setMinimumSize(QSize(45, 45));
        tlbParam->setMaximumSize(QSize(45, 45));
        tlbParam->setFont(font);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Image/main_config.png"), QSize(), QIcon::Normal, QIcon::Off);
        tlbParam->setIcon(icon2);
        tlbParam->setIconSize(QSize(45, 45));
        tlbParam->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tlbParam);

        tlbLog = new QToolButton(layoutWidget);
        tlbLog->setObjectName(QStringLiteral("tlbLog"));
        tlbLog->setMinimumSize(QSize(45, 45));
        tlbLog->setMaximumSize(QSize(45, 45));
        tlbLog->setFont(font);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Image/main_about.png"), QSize(), QIcon::Normal, QIcon::Off);
        tlbLog->setIcon(icon3);
        tlbLog->setIconSize(QSize(45, 45));
        tlbLog->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tlbLog);

        tlbExtern = new QToolButton(layoutWidget);
        tlbExtern->setObjectName(QStringLiteral("tlbExtern"));
        tlbExtern->setMinimumSize(QSize(45, 45));
        tlbExtern->setMaximumSize(QSize(45, 45));
        tlbExtern->setFont(font);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Image/main_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        tlbExtern->setIcon(icon4);
        tlbExtern->setIconSize(QSize(45, 45));
        tlbExtern->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tlbExtern);

        tlbSearch = new QToolButton(layoutWidget);
        tlbSearch->setObjectName(QStringLiteral("tlbSearch"));
        tlbSearch->setEnabled(true);
        tlbSearch->setMinimumSize(QSize(45, 45));
        tlbSearch->setMaximumSize(QSize(45, 45));
        tlbSearch->setFont(font);
        tlbSearch->setIcon(icon);
        tlbSearch->setIconSize(QSize(45, 45));
        tlbSearch->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tlbSearch);

        tlbChat_2 = new QToolButton(layoutWidget);
        tlbChat_2->setObjectName(QStringLiteral("tlbChat_2"));
        tlbChat_2->setEnabled(true);
        tlbChat_2->setMinimumSize(QSize(45, 45));
        tlbChat_2->setMaximumSize(QSize(45, 45));
        tlbChat_2->setFont(font);
        tlbChat_2->setIcon(icon);
        tlbChat_2->setIconSize(QSize(45, 45));
        tlbChat_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tlbChat_2);

        stackedWidget = new QStackedWidget(QToolButtonDemoClass);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(40, 0, 721, 501));
        stackedWidget->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"	border:1px solid #242424;\n"
"	border-radius:0px;\n"
"	background:#484848;\n"
"}\n"
"\n"
"QToolButton\n"
"{\n"
"	border-style:none;\n"
"	border:1px solid #242424;\n"
"	color:#DCDCDC;\n"
"	padding:5px;\n"
"	min-height:15px;\n"
"	border-radius:5px;\n"
"	background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252);\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"QToolButton::menu-indicator\n"
"{\n"
"	image:None;\n"
"}\n"
"\n"
"QToolButton:checked\n"
"{\n"
"    background-color: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #FFCC33, stop:1 #FFCC33);\n"
"    color:#4D4D4D;\n"
"	border-radius:4px;\n"
"    border:1px solid #B8B6B6;\n"
"}\n"
"\n"
"QMenu \n"
"{\n"
"	 border-radius:4px;\n"
"	 background-color:rgb(89,87,87); \n"
"	 bo"
                        "rder: 3px solid rgb(235,110,36);                    \n"
"}\n"
"\n"
"QMenu::item \n"
"{          \n"
"     border-radius:4px;         \n"
"	 font-size: 9pt; \n"
"	 color: rgb(225,225,225); \n"
"	 border: 3px solid rgb(60,60,60);   \n"
"	 background-color:rgb(89,87,87);\n"
"	 padding:12px 12px;\n"
"	 margin:2px 2px;\n"
"}\n"
"QMenu::item:selected \n"
"{ \n"
"	border-radius:4px;\n"
"	background-color:rgb(235,110,36);\n"
"}\n"
"\n"
"/*QMenu::item:pressed \n"
"{\n"
"	background-color: qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #FFCC33, stop:1 #FFCC33);\n"
"    color:#4D4D4D;\n"
"	border-radius:4px;\n"
"    border:1px solid #B8B6B6;\n"
"}*/\n"
""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label_9 = new QLabel(page);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(230, 170, 121, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        label_9->setFont(font1);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        label_8 = new QLabel(page_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(230, 160, 121, 51));
        label_8->setFont(font1);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        label_7 = new QLabel(page_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(220, 170, 121, 51));
        label_7->setFont(font1);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        label_6 = new QLabel(page_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(250, 170, 121, 51));
        label_6->setFont(font1);
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        label_5 = new QLabel(page_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(250, 180, 121, 51));
        label_5->setFont(font1);
        stackedWidget->addWidget(page_5);

        retranslateUi(QToolButtonDemoClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QToolButtonDemoClass);
    } // setupUi

    void retranslateUi(QWidget *QToolButtonDemoClass)
    {
        QToolButtonDemoClass->setWindowTitle(QApplication::translate("QToolButtonDemoClass", "QToolButtonDemo", 0));
        tlbChat->setText(QString());
        tlbDebug->setText(QString());
        tlbParam->setText(QString());
        tlbLog->setText(QString());
        tlbExtern->setText(QString());
        tlbSearch->setText(QString());
        tlbChat_2->setText(QString());
        label_9->setText(QApplication::translate("QToolButtonDemoClass", "\347\250\213\345\272\217", 0));
        label_8->setText(QApplication::translate("QToolButtonDemoClass", "\350\260\203\350\257\225", 0));
        label_7->setText(QApplication::translate("QToolButtonDemoClass", "\345\217\202\346\225\260", 0));
        label_6->setText(QApplication::translate("QToolButtonDemoClass", "\346\227\245\345\277\227", 0));
        label_5->setText(QApplication::translate("QToolButtonDemoClass", "\346\213\223\345\261\225", 0));
    } // retranslateUi

};

namespace Ui {
    class QToolButtonDemoClass: public Ui_QToolButtonDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTOOLBUTTONDEMO_H
