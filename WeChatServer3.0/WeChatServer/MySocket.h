#pragma once

#include <QTcpSocket>
#include "MyThread.h"
#include "MySocket.h"
#include "MyServer.h"
#include <QThread>
#include "Widget.h"
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QTextCodec>
#include <QMap>
#include <QList>
#include <QFile>
#include <QDir>
class MyServer;

class MySocket  : public QTcpSocket
{
	Q_OBJECT

public:
	MySocket(QObject *parent);
	~MySocket();
    MyServer* m_tcpServer;
    SocketHelper* sockethelper;
    void deal_login(QStringList list);//
    void deal_chat(QStringList list);//
	void deal_remindData(QByteArray data);
	void deal_chat(int fid, int tid, QString data);
	enum FILETYPE {
		FILE,
		IMAGE,
		TEXT,
		OTHERDATA
	};
public slots:
    void deal_readyRead();//��ȡ���ݲۺ���
    void deal_disconnect();//�Ͽ����Ӳۺ���
    void deal_write(QByteArray ba);//д�����ݲۺ���
signals:
    void AddMessage(QString data);//���͸�UI��ʾ
    void WriteMessage(QByteArray ba);//UI���͹�������
    void DeleteSocket();//�����ر�socket
private:
	QString fileName;//��ǰ�ļ���
	FILETYPE fileType;//��ǰ�ļ�����
	int fileSize;//��ǰ�ļ���С
	int recvSize;//��ǰ�����ļ��Ĵ�С
	QByteArray filebuf;//��ǰ���յ��ļ�����
	int from_id;
	int to_id;
};


class userInfo
{
public:
	userInfo(int uid, QString username, QString remark_name, int sex, QString wechat_id, QString image, QString address, int source, QString msg_date, QString content)
	{
		this->uid = uid;
		this->username = username;
		this->remark_name = remark_name;
		this->sex = sex;
		this->wechat_id = wechat_id;
		this->image = image;
		this->address = address;
		this->source = source;
		this->msg_date = msg_date;
		this->content = content;
	}
	userInfo() {}
	int uid;
	QString username;
	QString remark_name;
	int sex;
	QString wechat_id;
	QString image;
	QString address;
	int source;
	QString msg_date;
	QString content;
};

class Message
{
public:
	Message(int from_id, int to_id, QString msg_date, QString img, QString content)
	{
		this->from_id = from_id;
		this->to_id = to_id;
		this->msg_date = msg_date;
		this->img = img;
		this->content = content;
	}
	Message() {};
	int from_id = 0;
	int to_id = 0;
	QString msg_date;
	QString img;
	QString content;
};