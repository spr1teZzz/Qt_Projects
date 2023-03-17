#include "Server.h"

Server::Server(int port,QObject *parent)
	: QTcpServer(parent)
{
	listen(QHostAddress::Any, port);//����
}

Server::~Server()
{
}
void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"*****connect coming*****";
    TcpClientSocket* tcpclientsocket = new TcpClientSocket(this);//ֻҪ���µ����Ӿ�����һ���µ�ͨ���׽���
    //���´�����ͨ���׽���������ָ��Ϊ����socketdescriptor
    tcpclientsocket->setSocketDescriptor(socketDescriptor);
    
    //������׽�����ӽ��ͻ����׽����б���
    socket_map.insert(tcpclientsocket, 0);
    //���յ�tcpclientsocket���͹����ĸ��½�����ź�
    connect(tcpclientsocket, &TcpClientSocket::updateserver, this, &Server::slotupdateserver);
    connect(tcpclientsocket, &TcpClientSocket::connectsuccess, this, &Server::connectoperate);
    connect(tcpclientsocket, &TcpClientSocket::clientdisconnected, this, &Server::slotclientdisconnect);
}

void Server::slotupdateserver(QString msg, int fid,int tid)
{
    //������źŷ��͸�����
    emit showMsgServer(msg, fid,tid);
    //�׽����б����ҵ���Ҫ���յ��׽��� Ȼ����д��װ��Ϣд���׽������ӵĿͻ���
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
    //�Ͽ����Ӳ���
    QMap<TcpClientSocket*, int>::Iterator iter;
    for (iter = socket_map.begin(); iter != socket_map.end(); ++iter)
    {
        if (iter.key()->socketDescriptor() == descriptor)
        {
            
            qDebug() << "quit :"+QString::number(iter.value());
            emit quit(iter.value());
            socket_map.erase(iter);//����пͻ��˶Ͽ����ӣ� �ͽ��б��е��׽���ɾ��
            return;
        }
    }
}

void Server::connectoperate(int uid, qintptr descriptor)
{
    //������źŷ��͸�����
    emit loginserver(uid);//tidΪ0���͸�����
    //�׽����б����ҵ���Ҫ���յ��׽���
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