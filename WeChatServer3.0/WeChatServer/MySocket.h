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
    void deal_readyRead();//��ȡ���ݲۺ���
    void deal_disconnect();//�Ͽ����Ӳۺ���
    void deal_write(QByteArray ba);//д�����ݲۺ���
signals:
    void AddMessage(QString data);//���͸�UI��ʾ
    void WriteMessage(QByteArray ba);//UI���͹�������
    void DeleteSocket();//�����ر�socket
};
