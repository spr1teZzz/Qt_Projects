#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_MainWindow.h"
#include <QLayout>
#include <QMenu>
#include <QMessageBox>
#include "framelesswidget.h"
#include <QApplication>
#include <qdesktopwidget.h>
#include "chatFrom.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <qdebug.h>
#include <QList>
#include <QMap>
#include <QDateTime>
#include <qimage.h>
#include "Client.h"
#include "loginwidget.h"
#include "MsgFrom.h"
#include <QTextCodec>
class userInfo
{
public:
	userInfo(int uid, QString username, QString remark_name, int sex, QString wechat_id, QString image, QString address,int source, QString msg_date,QString content)
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
		this->content= content;
	}
	userInfo(){}
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
	Message(int from_id, int to_id, QString content, QString msg_date, QString img)
	{
		this->from_id = from_id;
		this->to_id = to_id;
		this->content = content;
		this->msg_date = msg_date;
		this->img = img;
	}
	Message(){};
	int from_id = 0;
	int to_id = 0;
	QString content;
	QString msg_date;
	QString img;
};

class MainWindow : public FramelessWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	int user_id;
	QString user_url;//需要在登录后传过来
	QMap<int, QList<Message>> message_map;
	QMap<int, userInfo> userinfo_map;
	//QImage *image_url =new QImage(":/img/image/userImage3.png");
	Client* send_client;
private:
	void initForm();
	void signalSlotConnect();
	void selectToolButton(QToolButton* toolButton);
	
	//QVBoxLayout* layout_user;
	//QSqlDatabase db;
signals:
	void closeLoginWindow();
public slots:
	void rcvLogin(int,QString);
	void updateShowList(QString);


	void slotToolButtonChat();
	void slotToolButtonAddressBook();
	void slotToolButtonCollect();
	void slotToolButtonFile();
	void slotToolButtonFriends();
	void slotToolButtonLook();
	void slotToolButtonSearch();
	void slotToolButtonProgram();
	void slotToolButtonPhone();
	void slotToolButtonSettings();
	void slotActionShow();
	void closeWindow();
	void minWindow();
	void maxWindow();
	void topWindow();
	void selectListWidgetItem(QListWidgetItem* item);
private:
	Ui::MainWindowClass ui;
};
