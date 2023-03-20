#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include "loginwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginWidget lw;
    lw.show();
    MainWidget mw;
    //°ó¶¨µÇÂ¼°´Å¥
    QObject::connect(&lw, &loginWidget::loginUser, &mw, &MainWidget::rcvLogin);
    //QObject::connect(&mw, &MainWidget::closeLoginWindow, &lw, &loginWidget::loginWindowClose);


    return a.exec();
}
