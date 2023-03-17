#pragma once

#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QTextCodec>
#include <QMap>
#include <QList>
class TcpClientSocket  : public QTcpSocket
{
	Q_OBJECT

public:
	TcpClientSocket(QObject *parent = 0);

	~TcpClientSocket();
protected slots:
	void receivedata();//处理readyRead信号读取数据
	void slotclientdisconnected();//客户端断开连接触发disconnected信号，这个槽函数用来处理这个信号

signals:
	void updateserver(QString,int,int);//用来告诉tcpserver需要跟新界面的显示 从 fid 发送 给 tid 内容:data
	void clientdisconnected(qintptr); //告诉server有客户端断开连接
	void connectsuccess(int, qintptr);//发送连接成功信号,并记录套接字对应的uid
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