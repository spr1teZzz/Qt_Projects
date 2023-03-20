#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: FramelessWidget(parent)
{
	ui.setupUi(this);
	//user_id = 1;
	//initForm();
	//signalSlotConnect();
}

MainWindow::~MainWindow()
{}

void MainWindow::initForm( )
{
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec);
	//标题渲染
	this->resize(940, 720);
	this->setStyleSheet("background-color:#F5F5F5;");
	this->setWindowFlags(Qt::FramelessWindowHint);
	//设置leftWigdet 背景颜色
	ui.widget_left->setStyleSheet("background-color:#2E2E2E;border:1px solid #2E2E2E;");
	ui.widget->setStyleSheet("background-color:#F5F5F5;border:1px solid #D1D1D1;");
	//搜索框
	ui.widget_search->setStyleSheet("background-color:#F7F7F7;border:1px solid #D6D6D6;");

	ui.lineEditSearch->setStyleSheet("background-color:#E2E2E2;border:none;");
	ui.labelSearchIcon->setStyleSheet("border:none;background-image:url(:/img/image/searchIcon.png);border-radius:2px;");
	ui.pushButtonAdd->setStyleSheet("background-color:#D1D1D1;border-radius:2px;border:none;");

	//聊天对象名字设置
	ui.pushButtonName->setStyleSheet("background-color:#F5F5F5;border:none;font-weight:bold;font-size:20px;text-align:left;");

	//聊天工具栏设置
	ui.widgetToolBar->setStyleSheet("background-color:#F5F5F5;border:none;");
	ui.pushButtonExpression->setStyleSheet("background-image:url(:/img/image/expression.png); ");
	ui.pushButtonFile->setStyleSheet("background-image:url(:/img/image/file.png); ");
	ui.pushButtonShot->setStyleSheet("background-image:url(:/img/image/screenShot.png); ");
	ui.pushButtonRecords->setStyleSheet("background-image:url(:/img/image/msgRecords.png); ");

	//发送消息窗口设置
	send_client = new Client(user_id,this);
	send_client->move(305,560);
	
	//接收消息窗口设置
	ui.listWidgetShow->setStyleSheet("background-color:#F5F5F5;border:1px solid #D1D1D1;");

	//窗口设置
	ui.pushButtonTop->setStyleSheet("background-image:url(:/img/image/windowTop.png);");

	//头像
	ui.pushButton_userImage->setGeometry(5,20,40,40);
	ui.pushButton_userImage->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/"+user_url+"); ");
	//用户列表设置
	ui.listWidget->setStyleSheet("background-color:#DADBDC;border:1px solid #D1D1D1;");
	//按钮
	ui.toolButtonChat->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/01.png);");
	ui.toolButtonAddressBook->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/02.png);");
	ui.toolButtonCollect->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/03.png);");
	ui.toolButtonFile->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/04.png);");
	ui.toolButtonFriends->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/05.png);");
	ui.toolButtonLook->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/06.png);");
	ui.toolButtonSearch->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/07.png);");
	ui.toolButtonProgram->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/08.png);");
	ui.toolButtonPhone->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/09.png);");
	ui.toolButtonSettings->setStyleSheet("border:1px solid #2E2E2E;");
	ui.toolButtonSettings->setIcon(QPixmap(":/img/image/10.png"));
	ui.toolButtonSettings->setIconSize(QPixmap(":/img/image/10.png").size());
	// 设置toolbutton可选择状态
	ui.toolButtonChat->setCheckable(true);
	ui.toolButtonAddressBook->setCheckable(true);
	ui.toolButtonCollect->setCheckable(true);
	ui.toolButtonFile->setCheckable(true);
	ui.toolButtonFriends->setCheckable(true);
	ui.toolButtonLook->setCheckable(true);
	ui.toolButtonSearch->setCheckable(true);
	ui.toolButtonProgram->setCheckable(true);
	ui.toolButtonPhone->setCheckable(true);
	ui.toolButtonSettings->setCheckable(true);

	// 设置默认选中程序
	ui.toolButtonChat->setChecked(true);
	ui.stackedWidget->setCurrentIndex(0);
	// 设置拓展按键菜单
	ui.toolButtonSettings->setPopupMode(QToolButton::InstantPopup);
	auto externMenu = new QMenu(ui.toolButtonSettings);
	auto moveAction = new QAction("迁移与备份", externMenu);
	auto suggestAction = new QAction("意见反馈", externMenu);
	auto settingsAction = new QAction("设置", externMenu);
	
	// 添加菜单
	externMenu->addAction(moveAction);
	externMenu->addAction(suggestAction);
	externMenu->addAction(settingsAction);


	// 设置内动作信号槽连接
	connect(moveAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
	connect(suggestAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
	connect(settingsAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
	ui.toolButtonSettings->setMenu(externMenu);
	//窗口动作信号槽连接
	connect(ui.pushButtonTop, SIGNAL(clicked()), this, SLOT(topWindow()));
	connect(ui.pushButtonMin, SIGNAL(clicked()), this, SLOT(minWindow()));
	connect(ui.pushButtonMax, SIGNAL(clicked()), this, SLOT(maxWindow()));
	connect(ui.pushButtonClose, SIGNAL(clicked()), this, SLOT(closeWindow()));

	//页面0 pageChat
	//获取信息列表
	//db
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","pageChat");  //连接的MYSQL的数据库驱动
	db.setHostName("localhost");         //主机名
	db.setPort(3306);                    //端口
	db.setDatabaseName("test");          //数据库名
	db.setUserName("root");              //用户名
	db.setPassword("123456");            //密码
	db.open();

	//meg_db
	QSqlDatabase db_msg = QSqlDatabase::addDatabase("QMYSQL", "pageChatMessage");  //连接的MYSQL的数据库驱动
	db_msg.setHostName("localhost");         //主机名
	db_msg.setPort(3306);                    //端口
	db_msg.setDatabaseName("test");          //数据库名
	db_msg.setUserName("root");              //用户名
	db_msg.setPassword("123456");            //密码
	db_msg.open();

	QSqlQuery query(db);
	QSqlQuery query_msg(db_msg);
	QString sql = "select wc_friend.friendid as uid , wc_user.username,remarkname as remark_name,\
		sex,wechatid as wechat_id,image,address,source from wc_friend LEFT JOIN wc_user ON (wc_friend.friendid = wc_user.uid) where wc_friend.uid = "+ QString::number(user_id);
	bool res = query.exec(sql);
	
	if (res)
	{
		qDebug() << "chatPage success! uid:"<<user_id;
		while (query.next())
		{
			int uid = query.value("uid").toInt();
			QString username = query.value("username").toString();
			QString remark_name = query.value("remark_name").toString();
			int sex = query.value("sex").toInt();
			QString wechat_id = query.value("wechat_id").toString();
			QString image = query.value("image").toString();
			QString address = query.value("address").toString();
			int source = query.value("source").toInt();
			//qDebug() << "search data!";
			QList<Message> messageList;
			//获取对话信息
			//SELECT* FROM wc_messagerecords  WHERE fromid = 1 and toid = 2 or fromid = 2 and toid = 1 ORDER BY msgdate DESC LIMIT 5;
			QString sql_message("select * from wc_messagerecords  WHERE fromid = " + QString::number(user_id) + " and toid = " + QString::number(uid) + " or toid = " + QString::number(user_id) + " and fromid = " + QString::number(uid) + " ORDER BY msgdate DESC LIMIT 5; ");
			qDebug() << user_id<<" uid:"<<uid;

			bool res_msg = query_msg.exec(sql_message);
			if (res_msg)
			{
				qDebug() << "chatPage message success!";
				while (query_msg.next())
				{
					int from_id = query_msg.value("fromid").toInt();
					int to_id = query_msg.value("toid").toInt();
					QString content = query_msg.value("content").toString();
					QString msg_date = query_msg.value("msgdate").toString();
					messageList.append(Message(from_id, to_id, content, msg_date, image));
				}
			}
			else
			{
				qDebug() << "chatPage messagefailed";
			}
			Message msg;
			if (messageList.size() != 0)
			{
				msg = messageList[0];
			}
			userinfo_map.insert(uid,userInfo(uid, username, remark_name, sex, wechat_id, image, address, source, msg.msg_date,msg.content));
			message_map.insert(uid,messageList);
		}
	}
	else
	{
		qDebug() << "chatPage failed";
	}


	QMap<int, userInfo>::Iterator user_iter;
	for (user_iter = userinfo_map.begin(); user_iter != userinfo_map.end();++user_iter)
	{
		QString name;
		if (user_iter.value().remark_name == nullptr)
		{
			name = user_iter.value().username;
		}
		else
		{
			name = user_iter.value().remark_name;
		}
		chatFrom* cf = new chatFrom(user_iter.value().uid,":/img/image/"+ user_iter.value().image, name, user_iter.value().msg_date, user_iter.value().content);
		QListWidgetItem* pItem = new QListWidgetItem();
		ui.listWidget->addItem(pItem);
		pItem->setSizeHint(QSize(250, 70));
		ui.listWidget->setItemWidget(pItem, cf);
	}
	db.close();
	//QListWidgetItem* checkedItem = ui.listWidget->currentItem();
	//if(checkedItem)
	//	qDebug()<< "item:"<< checkedItem->data(Qt::DisplayRole).toString();
	connect(ui.listWidget, &QListWidget::itemClicked, this, &MainWindow::selectListWidgetItem);

	//当接收到client发送过来的信号(发出消息)时,向listWidgetShow添加数据
	QObject::connect(send_client, &Client::sendMsgSuccess, this, &MainWindow::updateShowList);

	//当接收到client发送过来的信号(接收消息)时,向listWidgetShow添加数据
	QObject::connect(send_client, &Client::recvMsgSuccess, this, &MainWindow::updateShowList);
}

void MainWindow::rcvLogin(int uid,QString image)
{
	//登录成功
	//关闭登录页面
	qDebug() << "user_url:" + image;
	user_id = uid;
	user_url = image;
	initForm();
	signalSlotConnect();
	this->show();
	emit closeLoginWindow();
}


void MainWindow::updateShowList(QString msg)
{
	//更新消息显示
	//处理msg格式
	QStringList list = msg.split(",");
	int fid = (list[0].split(":"))[1].toInt();
	int tid = (list[1].split(":"))[1].toInt();
	//qDebug() << "fid:" << fid << " tid:" << tid;
	qDebug() << userinfo_map[fid].image << endl;
	QString data = msg.mid(list[0].size() + list[1].size()+2);
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString curDate = curDateTime.toString("yyyy-MM-dd hh:mm:ss");
	QString image;
	if(fid == user_id) 
	{ 
		image = user_url;
	}
	else
	{
		image = userinfo_map[fid].image;
	}
	MsgFrom* mf = new MsgFrom(user_id,fid, tid,image, curDate, data);
	QListWidgetItem* pItem = new QListWidgetItem();
	ui.listWidgetShow->addItem(pItem);
	pItem->setSizeHint(QSize(600, mf->height + 20));
	ui.listWidgetShow->setItemWidget(pItem, mf);
}


void MainWindow::slotToolButtonChat()
{
	selectToolButton(ui.toolButtonChat);
}

void MainWindow::slotToolButtonAddressBook()
{
	selectToolButton(ui.toolButtonAddressBook);
}

void MainWindow::slotToolButtonCollect()
{
	selectToolButton(ui.toolButtonCollect);
}

void MainWindow::slotToolButtonFile()
{
	selectToolButton(ui.toolButtonFile);
}
void MainWindow::slotToolButtonFriends()
{
	selectToolButton(ui.toolButtonFriends);
}
void MainWindow::slotToolButtonLook()
{
	selectToolButton(ui.toolButtonFriends);
}

void MainWindow::slotToolButtonSearch()
{
	selectToolButton(ui.toolButtonSearch);
}

void MainWindow::slotToolButtonProgram()
{
	selectToolButton(ui.toolButtonProgram);
}

void MainWindow::slotToolButtonPhone()
{
	selectToolButton(ui.toolButtonPhone);
}

void MainWindow::slotToolButtonSettings()
{
	selectToolButton(ui.toolButtonSettings);
}

void MainWindow::slotActionShow()
{
	QMessageBox::information(this, "按键菜单演示", "按键选择触发", QMessageBox::Yes);
}
void MainWindow::closeWindow()
{
	//关闭窗口
	this->close();
}
void MainWindow::minWindow()
{
	//最小化窗口
	this->showMinimized();
}
void MainWindow::maxWindow()
{
	//最大化窗口
	this->showMaximized();
}
void MainWindow::topWindow()
{
	//还未实现
}
//信号和槽的连接
void MainWindow::signalSlotConnect()
{
	connect(ui.toolButtonChat, SIGNAL(clicked()), this, SLOT(slotToolButtonChat()));
	connect(ui.toolButtonAddressBook, SIGNAL(clicked()), this, SLOT(slotToolButtonCollect()));
	connect(ui.toolButtonCollect, SIGNAL(clicked()), this, SLOT(slotToolButtonFile()));
	connect(ui.toolButtonFile, SIGNAL(clicked()), this, SLOT(slotToolButtonFriends()));
	connect(ui.toolButtonFriends, SIGNAL(clicked()), this, SLOT(slotToolButtonLook()));
	connect(ui.toolButtonLook, SIGNAL(clicked()), this, SLOT(slotToolButtonProgram()));
	connect(ui.toolButtonSearch, SIGNAL(clicked()), this, SLOT(slotToolButtonSearch()));
	connect(ui.toolButtonProgram, SIGNAL(clicked()), this, SLOT(slotToolButtonProgram()));
	connect(ui.toolButtonPhone, SIGNAL(clicked()), this, SLOT(slotToolButtonPhone()));
	connect(ui.toolButtonSettings, SIGNAL(clicked()), this, SLOT(slotToolButtonSettings()));
}

void MainWindow::selectToolButton(QToolButton* toolButton)
{
	if (ui.toolButtonChat == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(0);
		ui.toolButtonChat->setChecked(true);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(false);

	}
	else if (ui.toolButtonAddressBook == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(1);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(true);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(false);

	}
	else if (ui.toolButtonCollect == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(2);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(true);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(false);

	}
	else if (ui.toolButtonFile == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(3);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(true);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(false);

	}
	else if (ui.toolButtonFriends == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(4);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(true);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(false);

	}else if(ui.toolButtonLook == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(5);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(true);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(false);
	}else if(ui.toolButtonSearch == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(6);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(true);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(false);
	}else if(ui.toolButtonProgram == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(7);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(true);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(false);
	}else if(ui.toolButtonPhone == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(8);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(true);
		ui.toolButtonSettings->setChecked(false);
	}else if (ui.toolButtonSettings == toolButton)
	{
		ui.stackedWidget->setCurrentIndex(9);
		ui.toolButtonChat->setChecked(false);
		ui.toolButtonAddressBook->setChecked(false);
		ui.toolButtonCollect->setChecked(false);
		ui.toolButtonFile->setChecked(false);
		ui.toolButtonFriends->setChecked(false);
		ui.toolButtonLook->setChecked(false);
		ui.toolButtonSearch->setChecked(false);
		ui.toolButtonProgram->setChecked(false);
		ui.toolButtonPhone->setChecked(false);
		ui.toolButtonSettings->setChecked(true);
	}
}

void MainWindow::selectListWidgetItem(QListWidgetItem* item)
{
	//点击列表选项 处理业务

	//1.清空以前的message
	while (ui.listWidgetShow->count() > 0)
	{
		QListWidgetItem* item = ui.listWidgetShow->takeItem(0);
		delete item;
	}

	//2.通过点击获取当前选中widget
	int checked_uid = 0;
	QString url;
	if (item)
	{
		QWidget* itWidget = ui.listWidget->itemWidget(item);
		if (itWidget)
		{
			QLabel* label_date = itWidget->findChild<QLabel*>("label_date");
			QLabel* label_image = itWidget->findChild<QLabel*>("label_image");
			QLabel* label_msg = itWidget->findChild<QLabel*>("label_msg");
			QLabel* label_name= itWidget->findChild<QLabel*>("label_name");
			QLabel* label_uid = itWidget->findChild<QLabel*>("label_uid");
			//QLabel
			ui.pushButtonName->setText(label_name->text());
			checked_uid = label_uid->text().toInt();
			//url = label_image->pixmap()->toImage();
			qDebug() << url;
		}
	}
	//3.选中后选项背景变成#C6C5C5 ：未完成
	
	//4.从 message_map 加载对话信息
	QList<Message> messageList = message_map[checked_uid];

	//5.按照时间倒序输出
	if (messageList.size() != 0)
	{
		//有数据
		
		for (int i= messageList.size()-1;i>=0 ;--i )
		{
			QString img_url;
			if (messageList[i].from_id == user_id)
			{
				img_url = user_url;
			}
			else
			{
				img_url = messageList[i].img;
			}
			//qDebug()<<"url:"<< url;
			MsgFrom* mf = new MsgFrom(user_id, messageList[i].from_id, messageList[i].to_id, img_url, messageList[i].msg_date, messageList[i].content);
			QListWidgetItem* pItem = new QListWidgetItem();
			ui.listWidgetShow->addItem(pItem);
			pItem->setSizeHint(QSize(600,mf->height+20));
			ui.listWidgetShow->setItemWidget(pItem, mf);
		}
	}
	//6.改变发送人
	send_client->changeToId(user_id,checked_uid);
}

