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
    void deal_readyRead();//读取数据槽函数
    void deal_disconnect();//断开连接槽函数
    void deal_write(QByteArray ba);//写入数据槽函数
signals:
    void AddMessage(QString data);//发送给UI显示
    void WriteMessage(QByteArray ba);//UI发送过来数据
    void DeleteSocket();//主动关闭socket
private:
	QString fileName;//当前文件名
	FILETYPE fileType;//当前文件类型
	int fileSize;//当前文件大小
	int recvSize;//当前接收文件的大小
	QByteArray filebuf;//当前接收的文件数据
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