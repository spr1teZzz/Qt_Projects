#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QWidget>
#include "ui_Widget.h"
#include "Server.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
   void openserver();
   void showMsg(QString msg, int fid, int tid);
   void addClient(int uid);
   void quitClient(int uid);
private:
    Ui::WidgetClass ui;
    Server *server;
    int port;
};
