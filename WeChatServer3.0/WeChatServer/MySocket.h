#pragma once

#include <QTcpSocket>
#include "MyThread.h"
#include "MySocket.h"
#include "MyServer.h"
#include <QThread>
#include "Widget.h"


class MyServer;

class MySocket  : public QTcpSocket
{
	Q_OBJECT

public:
	MySocket(QObject *parent);
	~MySocket();
    MyServer* m_tcpServer;
    SocketHelper* sockethelper;
public slots:
    void deal_readyRead();//读取数据槽函数
    void deal_disconnect();//断开连接槽函数
    void deal_write(QByteArray ba);//写入数据槽函数
signals:
    void AddMessage(QString data);//发送给UI显示
    void WriteMessage(QByteArray ba);//UI发送过来数据
    void DeleteSocket();//主动关闭socket
};
