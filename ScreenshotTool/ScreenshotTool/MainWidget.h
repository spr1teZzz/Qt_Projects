#pragma once

#include <QtWidgets/QWidget>
#include <QKeyEvent>
#include "colorwidget.h"
#include "ui_MainWidget.h"
#include "screenwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidgetClass; };
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private slots :
    void Btn_start_clicked();
    void keyPressEvent(QKeyEvent* event);
private:
    Ui::MainWidgetClass *ui;
};
