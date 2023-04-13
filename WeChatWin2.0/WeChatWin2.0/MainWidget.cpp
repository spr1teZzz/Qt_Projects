#include "MainWidget.h"
typedef QPair<int, userInfo>userInfo_pair;
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    this->setMouseTracking(true);
}

MainWidget::~MainWidget()
{}

void MainWidget::initForm()
{
    //初始化界面
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    //标题渲染
    this->resize(940, 720);
    this->setStyleSheet("background-color:#F5F5F5;");

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

    QPixmap pixmapExpression(":/img/image/tools/emotion.png");
    pixmapExpression = pixmapExpression.scaled(20, 20, Qt::KeepAspectRatio);
    ui.pushButtonExpression->setIcon(QIcon(pixmapExpression));

    QPixmap pixmapFolder(":/img/image/tools/folder.png");
    pixmapFolder = pixmapFolder.scaled(20, 20, Qt::KeepAspectRatio);
    ui.pushButtonFile->setIcon(QIcon(pixmapFolder));

    QPixmap pixmapCut(":/img/image/tools/cut.png");
    pixmapCut = pixmapCut.scaled(20, 20, Qt::KeepAspectRatio);
    ui.pushButtonShot->setIcon(QIcon(pixmapCut));


    QPixmap pixmapMsg(":/img/image/tools/message3.png");
    pixmapMsg = pixmapMsg.scaled(20, 20, Qt::KeepAspectRatio);
    ui.pushButtonRecords->setIcon(QIcon(pixmapMsg));

    //发送消息窗口设置
    send_client = new Client(user_uid, this);
    send_client->move(270+55, 450+70);

    //接收消息窗口设置
    ui.listWidgetShow->setStyleSheet("background-color:#F5F5F5;border:1px solid #D1D1D1;");
    ui.listWidgetShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.listWidgetShow->setSelectionMode(QAbstractItemView::NoSelection);
    ui.listWidgetShow->setFocusPolicy(Qt::NoFocus);
    //窗口设置
    ui.pushButtonTop->setStyleSheet("background-image:url(:/img/image/windowTop.png);");

    //头像
    ui.pushButton_userImage->setGeometry(5, 20, 40, 40);
    ui.pushButton_userImage->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/" + user_url + "); ");
    //用户列表设置
    QFile file(":/qss/scrollbar.qss");
    if (file.open(QFile::ReadOnly))
    {

        QString array = file.readAll();
        ui.listWidget->verticalScrollBar()->setStyleSheet(array);
        ui.listWidgetShow->verticalScrollBar()->setStyleSheet(array);
        
        file.close();
    }else
    {
        qDebug() << "open scrollbar.qss failed";
    }

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

    //对userinfo_map 按照时间排序
    QVector<userInfo_pair>userInfo_vec;
    for (auto it = userinfo_map.begin(); it != userinfo_map.end(); ++it)
    {
        userInfo_pair tmp(it.key(), it.value());
        userInfo_vec.append(tmp);
    }

    //按照消息时间排序
    qSort(userInfo_vec.begin(), userInfo_vec.end(), [](userInfo_pair p1, userInfo_pair p2) {return p1.second.msg_date > p2.second.msg_date; });

    for (auto it : userInfo_vec)
    {
        QString name;
        if (it.second.remark_name == nullptr)
        {
            name = it.second.username;
        }
        else
        {
            name = it.second.remark_name;
        }
        chatFrom* cf = new chatFrom(it.second.uid, ":/img/image/" + it.second.image, name, it.second.msg_date, it.second.content);
        QListWidgetItem* pItem = new QListWidgetItem();
        ui.listWidget->addItem(pItem);
        pItem->setSizeHint(QSize(250, 70));
        ui.listWidget->setItemWidget(pItem, cf);
        ui.listWidget->sortItems(Qt::DescendingOrder);
    }

    connect(ui.listWidget, &QListWidget::itemClicked, this, &MainWidget::selectListWidgetItem);
    connect(ui.listWidget, &QListWidget::itemClicked, send_client, &Client::openSend);
    //当接收到client发送过来的信号(发出消息)时,向listWidgetShow添加数据
    connect(send_client, &Client::sendMsgSuccess, this, &MainWidget::updateShowList);
    //当接收到client发送过来的信号(接收消息)时,向listWidgetShow添加数据
    connect(send_client, &Client::recvMsgSuccess, this, &MainWidget::updateShowList);
}

void MainWidget::signalSlotConnect()
{
    //信号和槽初始化
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

void MainWidget::updateShowList(QString msg)
{
	//更新消息显示
	//处理msg格式
	QStringList list = msg.split("&");
	int fid = (list[1].split("="))[1].toInt();
	int tid = (list[2].split("="))[1].toInt();
	//qDebug() << "fid:" << fid << " tid:" << tid;
	//qDebug() << userinfo_map[fid].image << endl;
    //防止content有&或=
    QString data = list[3];
    for (int i = 4;i < list.size(); ++i)
    {
        data += list[i];
    }
	QDateTime curDateTime = QDateTime::currentDateTime();
    QString curDate = curDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QString dealcurDate = curDateTime.toString("yyyy-MM-ddThh:mm:ss");
	QString image;
	if (fid == user_uid)
	{
        //发出消息
		image = user_url;
        //添加到message_map
        message_map[tid].insert(0, Message(fid, tid, curDate, image, data));
        userinfo_map[tid].content = data;
        userinfo_map[tid].msg_date = curDate;
        //对发送消息的friend进行移动到第一个位置
        QListWidgetItem* item = ui.listWidget->currentItem();
        //ui.listWidget->currentRowChanged(0);
        QWidget* itWidget = ui.listWidget->itemWidget(item);
        QString friend_name;
        if (itWidget)
        {
            QLabel* label_name = itWidget->findChild<QLabel*>("label_name");
            friend_name = label_name->text();
        }
        chatFrom* cf = new chatFrom(tid, ":/img/image/" + userinfo_map[tid].image, friend_name, curDate, data);
        QListWidgetItem* frined_Item = new QListWidgetItem();
        ui.listWidget->insertItem(0, frined_Item);
        frined_Item->setSizeHint(QSize(240, 70));
        ui.listWidget->setItemWidget(frined_Item, cf);
        ui.listWidget->setCurrentRow(0);
        delete item;
        //添加时间消息
        dealMessageTime(dealcurDate);
        //添加消息
        MsgFrom* mf = new MsgFrom(image,ui.listWidgetShow);
        mf->setFixedWidth(ui.listWidgetShow->width());
        QSize size = mf->fontRect(data);
        QListWidgetItem* pItem = new QListWidgetItem();
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        ui.listWidgetShow->addItem(pItem);
        pItem->setSizeHint(size);
        mf->setText(data, curDate, size,MsgFrom::User_Me);
        ui.listWidgetShow->setItemWidget(pItem, mf);
	}
	else
	{
        //接收消息
        //添加到message_map
        image = userinfo_map[fid].image;
        message_map[fid].insert(0, Message(fid, tid, curDate, image, data));
        userinfo_map[fid].content = data;
        userinfo_map[fid].msg_date = curDate;
        //获取当前选中的item
        QListWidgetItem* item = ui.listWidget->currentItem();
        QWidget* itWidget = ui.listWidget->itemWidget(item);
        int selectId = 0;
        if (itWidget)
        {
            QLabel* label_id = itWidget->findChild<QLabel*>("label_uid");
            selectId = label_id->text().toInt();
        }
        //找到发出消息的friend 如果当前选中的friend是发送的,Item创建新的item插入第一行并删除原来的item
        if (fid != selectId)
        {
            for (int j = 0; j < ui.listWidget->count(); ++j)
            {
                QListWidgetItem* pItem = ui.listWidget->item(j);
                QWidget* itWidget = ui.listWidget->itemWidget(pItem);
                QLabel* label_uid = itWidget->findChild<QLabel*>("label_uid");
                if (fid == label_uid->text().toInt())
                {
                    QLabel* label_name = itWidget->findChild<QLabel*>("label_name");
                    chatFrom* cf = new chatFrom(fid, ":/img/image/" + userinfo_map[fid].image, label_name->text(), curDate, data);
                    QListWidgetItem* frined_Item = new QListWidgetItem();
                    ui.listWidget->insertItem(0, frined_Item);
                    frined_Item->setSizeHint(QSize(350, 70));
                    ui.listWidget->setItemWidget(frined_Item, cf);
                    delete pItem;
                    break;
                }
            }
        }
        else
        {
            QString friend_name;
            if (itWidget)
            {
                QLabel* label_name = itWidget->findChild<QLabel*>("label_name");
                friend_name = label_name->text();
            }
            chatFrom* cf = new chatFrom(fid, ":/img/image/" + userinfo_map[fid].image, friend_name, curDate, data);
            QListWidgetItem* frined_Item = new QListWidgetItem();
            ui.listWidget->insertItem(0, frined_Item);
            frined_Item->setSizeHint(QSize(240, 70));
            ui.listWidget->setItemWidget(frined_Item, cf);
            ui.listWidget->setCurrentRow(0);
            delete item;
            //添加时间消息
            dealMessageTime(dealcurDate);
            //添加消息
            MsgFrom* mf = new MsgFrom(image, ui.listWidgetShow);
            mf->setFixedWidth(ui.listWidgetShow->width());
            QSize size = mf->fontRect(data);
            QListWidgetItem* pItem = new QListWidgetItem();
            pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
            ui.listWidgetShow->addItem(pItem);
            pItem->setSizeHint(size);
            mf->setText(data, curDate, size, MsgFrom::User_Other);
            ui.listWidgetShow->setItemWidget(pItem, mf);
        }

	}
    //设置滑动到最下方
    ui.listWidgetShow->setCurrentRow(ui.listWidgetShow->count() - 1);
    this->update();
}
void MainWidget::rcvLogin(int uid, QString url, QMap<int, userInfo>userinfo, QMap<int, QList<Message>>  message)
{
    //接收传递的数据
    userinfo_map = userinfo;
    message_map = message;
    user_uid = uid;
    user_url = url;
    //初始化窗口
    initForm();
    //初始化槽函数
    signalSlotConnect();
    this->show();
}



void MainWidget::slotToolButtonChat()
{
    selectToolButton(ui.toolButtonChat);
}

void MainWidget::slotToolButtonAddressBook()
{
    selectToolButton(ui.toolButtonAddressBook);
}

void MainWidget::slotToolButtonCollect()
{
    selectToolButton(ui.toolButtonCollect);
}

void MainWidget::slotToolButtonFile()
{
    selectToolButton(ui.toolButtonFile);
}
void MainWidget::slotToolButtonFriends()
{
    selectToolButton(ui.toolButtonFriends);
}
void MainWidget::slotToolButtonLook()
{
    selectToolButton(ui.toolButtonFriends);
}

void MainWidget::slotToolButtonSearch()
{
    selectToolButton(ui.toolButtonSearch);
}

void MainWidget::slotToolButtonProgram()
{
    selectToolButton(ui.toolButtonProgram);
}

void MainWidget::slotToolButtonPhone()
{
    selectToolButton(ui.toolButtonPhone);
}

void MainWidget::slotToolButtonSettings()
{
    selectToolButton(ui.toolButtonSettings);
}

void MainWidget::slotActionShow()
{
    QMessageBox::information(this, "按键菜单演示", "按键选择触发", QMessageBox::Yes);
}
void MainWidget::closeWindow()
{
    //关闭窗口
    this->close();
}
void MainWidget::minWindow()
{
    //最小化窗口
    this->showMinimized();
}
void MainWidget::maxWindow()
{
    //最大化窗口
    this->showMaximized();
}
void MainWidget::topWindow()
{
    //还未实现
}
void MainWidget::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    
    if (ui.listWidgetShow->count() > 0) {
        QListWidgetItem* lastItem = ui.listWidgetShow->item(ui.listWidgetShow->count() - 1);
        MsgFrom* msgFrom = (MsgFrom*)ui.listWidgetShow->itemWidget(lastItem);
        int curTime = QDateTime::fromString(curMsgTime,"yyyy-MM-ddThh:mm:ss").toTime_t();
        int lastTime = QDateTime::fromString(msgFrom->time(), "yyyy-MM-ddThh:mm:ss").toTime_t();
        /*qDebug() << "curTime lasttime:" << curTime<<" "<< lastTime;*/
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
    }
    else {
        isShowTime = true;
    }
    if (isShowTime) {
        MsgFrom* messageTime = new MsgFrom("", ui.listWidgetShow);
        QListWidgetItem* itemTime = new QListWidgetItem(ui.listWidgetShow);
        itemTime->setFlags(itemTime->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        ui.listWidgetShow->addItem(itemTime);
        QSize size = QSize(ui.listWidgetShow->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, MsgFrom::User_Time);
        ui.listWidgetShow->setItemWidget(itemTime, messageTime);
    }
}
void MainWidget::selectListWidgetItem(QListWidgetItem* item)
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
            QLabel* label_name = itWidget->findChild<QLabel*>("label_name");
            QLabel* label_uid = itWidget->findChild<QLabel*>("label_uid");
            //QLabel
            ui.pushButtonName->setText(label_name->text());
            checked_uid = label_uid->text().toInt();
            //url = label_image->pixmap()->toImage();
            //qDebug() << url;
        }
    }
    //3.从 message_map 加载对话信息
    QList<Message> messageList = message_map[checked_uid];

    //4.按照时间倒序输出
    if (messageList.size() != 0)
    {
        //有数据
        for (int i = messageList.size() - 1; i >= 0; --i)
        {
            QString img_url;
            MsgFrom::User_Type type;
            if (messageList[i].from_id == user_uid)
            {
                img_url = user_url;
                type = MsgFrom::User_Me;
            }
            else
            {
                img_url = messageList[i].img;
                type = MsgFrom::User_Other;
            }
            dealMessageTime(messageList[i].msg_date);
            MsgFrom* mf = new MsgFrom(img_url, ui.listWidgetShow);
            mf->setFixedWidth(ui.listWidgetShow->width());
            QSize size = mf->fontRect(messageList[i].content);
            QListWidgetItem* pItem = new QListWidgetItem();
            pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
            ui.listWidgetShow->addItem(pItem);
            pItem->setSizeHint(size);
            mf->setText(messageList[i].content, messageList[i].msg_date, size, type);
            ui.listWidgetShow->setItemWidget(pItem, mf);
        }
    }
    //5.信息listwidget滑动到最下方
    //ui.listWidgetShow->scrollToBottom();

    ui.listWidgetShow->setCurrentRow(ui.listWidgetShow->count() - 1);
    //6.改变发送人
    send_client->changeToId(user_uid, checked_uid);
}


void MainWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) //如果鼠标左键按下
    {
        isPressed = true;
        curPos = event->pos();    //记录当前的点击坐标
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (isPressed) //如果鼠标左键按下           
    {
        this->move(event->pos() - curPos + this->pos());    //窗口移动
    }
}

//鼠标释放
void MainWidget::mouseReleaseEvent(QMouseEvent* event)
{
    isPressed = false;
}



void MainWidget::selectToolButton(QToolButton* toolButton)
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

    }
    else if (ui.toolButtonLook == toolButton)
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
    }
    else if (ui.toolButtonSearch == toolButton)
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
    }
    else if (ui.toolButtonProgram == toolButton)
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
    }
    else if (ui.toolButtonPhone == toolButton)
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
    }
    else if (ui.toolButtonSettings == toolButton)
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