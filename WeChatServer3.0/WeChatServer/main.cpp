#include "Widget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");//����"GBK",���ִ�Сд
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
