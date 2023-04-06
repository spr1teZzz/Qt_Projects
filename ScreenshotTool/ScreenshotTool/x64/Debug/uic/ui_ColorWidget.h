/********************************************************************************
** Form generated from reading UI file 'ColorWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORWIDGET_H
#define UI_COLORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorWidgetClass
{
public:
    QLabel *label_Img;
    QLabel *label_Text;

    void setupUi(QWidget *ColorWidgetClass)
    {
        if (ColorWidgetClass->objectName().isEmpty())
            ColorWidgetClass->setObjectName(QStringLiteral("ColorWidgetClass"));
        ColorWidgetClass->resize(100, 100);
        label_Img = new QLabel(ColorWidgetClass);
        label_Img->setObjectName(QStringLiteral("label_Img"));
        label_Img->setGeometry(QRect(0, 0, 100, 50));
        label_Text = new QLabel(ColorWidgetClass);
        label_Text->setObjectName(QStringLiteral("label_Text"));
        label_Text->setGeometry(QRect(0, 50, 100, 50));

        retranslateUi(ColorWidgetClass);

        QMetaObject::connectSlotsByName(ColorWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *ColorWidgetClass)
    {
        ColorWidgetClass->setWindowTitle(QApplication::translate("ColorWidgetClass", "ColorWidget", 0));
        label_Img->setText(QString());
        label_Text->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ColorWidgetClass: public Ui_ColorWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORWIDGET_H
