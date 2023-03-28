#pragma once

#include <QTcpServer>
#include "MyThread.h"
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "mysocket.h"
#include "ui_Widget.h"
#include "Widget.h"
class Widget;
class MyServer;

class SocketInformation
{
public:
	MySocket* mysocket;//socketָ��
	QString str_inf;//ip�˿��ַ���
	int threadIndex;//�����߳�ID
    int uid;//socket���ӵ�uid
};


class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject* parent = nullptr);
    ~MyServer();
    void SetThread(int num);//�����߳���
    int GetMinLoadThread();//��ȡ��ǰ���ٸ��ص��߳�ID

    SocketHelper* sockethelper;//socket������������
    QList<MyThread*> list_thread;//�߳��б�
    QList<SocketInformation> list_information;//socket��Ϣ�б�

    Widget *widget;
private:
    void incomingConnection(qintptr socketDescriptor);
public slots:
    void AddInf(MySocket* mysocket, int index,int uid);//�����Ϣ
    void RemoveInf(MySocket* mysocket);//�Ƴ���Ϣ
    void Foward(int fid, int tid,QString msg); //������ת����Ϣ
};
