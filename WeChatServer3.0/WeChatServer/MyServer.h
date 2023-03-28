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
	MySocket* mysocket;//socket指针
	QString str_inf;//ip端口字符串
	int threadIndex;//所在线程ID
    int uid;//socket连接的uid
};


class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject* parent = nullptr);
    ~MyServer();
    void SetThread(int num);//设置线程数
    int GetMinLoadThread();//获取当前最少负载的线程ID

    SocketHelper* sockethelper;//socket创建辅助对象
    QList<MyThread*> list_thread;//线程列表
    QList<SocketInformation> list_information;//socket信息列表

    Widget *widget;
private:
    void incomingConnection(qintptr socketDescriptor);
public slots:
    void AddInf(MySocket* mysocket, int index,int uid);//添加信息
    void RemoveInf(MySocket* mysocket);//移除信息
    void Foward(int fid, int tid,QString msg); //服务器转发消息
};
