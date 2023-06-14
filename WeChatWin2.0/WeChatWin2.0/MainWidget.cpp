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
    fileSize = 0;//�ļ���С
    recvSize = 0;//��ǰ�����ļ��Ĵ�С
}

MainWidget::~MainWidget()
{}

void MainWidget::initForm()
{
    //��ʼ������
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    //������Ⱦ
    this->resize(940, 720);
    this->setStyleSheet("background-color:#F5F5F5;");

    //����leftWigdet ������ɫ
    ui.widget_left->setStyleSheet("background-color:#2E2E2E;border:1px solid #2E2E2E;");
    ui.widget->setStyleSheet("background-color:#F5F5F5;border:1px solid #D1D1D1;");
    //������
    ui.widget_search->setStyleSheet("background-color:#F7F7F7;border:1px solid #D6D6D6;");

    ui.lineEditSearch->setStyleSheet("background-color:#E2E2E2;border:none;");
    ui.labelSearchIcon->setStyleSheet("border:none;background-image:url(:/img/image/searchIcon.png);border-radius:2px;");
    ui.pushButtonAdd->setStyleSheet("background-color:#D1D1D1;border-radius:2px;border:none;");

    //���������������
    ui.pushButtonName->setStyleSheet("background-color:#F5F5F5;border:none;font-weight:bold;font-size:20px;text-align:left;");

    //���칤��������
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

    //������Ϣ��������
    textedit = new MyTextEdit(this);
    textedit->setGeometry(320, 510, 620, 130);
    textedit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    textedit->hide();

    ui.pushButtonSend->setStyleSheet("QPushButton{ background-color:#E9E9E9; border-radius: 2px; border:none; font-weight:bold; color:#07CEBB; font-size:12px; }"
        "QPushButton:hover{background-color:#D2D2D2 ;}"
        "QPushButton:pressed{background-color:#C6C6C6;}");
    ui.pushButtonSend->hide();


    //������ϢΪ����ʾ
    emptyMsgLabel = new QLabel(this); 
    emptyMsgLabel->setGeometry(780, 610, 110, 30);
    emptyMsgLabel->setStyleSheet("background-color:#FFFFFF;font-size:12px;border-radius:5px;");
    emptyMsgLabel->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
    emptyMsgLabel->setText("���ܷ��Ϳհ���Ϣ");
    emptyMsgLabel->hide();

    //������Ϣ��������
    ui.listWidgetShow->setStyleSheet("background-color:#F5F5F5;border:1px solid #D1D1D1;");
    ui.listWidgetShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.listWidgetShow->setSelectionMode(QAbstractItemView::NoSelection);
    ui.listWidgetShow->setFocusPolicy(Qt::NoFocus);
    ui.listWidgetShow->setFlow(QListWidget::TopToBottom);

    //��������
    ui.pushButtonTop->setStyleSheet("background-image:url(:/img/image/windowTop.png);");

    //ͷ��
    ui.pushButton_userImage->setGeometry(5, 20, 40, 40);
    ui.pushButton_userImage->setStyleSheet("border:1px solid #2E2E2E;background-image:url(:/img/image/" + user_url + "); ");
    //�û��б�����
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

    //��ť
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

    // ����toolbutton��ѡ��״̬
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

    // ����Ĭ��ѡ�г���
    ui.toolButtonChat->setChecked(true);
    ui.stackedWidget->setCurrentIndex(0);
    // ������չ�����˵�
    ui.toolButtonSettings->setPopupMode(QToolButton::InstantPopup);
    auto externMenu = new QMenu(ui.toolButtonSettings);
    auto moveAction = new QAction("Ǩ���뱸��", externMenu);
    auto suggestAction = new QAction("�������", externMenu);
    auto settingsAction = new QAction("����", externMenu);

    // ��Ӳ˵�
    externMenu->addAction(moveAction);
    externMenu->addAction(suggestAction);
    externMenu->addAction(settingsAction);

    // �����ڶ����źŲ�����
    connect(moveAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
    connect(suggestAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
    ui.toolButtonSettings->setMenu(externMenu);
    //���ڶ����źŲ�����
    connect(ui.pushButtonTop, SIGNAL(clicked()), this, SLOT(topWindow()));
    connect(ui.pushButtonMin, SIGNAL(clicked()), this, SLOT(minWindow()));
    connect(ui.pushButtonMax, SIGNAL(clicked()), this, SLOT(maxWindow()));
    connect(ui.pushButtonClose, SIGNAL(clicked()), this, SLOT(closeWindow()));

    //��userinfo_map ����ʱ������
    QVector<userInfo_pair>userInfo_vec;
    for (auto it = userinfo_map.begin(); it != userinfo_map.end(); ++it)
    {
        userInfo_pair tmp(it.key(), it.value());
        userInfo_vec.append(tmp);
    }

    //������Ϣʱ������
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
    //�źźͲ۳�ʼ��
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
        QMessageBox::critical(this, QStringLiteral("����"), QStringLiteral("%1").arg(LoginWidget::socket->errorString()));
        qDebug() << __FUNCTION__ << "QAbstractSocket::ConnectionRefusedError";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << __FUNCTION__ << "QAbstractSocket::RemoteHostClosedError";
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, QStringLiteral("����"), QStringLiteral("%1").arg(LoginWidget::socket->errorString()));
        qDebug() << __FUNCTION__ << "QAbstractSocket::HostNotFoundError";
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::critical(this, QStringLiteral("����"), QStringLiteral("%1").arg(LoginWidget::socket->errorString()));
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
    //������Ϣ��ʾ
    //����msg��ʽ
    //"@FILE@12-05.md"
    QString data = msg;
    qDebug() << "updateShowList����:" << data;
    QDateTime curDateTime = QDateTime::currentDateTime();
    QString curDate = curDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QString dealcurDate = curDateTime.toString("yyyy-MM-ddThh:mm:ss");
    if (fid == user_uid)
    {
        //��ӵ�message_map
        message_map[tid].insert(0, Message(fid, tid, curDate, user_url, data));
        userinfo_map[tid].content = data;
        userinfo_map[tid].msg_date = curDate;
        //�Է�����Ϣ��friend�����ƶ�����һ��λ��
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
        //���ʱ����Ϣ
        dealMessageTime(dealcurDate);
        //�����Ϣ
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
        //������Ϣ
        //��ӵ�message_map
        message_map[fid].insert(0, Message(fid, tid, curDate, userinfo_map[fid].image, data));
        userinfo_map[fid].content = data;
        userinfo_map[fid].msg_date = curDate;
        //��ȡ��ǰѡ�е�item
        QListWidgetItem* item = ui.listWidget->currentItem();
        //��ǰ�û�ѡ������ϵ��
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
                            qDebug() << "qobject_cast<chatFrom*>ת��ʧ��";
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
                //���ʱ����Ϣ
                dealMessageTime(dealcurDate);
                //�����Ϣ
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
        else//��ǰ�û�δѡ������ϵ��
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
                        qDebug() << "qobject_cast<chatFrom*>ת��ʧ��";
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
    //���û��������·�
    ui.listWidgetShow->setCurrentRow(ui.listWidgetShow->count() - 1);
    this->update();
}

void MainWidget::updateShowList(QString msg)
{
	//������Ϣ��ʾ
	//����msg��ʽ
	QStringList list = msg.split(SPLIT);
	int fid = (list[1].split("="))[1].toInt();
	int tid = (list[2].split("="))[1].toInt();
	//qDebug() << "fid:" << fid << " tid:" << tid;
	//qDebug() << userinfo_map[fid].image << endl;
    //��ֹcontent��&��=
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
        //��ӵ�message_map
        message_map[tid].insert(0, Message(fid, tid, curDate, user_url, data));
        userinfo_map[tid].content = data;
        userinfo_map[tid].msg_date = curDate;
        //�Է�����Ϣ��friend�����ƶ�����һ��λ��
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
        //���ʱ����Ϣ
        dealMessageTime(dealcurDate);
        //�����Ϣ
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
        //������Ϣ
        //��ӵ�message_map
        message_map[fid].insert(0, Message(fid, tid, curDate, userinfo_map[fid].image, data));
        userinfo_map[fid].content = data;
        userinfo_map[fid].msg_date = curDate;
        //��ȡ��ǰѡ�е�item
        QListWidgetItem* item = ui.listWidget->currentItem();
        //��ǰ�û�ѡ������ϵ��
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
                            qDebug() << "qobject_cast<chatFrom*>ת��ʧ��";
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
                //���ʱ����Ϣ
                dealMessageTime(dealcurDate);
                //�����Ϣ
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
        else//��ǰ�û�δѡ������ϵ��
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
                        qDebug() << "qobject_cast<chatFrom*>ת��ʧ��";
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
    //���û��������·�
    ui.listWidgetShow->setCurrentRow(ui.listWidgetShow->count() - 1);
    this->update();
}
void MainWidget::selectExpression()
{
}
void MainWidget::selectFile()
{
    // �����ļ�ѡ�񴰿�
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("All Files (*.*)");
    // display dialog and get selected file path
    QString filePath = dialog.getOpenFileName(this, "Select File to Send", QDir::homePath(), "All Files (*.*)");
    //�����ļ�
    if (filePath != nullptr)
    {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        send_file_name = filePath;
        paintFile(filePath);
        select_file_flag = true;
        //fileNameΪ�ļ�(��·��)
        qDebug() << "select filePath:" << filePath;
    }
    else
    {
        qDebug() << "ѡ���ļ�����";
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
    //���մ��ݵ�����
    userinfo_map = userinfo;
    message_map = message;
    user_uid = uid;
    user_url = url;
    //��ʼ������
    initForm();
    //��ʼ���ۺ���
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
    QMessageBox::information(this, "�����˵���ʾ", "����ѡ�񴥷�", QMessageBox::Yes);
}
void MainWidget::closeWindow()
{
    //�رմ���
    this->close();
}
void MainWidget::minWindow()
{
    //��С������
    this->showMinimized();
}
void MainWidget::maxWindow()
{
    //��󻯴���
    this->showMaximized();
}
void MainWidget::topWindow()
{
    //��δʵ��
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
        isShowTime = ((curTime - lastTime) > 60); // ������Ϣ���һ����
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
    //����б�ѡ�� ����ҵ��
    //���ý������
    ui.pushButtonExpression->show();
    ui.pushButtonFile->show();
    ui.pushButtonShot->show();
    ui.pushButtonRecords->show();
    ui.pushButtonSend->show();
    textedit->show();


    //1.�����ǰ��message
    while (ui.listWidgetShow->count() > 0)
    {
        QListWidgetItem* item = ui.listWidgetShow->takeItem(0);
        delete item;
    }

    //2.ͨ�������ȡ��ǰѡ��widget
    int checked_uid = 0;
    QString url;
    if (item)
    {
        QWidget* itWidget = ui.listWidget->itemWidget(item);
        //�Ѷ���Ϣ
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

    //3.�� message_map ���ضԻ���Ϣ
    QList<Message> messageList = message_map[checked_uid];

    //4.����ʱ�䵹�����
    if (messageList.size() != 0)
    {
        //������
        for (int i = messageList.size() - 1; i >= 0; --i)
        {
            QString img_url;
            //�ж���Ϣ�ķ��ͷ�
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
    //5.��Ϣlistwidget���������·�
    ui.listWidgetShow->setCurrentRow(ui.listWidgetShow->count() - 1);

    //6.�ı䷢����
    send_id = checked_uid;
}


void MainWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) //�������������
    {
        isPressed = true;
        curPos = event->pos();    //��¼��ǰ�ĵ������
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (isPressed) //�������������           
    {
        this->move(event->pos() - curPos + this->pos());    //�����ƶ�
    }
}
//����ͷ�
void MainWidget::mouseReleaseEvent(QMouseEvent* event)
{
    isPressed = false;
}

void MainWidget::sendMsg()
{
    //����������
    if (textedit->toPlainText() != nullptr)
    {
        if (select_file_flag)
        {
            if (send_file_name != nullptr)
            {
                //�����ļ�
                QFile file(send_file_name);
                if (!file.open(QIODevice::ReadOnly)) {
                    qDebug() << "Failed to open file: " << file.errorString();
                    return;
                }
                //��ȡ�ļ���Ϣ
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
                //���÷����ļ���Ϣ
                send_file_name = nullptr;
            }
            //���÷����ļ�״̬
            select_file_flag = false;
            textedit->clear();
        }
        else
        {
            QString prefix = QString("type=2%1from=%2%1to=%3%1").arg(SPLIT).arg(user_uid).arg(send_id);
            //LoginWidget::socket->write(newData.toUtf8());
            //textedit->setText("");
            ////�����ź� ���и�ʽ���� ����from_id �� to_id
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

                            //ȡ��ͼƬ
                            QImage image = QImage(var.value<QImage>());
                            QByteArray imageData;
                            QBuffer buffer(&imageData);
                            image.save(&buffer, "png", 50);

                            // �������������
                            int randomNum = rand();

                            //�洢������ͼƬ�ļ�����
                            QString imageName = QString("image_%1.png").arg(randomNum);
                            QString localName = QString("image_%1(local).png").arg(randomNum);
                            QString curpath = QDir::currentPath() + "/..";
                            QString path = QString("%1/downImage/%2").arg(curpath).arg(localName);
                            image.loadFromData(imageData);
                            image.save(path);

                            //ͼƬת��
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
                        //������
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
                    // "type=2@SPRITE@from=1@SPRITE@to=2@SPRITE@@TEXT@\tNULL\t6\t���"
                    recv_msg_fid = (list[1].split("="))[1].toInt();
                    QStringList contentList = list[3].split("\t");
                    fileName = contentList[1];
                    fileSize = contentList[2].toInt();
                    if (contentList[0] == SE_IMAGE)
                    {
                        //ͼƬ
                        fileType = FILETYPE::IMAGE;
                    }
                    else if (contentList[0] == SE_FILE)
                    {
                        //�ļ�
                        fileType = FILETYPE::FILE;
                    }
                    else if (contentList[0] == SE_TEXT)
                    {
                        //����
                        fileType = FILETYPE::TEXT;
                        //ֱ�Ӵ���
                        qDebug() << "���յ�����Ϣ" << contentList[3];
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
                    qDebug() << "���͵���������";
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
                    //qDebug() << "���յ��ļ�����";
                }
                else if (fileType == FILETYPE::IMAGE) {
                    //�����ļ������ļ���С���պͱ����ļ�
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
                qDebug() << fileName << "���ճɹ�";
            }
        }
}

void MainWidget::deal_remindData(QByteArray data)
{
    // "type=2@SPRITE@from=1@SPRITE@to=2@SPRITE@@IMAGE@\timage_10125.png\t136004\t"
    QStringList list = QString(data).split(SPLIT);
    if (list.size() > 0 && list[0].startsWith("type"))
    {
        //�����µ�������Ϣ
        qDebug() << "deal_remindData(��������Ϣ)";
    }
    else
    {
        //���յ�����Ϊ��һ������ʣ�µ�����
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
                //�����ļ������ļ���С���պͱ����ļ�
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
    //��ȡ�ļ�����Ϣ(ͼ��,��С)
    QFileIconProvider provider;
    QFileInfo fileInfo(filePath);
    QIcon icon = provider.icon(fileInfo);
    QPixmap pixmap = icon.pixmap(QSize(20, 20)); // Convert QIcon to QPixmap
    QImage image = pixmap.toImage(); // Convert QPixmap to QImage
    if (image.isNull())
    {
        return;
    }
    QImage pain_image(250, 50, QImage::Format_RGB32); // ����һ��100x100��QImage
    pain_image.fill(Qt::white); // ��QImage���Ϊ��ɫ
    QPainter painter(&pain_image); // ����һ��QPainter���󣬲�ָ������Ŀ��ΪQImage
    painter.drawPixmap(15, 10, pixmap);  // ��(0,0)λ�û���QPixmap����
    // ��������Լ���ʹ��QPainter���������Ļ�ͼ����
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

    //���߿�
    painter.drawLine(0, 0, 249, 0);
    painter.drawLine(0, 0, 0, 49);
    painter.drawLine(249, 0, 249, 49);
    painter.drawLine(0, 49, 249, 49);
    painter.end(); // ������ͼ

    QTextCursor cursor = textedit->textCursor();
    QTextDocument* document = textedit->document();

    // ���������
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