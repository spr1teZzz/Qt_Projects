#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>
#include "loginwidget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "QToolButtonDemo.h"
#include "MainWindow.h"
#include "framelesswidget.h"
#include "TestDemo.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginWidget lg;
    //MainWidget w;
    MainWindow mw;
    //mw.show();

    lg.show();
    //�󶨵�¼��ť
    QObject::connect(&lg, &loginWidget::loginUser,&mw, &MainWindow::rcvLogin);
    QObject::connect(&mw, &MainWindow::closeLoginWindow, &lg, &loginWidget::loginWindowClose);

    return a.exec();
}
