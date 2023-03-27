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
		delete this->sockethelper;//�ͷ�sockethelper
	}
}

void MyThread::run()
{
	//���߳��ڴ������󣬲ۺ���������߳���ִ��
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
    //��ʼ��socket
    tcpsocket->setSocketDescriptor(socketDescriptor);
    //���͵�UI�̼߳�¼��Ϣ
    emit AddList(tcpsocket, index);//

    if (index != -1)//��UI�߳�ʱ
    {
        //����+1
        myserver->list_thread[index]->ThreadLoad += 1;//����+1
        //�����ͷ�socket,��UI�߳���Ҫ����
        connect(tcpsocket, &MySocket::DeleteSocket, tcpsocket, &MySocket::deal_disconnect, Qt::ConnectionType::BlockingQueuedConnection);
    }
    else
    {
        connect(tcpsocket, &MySocket::DeleteSocket, tcpsocket, &MySocket::deal_disconnect, Qt::ConnectionType::AutoConnection);
    }

    //������ʾ��Ϣ
    connect(tcpsocket, &MySocket::AddMessage, myserver->widget, &Widget::on_add_serverMessage);
    //������Ϣ
    connect(tcpsocket, &MySocket::WriteMessage, tcpsocket, &MySocket::deal_write);
    //������������
    connect(tcpsocket, &MySocket::readyRead, tcpsocket, &MySocket::deal_readyRead);
    //�����Ͽ�����ʱ�Ĵ����
    connect(tcpsocket, &MySocket::disconnected, tcpsocket, &MySocket::deal_disconnect);

    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    QString message = QString("[%1:%2] ������").arg(ip).arg(port);
    //���͵�UI�߳���ʾ
    emit tcpsocket->AddMessage(message);
}