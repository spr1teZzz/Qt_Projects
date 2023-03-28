#pragma once

#include <QThread>
class MyServer;
class MySocket;

//Socket����������
class SocketHelper :public QObject
{
    Q_OBJECT
public:
    explicit SocketHelper(QObject* parent = nullptr);
    MyServer* myserver;
public slots:
    void CreateSocket(qintptr socketDescriptor, int index);//����socket
signals:
    void Create(qintptr socketDescriptor, int index);//����
    void AddList(MySocket* tcpsocket, int index,int uid);//�����Ϣ
    void RemoveList(MySocket* tcpsocket);//�Ƴ���Ϣ
    void UserCommunication(int fid, int tid, QString msg);//�û���ͨ��
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



