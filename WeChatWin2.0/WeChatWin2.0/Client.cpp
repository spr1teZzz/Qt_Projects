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
    //����Ƶ����Ͱ�ť���#D2D2D2 ��סΪ#C6C6C6
    ui.pushButtonSend->setStyleSheet("QPushButton{background-color:#E9E9E9;border-radius: 2px;border:none;font-weight:bold;color:#07CEBB;font-size:12px;}"
        "QPushButton:hover{background-color:#D2D2D2 ;}"
        "QPushButton:pressed{background-color:#C6C6C6;}");
    ui.textEditSend->setStyleSheet("background-color:#F5F5F5;border:none;");
    
    //δ��������û�ʱ,���ܵ�����Ϳ�ͷ��Ͱ�ť����
    ui.textEditSend->setReadOnly(true);
    ui.pushButtonSend->hide();
}

Client::~Client()
{

}

void Client::recvMsg()
{
    //�������Ӻ����
    QByteArray arr = loginWidget::socket->readAll();
    //    arr.data();
    QString data = arr.data();
    qDebug() << "recvMsg:" + data;
    emit recvMsgSuccess(data);
}

void Client::openSend()
{    
    //��������û�ʱ,���Ϳ���úͷ��Ͱ�ť��ʾ
    ui.textEditSend->setReadOnly(false);
    ui.pushButtonSend->show();

}

void Client::sendMsg()
{
    //����������
    QString data = ui.textEditSend->toPlainText();
    QString fid_str = "type=2&from=" + QString::number(from_id);
    QString tid_str = "to=" + QString::number(to_id);
    data = fid_str + "&" + tid_str + "&" + data;
    loginWidget::socket->write(data.toUtf8());
    ui.textEditSend->setText("");
    //qDebug() << "click for send from:"<<from_id<<" to uid :"<<to_id;
    
    //�����ź� ���и�ʽ���� ����from_id �� to_id
    qDebug() << data;
    emit sendMsgSuccess(data);
    //���ݿ����
}