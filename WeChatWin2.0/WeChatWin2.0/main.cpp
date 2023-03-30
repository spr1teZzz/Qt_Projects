#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include "loginwidget.h"
int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");//����"GBK",���ִ�Сд
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    loginWidget lw;
    lw.show();
    MainWidget mw;
    //�󶨵�¼��ť
    QObject::connect(&lw, &loginWidget::loginUser, &mw, &MainWidget::rcvLogin);
    return a.exec();
}
