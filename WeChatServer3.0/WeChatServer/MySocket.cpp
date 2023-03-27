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
	qDebug() << "�ͷ�Socket,�����̣߳�" << QThread::currentThreadId();
}

void MySocket::deal_disconnect()
{
    MySocket* tcpsocket = static_cast<MySocket*>(sender());
    //�Ͽ�socket
    tcpsocket->abort();
    //��Ϣ��ʾ�Ͽ�
    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    QString message = QString("[%1:%2] �ѶϿ�").arg(ip).arg(port);
    //���͵�UI�߳���ʾ
    emit AddMessage(message);
    //�Ͽ������ź�����
    tcpsocket->disconnect();
    //���͵�UI�߳��Ƴ���Ϣ
    emit this->sockethelper->RemoveList(tcpsocket);
    //�ͷ�
    tcpsocket->deleteLater();
}

void MySocket::deal_write(QByteArray ba)
{
    this->write(ba);
}

void MySocket::deal_readyRead()
{
    MySocket* tcpsocket = static_cast<MySocket*>(sender());
    //��ȡ�ͻ���IP��ַ,�˿ں�
    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    //��ȡ�ͻ��˷���������
    QByteArray ba = tcpsocket->readAll();
    QString data;
    data = QString::fromLocal8Bit(ba);
    //���ݴ��
    qDebug() << "��ȡ�����̣߳�" << QThread::currentThreadId();
    data = QString("[%1��%2] \n%3").arg(ip).arg(port).arg(data);
    //���͵�UI�߳���ʾ
    emit AddMessage(data);
}
