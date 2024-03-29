#include "MainWidget.h"
#pragma execution_character_set("utf-8")
typedef QPair<int, userInfo>userInfo_pair;
#define SE_IMAGE "@IMAGE@"
#define SE_FILE "@FILE@"
#define SE_TEXT "@TEXT@"
#define MAX_BYTES_TO_WRITE 65535
#define MAX_BUFFER_SIZE 65535
#define MB 8,388,608
#define KB 1024
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    this->setMouseTracking(true); 
    select_file_flag = false;
    send_file_name = nullptr;
    fileSize = 0;//文件大小
    recvSize = 0;//当前接收文件的大小
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
    ui.pushButtonExpression->hide();

    QPixmap pixmapFolder(":/img/image/tools/folder.png");
    pixmapFolder = pixmapFolder.scaled(20, 20, Qt::KeepAspectRatio);
    ui.pushButtonFile->setIcon(QIcon(pixmapFolder));
    ui.pushButtonFile->hide();

    QPixmap pixmapCut(":/img/image/tools/cut.png");
    pixmapCut = pixmapCut.scaled(20, 20, Qt::KeepAspectRatio);
    ui.pushButtonShot->setIcon(QIcon(pixmapCut));
    ui.pushButtonShot->hide();

    QPixmap pixmapMsg(":/img/image/tools/message3.png");
    pixmapMsg = pixmapMsg.scaled(20, 20, Qt::KeepAspectRatio);
    ui.pushButtonRecords->setIcon(QIcon(pixmapMsg));
    ui.pushButtonRecords->hide();

    //发送消息窗口设置
    textedit = new MyTextEdit(this);
    textedit->setGeometry(320, 510, 620, 130);
    textedit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    textedit->hide();

    ui.pushButtonSend->setStyleSheet("QPushButton{ background-color:#E9E9E9; border-radius: 2px; border:none; font-weight:bold; color:#07CEBB; font-size:12px; }"
        "QPushButton:hover{background-color:#D2D2D2 ;}"
        "QPushButton:pressed{background-color:#C6C6C6;}");
    ui.pushButtonSend->hide();


    //发送消息为空提示
    emptyMsgLabel = new QLabel(this); 
    emptyMsgLabel->setGeometry(780, 610, 110, 30);
    emptyMsgLabel->setStyleSheet("background-color:#FFFFFF;font-size:12px;border-radius:5px;");
    emptyMsgLabel->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
    emptyMsgLabel->setText("不能发送空白消息");
    emptyMsgLabel->hide();

    //接收消息窗口设置
    ui.listWidgetShow->setStyleSheet("background-color:#F5F5F5;border:1px solid #D1D1D1;");
    ui.listWidgetShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.listWidgetShow->setSelectionMode(QAbstractItemView::NoSelection);
    ui.listWidgetShow->setFocusPolicy(Qt::NoFocus);
    ui.listWidgetShow->setFlow(QListWidget::TopToBottom);

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
    connect(ui.listWidget, &QListWidget::itemClicked, this, &MainWidget::selectListWidgetItem);
    connect(LoginWidget::socket, &QTcpSocket::readyRead, this, &MainWidget::recvMsg);
    connect(ui.pushButtonSend, SIGNAL(clicked()), this, SLOT(sendMsg()));
    connect(ui.pushButtonExpression, SIGNAL(clicked()), this, SLOT(selectExpression()));
    connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(selectFile()));
    connect(ui.pushButtonShot, SIGNAL(clicked()), this, SLOT(screenCut()));
    connect(ui.pushButtonRecords, SIGNAL(clicked()), this, SLOT(msgRecords()));

    //connect(LoginWidget::socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    //m_inStream.setDevice(LoginWidget::socket);
    //m_inStream.setVersion(QDataStream::Qt_5_6);

}

void MainWidget::onSocketError(QAbstractSocket::SocketError error)
{
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("%1").arg(LoginWidget::socket->errorString()));
        qDebug() << __FUNCTION__ << "QAbstractSocket::ConnectionRefusedError";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << __FUNCTION__ << "QAbstractSocket::RemoteHostClosedError";
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("%1").arg(LoginWidget::socket->errorString()));
        qDebug() << __FUNCTION__ << "QAbstractSocket::HostNotFoundError";
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::critical(this, QStringLiteral("错误"), QStringLiteral("%1").arg(LoginWidget::socket->errorString()));
        qDebug() << __FUNCTION__ << "QAbstractSocket::SocketTimeoutError";
        break;
    case QAbstractSocket::AddressInUseError:
        qDebug() << __FUNCTION__ << "QAbstractSocket::AddressInUseError";
        break;
    default:
        break;
    }
}
void MainWidget::updateShowList(int fid, int tid, QString msg)
{
    //更新消息显示
    //处理msg格式
    //"@FILE@12-05.md"
    QString data = msg;
    qDebug() << "updateShowList函数:" << data;
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString curDate = curDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QString dealcurDate = curDateTime.toString("yyyy-MM-ddThh:mm:ss");
    if (fid == user_uid)
    {
        //添加到message_map
        message_map[tid].insert(0, Message(fid, tid, curDate, user_url, data));
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
        MsgFrom* mf = new MsgFrom(user_url, ui.listWidgetShow);
        mf->setFixedWidth(ui.listWidgetShow->width());
        QSize size = mf->fontRect(data);
        QListWidgetItem* pItem = new QListWidgetItem();
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        ui.listWidgetShow->addItem(pItem);
        pItem->setSizeHint(size);
        mf->setText(data, curDate, size, MsgFrom::User_Me);
        ui.listWidgetShow->setItemWidget(pItem, mf);
    }
    else
    {
        //接收消息
        //添加到message_map
        message_map[fid].insert(0, Message(fid, tid, curDate, userinfo_map[fid].image, data));
        userinfo_map[fid].content = data;
        userinfo_map[fid].msg_date = curDate;
        //获取当前选中的item
        QListWidgetItem* item = ui.listWidget->currentItem();
        //当前用户选中了联系人
        if (item != nullptr)
        {
            qDebug() << "item != nullptr";
            QWidget* itWidget = ui.listWidget->itemWidget(item);
            int selectId = 0;
            if (itWidget)
            {
                QLabel* label_id = itWidget->findChild<QLabel*>("label_uid");
                selectId = label_id->text().toInt();
            }

            if (fid != selectId)
            {
                qDebug() << "fid != selectId";
                for (int j = 0; j < ui.listWidget->count(); ++j)
                {
                    QListWidgetItem* pItem = ui.listWidget->item(j);
                    QWidget* itWidget = ui.listWidget->itemWidget(pItem);
                    QLabel* label_uid = itWidget->findChild<QLabel*>("label_uid");
                    if (fid == label_uid->text().toInt())
                    {
                        int unread_count = 0;
                        chatFrom* temp_cf = qobject_cast<chatFrom*>(itWidget);
                        if (temp_cf != nullptr)
                        {
                            unread_count = temp_cf->getCount();
                        }
                        else
                        {
                            qDebug() << "qobject_cast<chatFrom*>转化失败";
                        }
                        //delete temp_cf;
                        QLabel* label_name = itWidget->findChild<QLabel*>("label_name");
                        chatFrom* cf = new chatFrom(fid, ":/img/image/" + userinfo_map[fid].image, label_name->text(), curDate, data);
                        cf->setCount(unread_count + 1);
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
                MsgFrom* mf = new MsgFrom(userinfo_map[fid].image, ui.listWidgetShow);
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
        else//当前用户未选中了联系人
        {
            for (int j = 0; j < ui.listWidget->count(); ++j)
            {
                QListWidgetItem* pItem = ui.listWidget->item(j);
                QWidget* itWidget = ui.listWidget->itemWidget(pItem);
                QLabel* label_uid = itWidget->findChild<QLabel*>("label_uid");
                if (fid == label_uid->text().toInt())
                {
                    int unread_count = 0;
                    qDebug() << "qobject_cast<chatFrom*>";
                    chatFrom* temp_cf = qobject_cast<chatFrom*>(itWidget);
                    if (temp_cf != nullptr)
                    {
                        unread_count = temp_cf->getCount();
                    }
                    else
                    {
                        qDebug() << "qobject_cast<chatFrom*>转化失败";
                    }
                    //delete temp_cf;
                    QLabel* label_name = itWidget->findChild<QLabel*>("label_name");
                    chatFrom* cf = new chatFrom(fid, ":/img/image/" + userinfo_map[fid].image, label_name->text(), curDate, data);
                    cf->setCount(unread_count + 1);
                    QListWidgetItem* frined_Item = new QListWidgetItem();
                    ui.listWidget->insertItem(0, frined_Item);
                    frined_Item->setSizeHint(QSize(350, 70));
                    ui.listWidget->setItemWidget(frined_Item, cf);
                    delete pItem;
                    break;
                }
            }
        }
    }
    //设置滑动到最下方
    ui.listWidgetShow->setCurrentRow(ui.listWidgetShow->count() - 1);
    this->update();
}

void MainWidget::updateShowList(QString msg)
{
	//更新消息显示
	//处理msg格式
	QStringList list = msg.split(SPLIT);
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
	if (fid == user_uid)
	{
        //添加到message_map
        message_map[tid].insert(0, Message(fid, tid, curDate, user_url, data));
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
        MsgFrom* mf = new MsgFrom(user_url,ui.listWidgetShow);
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
        message_map[fid].insert(0, Message(fid, tid, curDate, userinfo_map[fid].image, data));
        userinfo_map[fid].content = data;
        userinfo_map[fid].msg_date = curDate;
        //获取当前选中的item
        QListWidgetItem* item = ui.listWidget->currentItem();
        //当前用户选中了联系人
        if (item != nullptr)
        {
            qDebug() << "item != nullptr";
            QWidget* itWidget = ui.listWidget->itemWidget(item);
            int selectId = 0;
            if (itWidget)
            {
                QLabel* label_id = itWidget->findChild<QLabel*>("label_uid");
                selectId = label_id->text().toInt();
            }

            if (fid != selectId)
            {
                qDebug() << "fid != selectId";
                for (int j = 0; j < ui.listWidget->count(); ++j)
                {
                    QListWidgetItem* pItem = ui.listWidget->item(j);
                    QWidget* itWidget = ui.listWidget->itemWidget(pItem);
                    QLabel* label_uid = itWidget->findChild<QLabel*>("label_uid");
                    if (fid == label_uid->text().toInt())
                    {
                        int unread_count = 0;
                        chatFrom* temp_cf = qobject_cast<chatFrom*>(itWidget);
                        if (temp_cf != nullptr)
                        {
                            unread_count = temp_cf->getCount();
                        }
                        else
                        {
                            qDebug() << "qobject_cast<chatFrom*>转化失败";
                        }
                        //delete temp_cf;
                        QLabel* label_name = itWidget->findChild<QLabel*>("label_name");
                        chatFrom* cf = new chatFrom(fid, ":/img/image/" + userinfo_map[fid].image, label_name->text(), curDate, data);
                        cf->setCount(unread_count + 1);
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
                MsgFrom* mf = new MsgFrom(userinfo_map[fid].image, ui.listWidgetShow);
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
        else//当前用户未选中了联系人
        {
            for (int j = 0; j < ui.listWidget->count(); ++j)
            {
                QListWidgetItem* pItem = ui.listWidget->item(j);
                QWidget* itWidget = ui.listWidget->itemWidget(pItem);
                QLabel* label_uid = itWidget->findChild<QLabel*>("label_uid");
                if (fid == label_uid->text().toInt())
                {
                    int unread_count = 0;
                    qDebug() << "qobject_cast<chatFrom*>";
                    chatFrom* temp_cf = qobject_cast<chatFrom*>(itWidget);
                    if (temp_cf != nullptr)
                    {
                        unread_count = temp_cf->getCount();
                    }
                    else
                    {
                        qDebug() << "qobject_cast<chatFrom*>转化失败";
                    }
                    //delete temp_cf;
                    QLabel* label_name = itWidget->findChild<QLabel*>("label_name");
                    chatFrom* cf = new chatFrom(fid, ":/img/image/" + userinfo_map[fid].image, label_name->text(), curDate, data);
                    cf->setCount(unread_count + 1);
                    QListWidgetItem* frined_Item = new QListWidgetItem();
                    ui.listWidget->insertItem(0, frined_Item);
                    frined_Item->setSizeHint(QSize(350, 70));
                    ui.listWidget->setItemWidget(frined_Item, cf);
                    delete pItem;
                    break;
                }
            }
        }
	}
    //设置滑动到最下方
    ui.listWidgetShow->setCurrentRow(ui.listWidgetShow->count() - 1);
    this->update();
}
void MainWidget::selectExpression()
{
}
void MainWidget::selectFile()
{
    // 弹出文件选择窗口
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("All Files (*.*)");
    // display dialog and get selected file path
    QString filePath = dialog.getOpenFileName(this, "Select File to Send", QDir::homePath(), "All Files (*.*)");
    //发送文件
    if (filePath != nullptr)
    {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        send_file_name = filePath;
        paintFile(filePath);
        select_file_flag = true;
        //fileName为文件(带路径)
        qDebug() << "select filePath:" << filePath;
    }
    else
    {
        qDebug() << "选择文件有误";
    }
}
void MainWidget::screenCut()
{
}
void MainWidget::msgRecords()
{
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
    //设置界面可用
    ui.pushButtonExpression->show();
    ui.pushButtonFile->show();
    ui.pushButtonShot->show();
    ui.pushButtonRecords->show();
    ui.pushButtonSend->show();
    textedit->show();


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
        //已读消息
        chatFrom* cf = static_cast<chatFrom*>(itWidget);
        cf->have_read();
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
            //判断消息的发送方
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
    ui.listWidgetShow->setCurrentRow(ui.listWidgetShow->count() - 1);

    //6.改变发送人
    send_id = checked_uid;
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

void MainWidget::sendMsg()
{
    //处理发送数据
    if (textedit->toPlainText() != nullptr)
    {
        if (select_file_flag)
        {
            if (send_file_name != nullptr)
            {
                //发送文件
                QFile file(send_file_name);
                if (!file.open(QIODevice::ReadOnly)) {
                    qDebug() << "Failed to open file: " << file.errorString();
                    return;
                }
                //获取文件信息
                QFileInfo fileInfo(send_file_name);

                QByteArray fileData = file.readAll();
                file.close();
                qint64 size = fileData.size();
                QString prefix = QString("type=2%1from=%2%1to=%3%1").arg(SPLIT).arg(user_uid).arg(send_id);
                QString message = QString("%1\t%2\t%3\t").arg(SE_FILE).arg(fileInfo.fileName()).arg(size);
                qDebug() << "message:" << message;
                qint64 bytesWritten = LoginWidget::socket->write((prefix + message).toUtf8());
                LoginWidget::socket->flush();
                if (bytesWritten == -1) {
                    qDebug() << "Failed to send file: " << LoginWidget::socket->errorString();
                    return;
                }
                LoginWidget::socket->write(fileData);
                updateShowList(user_uid, send_id, QString("%1%2").arg(SE_FILE).arg(send_file_name));
                qDebug() << "File sent successfully!";
                //重置发送文件信息
                send_file_name = nullptr;
            }
            //重置发送文件状态
            select_file_flag = false;
            textedit->clear();
        }
        else
        {
            QString prefix = QString("type=2%1from=%2%1to=%3%1").arg(SPLIT).arg(user_uid).arg(send_id);
            //LoginWidget::socket->write(newData.toUtf8());
            //textedit->setText("");
            ////发送信号 进行格式处理 带有from_id 和 to_id
            //qDebug() << "newData:" << newData;
            //updateShowList(newData);
            QTextDocument* document = textedit->document();
            QTextBlock block = document->begin();
            while (block.isValid())
            {
                for (QTextBlock::iterator i = block.begin(); !i.atEnd(); ++i)
                {
                    QTextCharFormat format = i.fragment().charFormat();
                    if (format.isImageFormat() || format.hasProperty(QTextFormat::UserProperty))
                    {
                        QTextImageFormat imgf = format.toImageFormat();
                        if (format.hasProperty(QTextFormat::UserProperty))
                        {
                            QString imageName = format.property(QTextFormat::UserProperty).toString();
                            qDebug() << "Image name: " << imageName;
                        }

                        if (document->resource(QTextDocument::ImageResource, imgf.name()).canConvert<QPixmap>())
                        {
                            QString type = document->resource(QTextDocument::ImageResource, imgf.name()).typeName();
                            QVariant var = document->resource(QTextDocument::ImageResource, imgf.name());
                            QString imgName = imgf.name();

                            //取出图片
                            QImage image = QImage(var.value<QImage>());
                            QByteArray imageData;
                            QBuffer buffer(&imageData);
                            image.save(&buffer, "png", 50);

                            // 生成随机数名字
                            int randomNum = rand();

                            //存储到本地图片文件夹下
                            QString imageName = QString("image_%1.png").arg(randomNum);
                            QString localName = QString("image_%1(local).png").arg(randomNum);
                            QString curpath = QDir::currentPath() + "/..";
                            QString path = QString("%1/downImage/%2").arg(curpath).arg(localName);
                            image.loadFromData(imageData);
                            image.save(path);

                            //图片转码
                            imageData = imageData.toBase64();
                            qint64  size = imageData.size();
                            QString message = QString("%1\t%2\t%3\t").arg(SE_IMAGE).arg(imageName).arg(size);
                            QString data = prefix + message;
                            qDebug() << data;
                            LoginWidget::socket->write(data.toUtf8());
                            LoginWidget::socket->flush();
                            qint64 bytesWritten = 0;
                            while (bytesWritten < size) {
                                int bytesToWrite = qMin(size - bytesWritten, (long long)MAX_BYTES_TO_WRITE);
                                int bytesActuallyWritten = LoginWidget::socket->write(imageData.mid(bytesWritten, bytesToWrite));
                                bytesWritten += bytesActuallyWritten;
                                if (bytesActuallyWritten == -1) {
                                    qDebug() << "Error: failed to write to socket";
                                    return;
                                }
                            }
                            qDebug() << "updateShowList:" << QString("%1%2").arg(SE_IMAGE).arg(localName);
                            updateShowList(user_uid, send_id, QString("%1%2").arg(SE_IMAGE).arg(localName));
                            LoginWidget::socket->flush();
                        }
                    }
                    else
                    {
                        //是文字
                        QString text = i.fragment(). text();
                        QByteArray byteArr = text.toUtf8();
                        int size = byteArr.size();
                        QString message = QString("%1\tNULL\t%2\t%3").arg(SE_TEXT).arg(size).arg(text);
                        QString data = prefix + message;
                        //qDebug() << data;
                        qDebug() << "updateShowList:" << QString("%1%2").arg(SE_TEXT).arg(text);
                        updateShowList(user_uid, send_id, QString("%1%2").arg(SE_TEXT).arg(text));
                        LoginWidget::socket->write(data.toUtf8());
                        LoginWidget::socket->flush();
                    }
                }
                block = block.next();
            }
        }
        textedit->clear();
    }
    else
    {
        emptyMsgLabel->show();
        QTimer::singleShot(2000, this, &MainWidget::hideLabel);
    }
}
void MainWidget::hideLabel()
{
    emptyMsgLabel->hide();
}

void MainWidget::recvMsg()
{
        if (0 == fileSize && LoginWidget::socket->bytesAvailable() > sizeof(qint64))
        {
            QByteArray  data;
            //m_inStream >> data;
            data = LoginWidget::socket->readAll();
            qDebug() <<"data:"<< data;
            QStringList list = QString(data).split(SPLIT);
            if (list.size() >= 3)
            {
                int type = (list[0].split("="))[1].toInt();
                if (type == 2)
                {
                    //"type=2@SPRITE@from=1@SPRITE@to=2@SPRITE@@IMAGE@\timage_7588.png\t136004\t"
                    // "type=2@SPRITE@from=1@SPRITE@to=2@SPRITE@@TEXT@\tNULL\t6\t你好"
                    recv_msg_fid = (list[1].split("="))[1].toInt();
                    QStringList contentList = list[3].split("\t");
                    fileName = contentList[1];
                    fileSize = contentList[2].toInt();
                    if (contentList[0] == SE_IMAGE)
                    {
                        //图片
                        fileType = FILETYPE::IMAGE;
                    }
                    else if (contentList[0] == SE_FILE)
                    {
                        //文件
                        fileType = FILETYPE::FILE;
                    }
                    else if (contentList[0] == SE_TEXT)
                    {
                        //文字
                        fileType = FILETYPE::TEXT;
                        //直接处理
                        qDebug() << "接收到的消息" << contentList[3];
                        updateShowList(recv_msg_fid, user_uid, SE_TEXT + contentList[3]);
                        filebuf = nullptr;
                        fileSize = 0;
                        recvSize = 0;
                        return;
                    }
                    else
                    {
                        qDebug() << "Other Data";
                        fileType = FILETYPE::OTHERDATA;
                        return;
                    }
                    if (contentList[3] == "")
                    {
                        qDebug() << "contentList[3] == NULL";
                        recvSize = 0;
                        filebuf.clear();
                    }
                    else
                    {
                        qDebug() << "contentList[3] != NULL";
                        filebuf.clear();
                        filebuf.append(contentList[3]);
                        recvSize = contentList[3].size();
                    }
                }
                else
                {
                    qDebug() << "传送的数据有误";
                }
            }
        }
        else
        {
            
            qint64 size = qMin(LoginWidget::socket->bytesAvailable(), fileSize - recvSize);
            qDebug() << "recv file size:" << recvSize << "fileSize: " << fileSize<<"size:"<<size;
            if (size == 0) {
                return ;
            }
            QByteArray arry(size, 0);
            arry = LoginWidget::socket->read(size);
            filebuf.append(arry);
            //m_inStream.readRawData(arry.data(), size);
            recvSize += size;
            if (recvSize == fileSize && fileSize != 0) {
                if (fileType == FILETYPE::FILE) {
                    QString curpath = QDir::currentPath() + "/..";
                    QString path = QString("%1/downFile/%2").arg(curpath).arg(fileName);
                    QFile file(path);
                    file.open(QIODevice::WriteOnly);
                    file.write(filebuf);
                    file.close();
                    updateShowList(recv_msg_fid, user_uid, SE_FILE + fileName);
                    filebuf = nullptr;
                    fileSize = 0;
                    recvSize = 0;
                    //qDebug() << "接收到文件数据";
                }
                else if (fileType == FILETYPE::IMAGE) {
                    //根据文件名和文件大小接收和保存文件
                    QByteArray imagedata = QByteArray::fromBase64(filebuf);
                    QImage image;
                    qDebug() << "receive image:" << fileName;
                    QString curpath = QDir::currentPath() + "/..";
                    QString path = QString("%1/downImage/%2").arg(curpath).arg(fileName);
                    image.loadFromData(imagedata);
                    image.save(path);
                    updateShowList(recv_msg_fid, user_uid, SE_IMAGE + fileName);
                    filebuf = nullptr;
                    fileSize = 0;
                    recvSize = 0;
                }
                else
                {
                    qDebug() << "Other Data";
                }
                qDebug() << fileName << "接收成功";
            }
        }
}

void MainWidget::deal_remindData(QByteArray data)
{
    // "type=2@SPRITE@from=1@SPRITE@to=2@SPRITE@@IMAGE@\timage_10125.png\t136004\t"
    QStringList list = QString(data).split(SPLIT);
    if (list.size() > 0 && list[0].startsWith("type"))
    {
        //处理新的数据消息
        qDebug() << "deal_remindData(处理新消息)";
    }
    else
    {
        //接收的数据为上一个数据剩下的数据
        qDebug() << "deal_remindData";
        filebuf += data;
        recvSize += data.length();
        if (recvSize >= fileSize) {
            if (fileType == FILETYPE::FILE) {
                QFile file(fileName);
                file.open(QIODevice::WriteOnly);
                file.write(filebuf);
                file.close();
                filebuf = nullptr;
                fileSize = 0;
                recvSize = 0;
            }
            else if (fileType == FILETYPE::IMAGE) {
                //根据文件名和文件大小接收和保存文件
                QByteArray imagedata = QByteArray::fromBase64(filebuf);
                QImage image;
                qDebug() << "receive image:" << fileName;
                image.loadFromData(imagedata);
                image.save(fileName);
                filebuf = nullptr;
                fileSize = 0;
                recvSize = 0;
            }
            else
            {
                qDebug() << "Other Data";
            }
        }
    }
}

void MainWidget::paintFile(QString filePath)
{
    //获取文件的信息(图标,大小)
    QFileIconProvider provider;
    QFileInfo fileInfo(filePath);
    QIcon icon = provider.icon(fileInfo);
    QPixmap pixmap = icon.pixmap(QSize(20, 20)); // Convert QIcon to QPixmap
    QImage image = pixmap.toImage(); // Convert QPixmap to QImage
    if (image.isNull())
    {
        return;
    }
    QImage pain_image(250, 50, QImage::Format_RGB32); // 创建一个100x100的QImage
    pain_image.fill(Qt::white); // 将QImage填充为白色
    QPainter painter(&pain_image); // 创建一个QPainter对象，并指定绘制目标为QImage
    painter.drawPixmap(15, 10, pixmap);  // 在(0,0)位置绘制QPixmap对象
    // 在这里可以继续使用QPainter进行其他的绘图操作
    painter.drawText(50, 20, fileInfo.fileName());
    QString fileSize;
    if (fileInfo.size() < KB)
    {
        fileSize = QString("%1 B").arg(fileInfo.size());
    }
    else if (fileInfo.size() > KB && fileInfo.size() < MB)
    {
        int kb = fileInfo.size() >>10;
        fileSize = QString("%1 KB").arg(kb);
    }
    else
    {
        int mb = fileInfo.size() >> 20;
        fileSize = QString("%1 MB").arg(mb);
    }
    painter.drawText(50, 40, fileSize);

    //画边框
    painter.drawLine(0, 0, 249, 0);
    painter.drawLine(0, 0, 0, 49);
    painter.drawLine(249, 0, 249, 49);
    painter.drawLine(0, 49, 249, 49);
    painter.end(); // 结束绘图

    QTextCursor cursor = textedit->textCursor();
    QTextDocument* document = textedit->document();

    // 生成随机数
    int randomNum = rand();
    QString imageName = QString("image_%1").arg(randomNum);
    document->addResource(QTextDocument::ImageResource, QUrl(imageName), pain_image);
    cursor.insertImage(imageName);
    textedit->setTextCursor(cursor);
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