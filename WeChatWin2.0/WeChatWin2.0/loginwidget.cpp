#include "loginwidget.h"
#define PORT 8888
#define IP "192.168.1.2"

QTcpSocket* LoginWidget::socket = new QTcpSocket();
LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::LoginWidgetClass())
{
	ui->setupUi(this);
    //初始化socket 连接服务器
    LoginWidget::socket->connectToHost(IP, PORT);
    //背景 设置成白色
    this->resize(280, 340);
    this->setWindowTitle("微信");
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setFixedSize(this->geometry().size());
    //账号框
    ui->LineEdit_username->installEventFilter(this);
    //密码框
    ui->LineEdit_password->setEchoMode(QLineEdit::Password);
    //头像
    QPixmap pixmap = QPixmap(":/img/image/login_in.png");
    QPixmap scaledPixmap = pixmap.scaled(80, 80, Qt::KeepAspectRatio);
    ui->label_img->setPixmap(scaledPixmap); 

    //账号密码提示
    QFont ft1;
    ft1.setPointSize(12);
    ui->label_userId->setFont(ft1);
    ui->label_password->setFont(ft1);
    ui->label_userId->setText("账 号");
    ui->label_password->setText("密 码");
    
    //登录按钮
    ui->btn_login->setStyleSheet("QPushButton{background-color: #07C160;border-radius: 2px;border-style: outset;}"
        "QPushButton:hover{background-color:#38CD7F ;}"
        "QPushButton:pressed{background-color:#07C160;");
    ui->btn_login->setText("登 录");
    QPalette btn_pal = ui->btn_login->palette();             //startBtn是我已经定义好的QPushButton对象
    btn_pal.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
    ui->btn_login->setPalette(btn_pal);
    //绑定登录按钮
    connect(ui->btn_login, &QPushButton::clicked, this, &LoginWidget::btn_login);
    connect(LoginWidget::socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
}

void LoginWidget::btn_login()
{
    //连接服务器校验登录
    QString username = ui->LineEdit_username->text();
    QString password = ui->LineEdit_password->text();
    QString login_msg = QString("type=1%1username=%2%1password=%3").arg(SPLIT).arg(username).arg(password);
    LoginWidget::socket->write(login_msg.toUtf8());
}

void LoginWidget::recvMsg()
{
    //接收服务器的校验信息
    QByteArray arr = LoginWidget::socket->readAll();
    QString data = QString::fromUtf8(arr);
    qDebug() << "loginWidget::recvMsg()" << data;
    //拆解data
    QStringList list = data.split("&");
    QString success = (list[0].split("="))[1];
    if (success == "false")
    {
        //登录失败
        QMessageBox::information(this, "login", "登录失败，账号或密码错误!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else
    {
        //登录成功 ,接收user_id、user_url、friendInfo、message
        int user_id = (list[1].split("="))[1].toInt();
        QString user_url = (list[2].split("="))[1];
        QString friendInfo = (list[3].split("="))[1];
        int pos = 0;
        for (int i = 0; i < 4; i++)
        {
            pos += list[i].size() + 1;
        }
        pos += 8;
        QString message = data.mid(pos);
        qDebug() << message;
        //解析friendInfo 和 Message
        QMap<int, userInfo> userinfo_map;
        QMap<int, QList<Message>> message_map;
        QStringList userList = friendInfo.split("/r");
        qDebug() << userList.size();

        for (int i = 0; i < userList.size() - 1; ++i)
        {
            QString frined;
            if (i == 0) //第一个元素处理{{ }
            {
                frined = userList[i].mid(2, userList[i].size() - 3);
            }
            else if (i == userList.size() - 1) //最后一个元素处理{ }}
            {
                frined = userList[i].mid(1, userList[i].size() - 3);
            }
            else //其他处理 { }
            {
                frined = userList[i].mid(1, userList[i].size() - 2);
            }
            //再通过 ","来分割信息
            //int uid;QString username;QString remark_name;int sex; QString wechat_id;QString image;
            //QString address;int source;QString msg_date;QString content;
            QStringList friendList = frined.split(",");
            int uid = friendList[0].toInt();
            QString username = friendList[1];
            QString remark_name = friendList[2];
            int sex = friendList[3].toInt();
            QString wechat_id = friendList[4];
            QString image = friendList[5];
            QString address = friendList[6];
            int source = friendList[7].toInt();
            QString msg_date = friendList[8];
            QString content = friendList[9];
            userInfo tmp = userInfo(uid, username, remark_name, sex, wechat_id, image, address, source, msg_date, content);
            userinfo_map.insert(uid, tmp);
        }
        QStringList firstList = message.split("/r/r", QString::SkipEmptyParts);
        for (int i = 0; i < firstList.size() - 1; ++i)
        {
            //if (firstList[i] == nullptr) continue;
            //通过 ","分割获取MessageList的uid
            QStringList secondList = firstList[i].split("/r");
            int message_id = 0;
            QList<Message> msg_list;
            for (int j = 0; j < secondList.size() - 1; ++j)
            {
                int from_id = 0;
                int to_id = 0;
                QString msg_date = "";
                QString img = "";
                QString content = "";
                QStringList thirdList = secondList[j].split(",");
                for (auto it : thirdList)
                {
                    qDebug() << it;
                }
                if (j == 0)
                {
                    //提取 message_id;
                    int num = 5;
                    if (i == 0)
                    {
                        num = 6;
                    }
                    message_id = thirdList[0].mid(num).toInt();

                    from_id = thirdList[1].mid(1).toInt();
                    to_id = thirdList[2].toInt();
                    msg_date = thirdList[3];
                    img = thirdList[4];
                    //获取所有内容
                    int size = 0;
                    for (int k = 0; k <= 4; ++k)
                    {
                        size += thirdList[k].size()+1;
                    }
                    content = secondList[j].mid(size, secondList[j].size() - size-1);
                    
                }
                else
                {
                    from_id = thirdList[0].mid(1).toInt();
                    to_id = thirdList[1].toInt();
                    msg_date = thirdList[2];
                    img = thirdList[3];
                    //content = thirdList[4].mid(0, thirdList[4].size() - 1);
                    //获取所有内容
                    int size = 0;
                    for (int k = 0; k <= 3; ++k)
                    {
                        size += thirdList[k].size()+1;
                    }
                    content = secondList[j].mid(size, secondList[j].size()-size-1);
                }
                msg_list.append(Message(from_id, to_id, msg_date, img, content));
            }

            //qDebug() << "message_id:" << message_id;
            message_map.insert(message_id, msg_list);
        }
        //登录成功给信号
        //解除绑定connect(loginWidget::socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
        disconnect(LoginWidget::socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
        emit loginUser(user_id, user_url, userinfo_map, message_map);
        this->close();
    }
}
bool LoginWidget::eventFilter(QObject* obj, QEvent* event)
{

    if (event->type() == QEvent::FocusOut && obj == ui->LineEdit_username &&ui->LineEdit_username->text() != "") {
        // 处理鼠标离开LineEdit框事件
        // 创建QGraphicsOpacityEffect并设置其透明度为0
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
        effect->setOpacity(0.0);
        ui->label_img->setGraphicsEffect(effect);
        // 创建动画并将其应用于QGraphicsOpacityEffect的透明度属性
        QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
        animation->setDuration(1000); // 动画时间为1秒
        animation->setStartValue(0.0);
        animation->setEndValue(1.0);
        //通过改变用户账号框 获取用户头像
        QString curpath = QDir::currentPath() + "/..";
        QString path = curpath + "/userData/userdata.ini";
        QFile file(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                //格式:phone img
                QStringList  list = line.split(" ");
                if (list[0] == ui->LineEdit_username->text())
                {   
                    
                    QPixmap pixmap = QPixmap(list[1]); // 本地路径
                    QPixmap scaledPixmap = pixmap.scaled(80, 80, Qt::KeepAspectRatio);
                    ui->label_img->setPixmap(scaledPixmap);
                    // 启动动画
                    animation->start();
                    break;
                }
                else
                {
                    QPixmap pixmap = QPixmap(":/img/image/login_in.png");
                    QPixmap scaledPixmap = pixmap.scaled(80, 80, Qt::KeepAspectRatio);
                    ui->label_img->setPixmap(scaledPixmap);
                    // 启动动画
                    animation->start();
                }
            }
            file.close();
        }
    }
    return false;
}
void LoginWidget::loginWindowClose()
{
    this->close();
}
LoginWidget::~LoginWidget()
{
    delete ui;
}

