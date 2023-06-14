#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include "loginwidget.h"
#include "filemanager.h"
int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");//����"GBK",���ִ�Сд
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    //�����ļ�
    FileManager fm;
    LoginWidget lw;
    lw.show();
    MainWidget mw;
    //�󶨵�¼��ť
    QObject::connect(&lw, &LoginWidget::loginUser, &mw, &MainWidget::rcvLogin);
    return a.exec();
}
