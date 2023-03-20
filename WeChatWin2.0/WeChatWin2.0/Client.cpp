#include "Client.h"
#define PORT 8888
#define IP "127.0.0.1"
Client::Client(int uid,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    //初始化socket
    //loginWidget::socket = new QTcpSocket(this);
    //loginWidget::socket->connectToHost(IP, PORT);
    
    //连接后发送一条信息进行登录 from:uid ,to:0;
    from_id = uid;
    //QString login_msg = "from:" + QString::number(from_id) + ",to:0";
    //socket->write(login_msg.toUtf8());
    connect(loginWidget::socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
    connect(ui.pushButtonSend, SIGNAL(clicked()), this, SLOT(sendMsg()));
    //鼠标移到发送按钮变成#D2D2D2 按住为#C6C6C6
    ui.pushButtonSend->setStyleSheet("QPushButton{background-color:#E9E9E9;border-radius: 2px;border:none;font-weight:bold;color:#07CEBB;font-size:12px;}"
        "QPushButton:hover{background-color:#D2D2D2 ;}"
        "QPushButton:pressed{background-color:#C6C6C6;}");
    ui.textEditSend->setStyleSheet("background-color:#F5F5F5;border:none;");
}

Client::~Client()
{

}

void Client::recvMsg()
{
    //处理连接后操作
    QByteArray arr = loginWidget::socket->readAll();
    //    arr.data();
    QString data = arr.data();
    qDebug() << "recvMsg:" + data;
    emit recvMsgSuccess(data);
}

void Client::sendMsg()
{
    //处理发送数据
    QString data = ui.textEditSend->toPlainText();
    QString fid_str = "type=2&from=" + QString::number(from_id);
    QString tid_str = "to=" + QString::number(to_id);
    data = fid_str + "&" + tid_str + "&" + data;
    loginWidget::socket->write(data.toUtf8());
    ui.textEditSend->setText("");
    //qDebug() << "click for send from:"<<from_id<<" to uid :"<<to_id;
    
    //发送信号 进行格式处理 带有from_id 和 to_id
    qDebug() << data;
    emit sendMsgSuccess(data);
    //数据库添加
}