#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include "loginwidget.h"
#include "filemanager.h"
int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    //创建文件
    FileManager fm;
    LoginWidget lw;
    lw.show();
    MainWidget mw;
    //绑定登录按钮
    QObject::connect(&lw, &LoginWidget::loginUser, &mw, &MainWidget::rcvLogin);
    return a.exec();
}
