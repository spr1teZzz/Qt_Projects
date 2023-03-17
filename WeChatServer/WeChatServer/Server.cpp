#include "Server.h"

Server::Server(int port,QObject *parent)
	: QTcpServer(parent)
{
	listen(QHostAddress::Any, port);//监听
}

Server::~Server()
{
}
void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"*****connect coming*****";
    TcpClientSocket* tcpclientsocket = new TcpClientSocket(this);//只要有新的连接就生成一个新的通信套接字
    //将新创建的通信套接字描述符指定为参数socketdescriptor
    tcpclientsocket->setSocketDescriptor(socketDescriptor);
    
    //将这个套接字添加进客户端套接字列表中
    socket_map.insert(tcpclientsocket, 0);
    //接收到tcpclientsocket发送过来的更新界面的信号
    connect(tcpclientsocket, &TcpClientSocket::updateserver, this, &Server::slotupdateserver);
    connect(tcpclientsocket, &TcpClientSocket::connectsuccess, this, &Server::connectoperate);
    connect(tcpclientsocket, &TcpClientSocket::clientdisconnected, this, &Server::slotclientdisconnect);
}

void Server::slotupdateserver(QString msg, int fid,int tid)
{
    //将这个信号发送给界面
    emit showMsgServer(msg, fid,tid);
    //套接字列表中找到需要接收的套接字 然后再写封装信息写给套接字链接的客户端
    QMap<TcpClientSocket*, int>::Iterator iter;
    for (iter = socket_map.begin(); iter != socket_map.end(); ++iter)
    {
        if (iter.value() == tid)
        {
            QString data= "type=2&from=" + QString::number(fid) + "&to=" + QString::number(tid) + "&" + msg;
            iter.key()->write(data.toUtf8().data());
            qDebug() << "send msg:" + data;
            return;
        }
    }
    
}

void Server::slotclientdisconnect(qintptr descriptor)
{
    //断开连接操作
    QMap<TcpClientSocket*, int>::Iterator iter;
    for (iter = socket_map.begin(); iter != socket_map.end(); ++iter)
    {
        if (iter.key()->socketDescriptor() == descriptor)
        {
            
            qDebug() << "quit :"+QString::number(iter.value());
            emit quit(iter.value());
            socket_map.erase(iter);//如果有客户端断开连接， 就将列表中的套接字删除
            return;
        }
    }
}

void Server::connectoperate(int uid, qintptr descriptor)
{
    //将这个信号发送给界面
    emit loginserver(uid);//tid为0发送给界面
    //套接字列表中找到需要接收的套接字
    QMap<TcpClientSocket*, int>::Iterator iter;
    qDebug() << "go to:connectoperate";
    for (iter = socket_map.begin(); iter != socket_map.end(); ++iter)
    {
        if (iter.key()->socketDescriptor() == descriptor)
        {
            iter.value() = uid;
            qDebug() << QString::number(uid) + "login success!";
            break;
        }
    }
}