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
	void receivedata();//����readyRead�źŶ�ȡ����
	void slotclientdisconnected();//�ͻ��˶Ͽ����Ӵ���disconnected�źţ�����ۺ���������������ź�

signals:
	void updateserver(QString,int,int);//��������tcpserver��Ҫ���½������ʾ �� fid ���� �� tid ����:data
	void clientdisconnected(qintptr); //����server�пͻ��˶Ͽ�����
	void connectsuccess(int, qintptr);//�������ӳɹ��ź�,����¼�׽��ֶ�Ӧ��uid
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