#include "MySocket.h"


#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

MySocket::MySocket(QObject *parent)
{
	this->m_tcpServer = static_cast<MyServer*>(parent);
}

MySocket::~MySocket()
{
	qDebug() << "释放Socket,所在线程：" << QThread::currentThreadId();
}

void MySocket::deal_disconnect()
{
    MySocket* tcpsocket = static_cast<MySocket*>(sender());
    //断开socket
    tcpsocket->abort();
    //消息提示断开
    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    QString message = QString("[%1:%2] 已断开").arg(ip).arg(port);
    //发送到UI线程显示
    emit AddMessage(message);
    //断开所有信号连接
    tcpsocket->disconnect();
    //发送到UI线程移除信息
    emit this->sockethelper->RemoveList(tcpsocket);
    //释放
    tcpsocket->deleteLater();
}

void MySocket::deal_write(QByteArray ba)
{
    this->write(ba);
}

void MySocket::deal_readyRead()
{
    MySocket* tcpsocket = static_cast<MySocket*>(sender());
    //获取客户端IP地址,端口号
    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    //获取客户端发来的数据
    QByteArray ba = tcpsocket->readAll();
    QString data;
    data = QString::fromLocal8Bit(ba);
    //数据打包
    qDebug() << "读取数据线程：" << QThread::currentThreadId();
    data = QString("[%1：%2] \n%3").arg(ip).arg(port).arg(data);
    //发送到UI线程显示
    emit AddMessage(data);
}
