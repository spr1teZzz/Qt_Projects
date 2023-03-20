#pragma once

#include <QWidget>
#include "ui_Client.h"
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QDebug>
class Client : public QWidget
{
	Q_OBJECT

public:
	Client(int uid,QWidget *parent = nullptr);
	~Client();
	void changeToId(int fid,int tid) //ÐÞ¸Ä·¢ËÍÈË
	{
		to_id = tid;
		from_id = fid;
	}
private slots:
	void sendMsg();
	void recvMsg();
signals:
	void sendMsgSuccess(QString msg);
	void recvMsgSuccess(QString msg);
private:
	Ui::ClientClass ui;
	QTcpSocket* socket;
	int to_id = 0;
	int from_id = 0;
};
