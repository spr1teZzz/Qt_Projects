#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QObject>
#include <QHostAddress>
#include "TcpClientSocket.h"
#include <QMap>
#include <QString>
class Server  : public QTcpServer
{
	Q_OBJECT

public:
	 Server(int port=0,QObject *parent = nullptr);
	~Server();
private:
	QMap<TcpClientSocket*, int> socket_map;
protected:
	void incomingConnection(qintptr socketDescriptor);
protected slots:
	void slotupdateserver(QString, int,int);//��������tcpclient���������ź�
	void slotclientdisconnect(qintptr);
	void connectoperate(int, qintptr);//�ͻ������ӳɹ��󣬴����͹�����uid
signals:
	void showMsgServer(QString,int,int);//�����źŸ����棬�ý��������Ϣ
	void loginserver(int);	//�����źŸ������û���¼
	void quit(int);//�����źŸ������û��˳�
};
