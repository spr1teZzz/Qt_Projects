#include "Client.h"
#define PORT 8888
#define IP "192.168.5.94"
Client::Client(int uid,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    from_id = uid;
    //QString login_msg = "from:" + QString::number(from_id) + ",to:0";
    connect(loginWidget::socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
    connect(ui.pushButtonSend, SIGNAL(clicked()), this, SLOT(sendMsg()));
    //鼠标移到发送按钮变成#D2D2D2 按住为#C6C6C6
    ui.pushButtonSend->setStyleSheet("QPushButton{background-color:#E9E9E9;border-radius: 2px;border:none;font-weight:bold;color:#07CEBB;font-size:12px;}"
        "QPushButton:hover{background-color:#D2D2D2 ;}"
        "QPushButton:pressed{background-color:#C6C6C6;}");
    ui.textEditSend->setStyleSheet("background-color:#F5F5F5;border:none;");
    
    //未点击发送用户时,不能点击发送框和发送按钮隐藏
    ui.textEditSend->setReadOnly(true);
    ui.pushButtonSend->hide();
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

void Client::openSend()
{    
    //点击发送用户时,发送框可用和发送按钮显示
    ui.textEditSend->setReadOnly(false);
    ui.pushButtonSend->show();

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