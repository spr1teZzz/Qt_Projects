#pragma once
#pragma execution_character_set("utf-8")
#include <qwidget.h>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QString>
#include <QTcpSocket>
#include <QByteArray>
#include <QList>
#include <QListWidgetItem>
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
		this->content = content;
		this->msg_date = msg_date;
		this->img = img;
	}
	Message() {};
	int from_id = 0;
	int to_id = 0;
	QString content;
	QString msg_date;
	QString img;
};
class loginWidget :
    public QWidget
{
    Q_OBJECT
public:
	loginWidget( QWidget* parent = nullptr);
    ~loginWidget();
    void btn_login();
	static QTcpSocket* socket;
signals:
    void loginUser(int, QString, QMap<int, userInfo>,QMap<int,QList<Message>>);
public slots:
    void loginWindowClose();
    void recvMsg();

private:
    QLineEdit* LineEdit_username;
    QLineEdit* LineEdit_password;
    
};
struct sendMsgType
{
	int type;
	int uid;
	QString image;
	QMap<int, QList<Message>> message_map;
	QMap<int, userInfo> userinfo_map;
};

