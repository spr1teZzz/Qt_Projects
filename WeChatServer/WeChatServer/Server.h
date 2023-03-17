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
	void slotupdateserver(QString, int,int);//用来处理tcpclient发过来的信号
	void slotclientdisconnect(qintptr);
	void connectoperate(int, qintptr);//客户端连接成功后，处理发送过来的uid
signals:
	void showMsgServer(QString,int,int);//发送信号给界面，让界面更新信息
	void loginserver(int);	//发送信号给界面用户登录
	void quit(int);//发送信号给界面用户退出
};
