#include "MyThread.h"
#include "Widget.h"
#include "MyServer.h"
#include "MySocket.h"

#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
MyThread::MyThread(QObject *parent)
{
	this->myserver = static_cast<MyServer*>(parent);
	this->sockethelper = nullptr;
	this->ThreadLoad = 0;
}

MyThread::~MyThread()
{
	if (this->sockethelper != nullptr)
	{
		sockethelper->disconnect();
		delete this->sockethelper;//释放sockethelper
	}
}

void MyThread::run()
{
	//在线程内创建对象，槽函数在这个线程中执行
	this->sockethelper = new SocketHelper(this->myserver);
	connect(sockethelper, &SocketHelper::Create, sockethelper, &SocketHelper::CreateSocket);
	connect(sockethelper, &SocketHelper::AddList, myserver, &MyServer::AddInf);
	connect(sockethelper, &SocketHelper::RemoveList, myserver, &MyServer::RemoveInf);

	exec();
}



SocketHelper::SocketHelper(QObject* parent)
{
	this->myserver = static_cast<MyServer*>(parent);
}

void SocketHelper::CreateSocket(qintptr socketDescriptor, int index)
{
    qDebug() << "subThread:" << QThread::currentThreadId();

    MySocket* tcpsocket = new MySocket(this->myserver);
    tcpsocket->sockethelper = this;
    //初始化socket
    tcpsocket->setSocketDescriptor(socketDescriptor);
    //发送到UI线程记录信息
    emit AddList(tcpsocket, index);//

    if (index != -1)//非UI线程时
    {
        //负载+1
        myserver->list_thread[index]->ThreadLoad += 1;//负载+1
        //关联释放socket,非UI线程需要阻塞
        connect(tcpsocket, &MySocket::DeleteSocket, tcpsocket, &MySocket::deal_disconnect, Qt::ConnectionType::BlockingQueuedConnection);
    }
    else
    {
        connect(tcpsocket, &MySocket::DeleteSocket, tcpsocket, &MySocket::deal_disconnect, Qt::ConnectionType::AutoConnection);
    }

    //关联显示消息
    connect(tcpsocket, &MySocket::AddMessage, myserver->widget, &Widget::on_add_serverMessage);
    //发送消息
    connect(tcpsocket, &MySocket::WriteMessage, tcpsocket, &MySocket::deal_write);
    //关联接收数据
    connect(tcpsocket, &MySocket::readyRead, tcpsocket, &MySocket::deal_readyRead);
    //关联断开连接时的处理槽
    connect(tcpsocket, &MySocket::disconnected, tcpsocket, &MySocket::deal_disconnect);

    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    QString message = QString("[%1:%2] 已连接").arg(ip).arg(port);
    //发送到UI线程显示
    emit tcpsocket->AddMessage(message);
}