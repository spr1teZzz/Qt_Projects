#include "mainwidget.h"

#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    // 设置UTF-8编码
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);

    MainWidget w;
    w.show();
    return a.exec();
}
