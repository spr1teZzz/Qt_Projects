#pragma once

#include <QThread>
class MyServer;
class MySocket;

//Socket创建辅助类
class SocketHelper :public QObject
{
    Q_OBJECT
public:
    explicit SocketHelper(QObject* parent = nullptr);
    MyServer* myserver;
public slots:
    void CreateSocket(qintptr socketDescriptor, int index);//创建socket
signals:
    void Create(qintptr socketDescriptor, int index);//创建
    void AddList(MySocket* tcpsocket, int index);//添加信息
    void RemoveList(MySocket* tcpsocket);//移除信息
};

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit  MyThread(QObject* parent);
    ~MyThread() override;
public:
    MyServer* myserver;
    SocketHelper* sockethelper;
    int ThreadLoad;
    void run() override;
};



