#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include "loginwidget.h"
int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    loginWidget lw;
    lw.show();
    MainWidget mw;
    //绑定登录按钮
    QObject::connect(&lw, &loginWidget::loginUser, &mw, &MainWidget::rcvLogin);
    return a.exec();
}
