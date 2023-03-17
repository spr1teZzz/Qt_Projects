#include "Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    port = 8888;
    connect(ui.pushButtonBegin, SIGNAL(clicked()), this, SLOT(openserver()));

}
Widget::~Widget()
{

}
void Widget::showMsg(QString msg, int fid, int tid)
{
    //显示信息
    QString showMsg = QString::number(fid) + "对" + QString::number(tid) + "说:" + msg;
    ui.textEdit->append(showMsg);
}

void Widget::addClient(int uid)
{
    //登录
    QString showMsg = QString::number(uid) + "已经登录!";
    ui.textEdit->append(showMsg);
}

void Widget::quitClient(int uid)
{
    //退出
    QString showMsg = QString::number(uid) + "已经退出!";
    ui.textEdit->append(showMsg);
}


void Widget::openserver()
{
    port = ui.lineEditPort->text().toInt();
    qDebug() << "*****server start port:"+QString::number(port)+"*****";
    server = new Server(port,this);
    ui.pushButtonBegin->setEnabled(false);
    connect(server, &Server::showMsgServer, this, &Widget::showMsg);
    connect(server, &Server::loginserver, this, &Widget::addClient);
    connect(server, &Server::quit, this, &Widget::quitClient);
}