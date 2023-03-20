#include "loginwidget.h"
#define PORT 8888
#define IP "127.0.0.1"
QTcpSocket* loginWidget::socket = new QTcpSocket();
loginWidget::loginWidget( QWidget* parent) :QWidget(parent)
{
    //��ʼ��socket ���ӷ�����
    loginWidget::socket->connectToHost(IP, PORT);
    //���� ���óɰ�ɫ
    this->resize(280, 340);
    this->setWindowTitle("΢��");
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setFixedSize(this->geometry().size());

    //ͷ��
    QLabel* img_label = new QLabel(this);
    img_label->setGeometry(100, 60, 80, 80);
    //QPixmap* pm = new QPixmap();
    //pm->load(":/img/image/userImage.png");
    //img_label->setPixmap(*pm);
    //img_label->setParent(this);
    img_label->setStyleSheet("background-image:url(:/img/image/userImage2.png);Background-size:80px,80px;");
    //�˺����������
    LineEdit_username = new QLineEdit(this);
    LineEdit_password = new QLineEdit(this);
    LineEdit_password->setEchoMode(QLineEdit::Password);
    LineEdit_username->setGeometry(85, 190, 145, 25);
    LineEdit_password->setGeometry(85, 220, 145, 25);

    //�˺�������ʾ
    QLabel* label_userId = new QLabel(this);
    QLabel* label_password = new QLabel(this);

    label_userId->setGeometry(40, 187, 40, 30);
    label_password->setGeometry(40, 217, 40, 30);
    QFont ft1;
    ft1.setPointSize(12);
    label_userId->setFont(ft1);
    label_password->setFont(ft1);
    label_userId->setText("�� ��");
    label_password->setText("�� ��");

    QPushButton* btn_login = new QPushButton(this);
    btn_login->setGeometry(40, 280, 200, 35);//
    btn_login->setStyleSheet("QPushButton{background-color: #07C160;border-radius: 2px;border-style: outset;}"
        "QPushButton:hover{background-color:#38CD7F ;}"
        "QPushButton:pressed{background-color:#07C160;");
    btn_login->setText("�� ¼");
    QPalette btn_pal = btn_login->palette();             //startBtn�����Ѿ�����õ�QPushButton����
    btn_pal.setColor(QPalette::ButtonText, Qt::white);    //���ð�ť�ϵ�������ɫ�������Ͽ��ԣ�ʵ���Ͼ��ǿ���
    btn_login->setPalette(btn_pal);

    //�ǳ�
    QLabel* username = new QLabel(this);
    username->setText("�� ��");
    username->setGeometry(115, 140, 50, 30);
    QFont ft;
    ft.setPointSize(14);
    username->setFont(ft);

    //�󶨵�¼��ť
    connect(btn_login, &QPushButton::clicked, this, &loginWidget::btn_login);
}
void loginWidget::btn_login()
{
    //���ӷ�����У���¼
    QString username = LineEdit_username->text();
    QString password = LineEdit_password->text();

    QString login_msg = "type=1&username=" + username + "&password=" + password;
    loginWidget::socket->write(login_msg.toUtf8());
    connect(loginWidget::socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
}

void loginWidget::recvMsg()
{
    //���շ�������У����Ϣ
    QByteArray arr = loginWidget::socket->readAll();
    QString data = arr.data();
    qDebug() << "loginWidget::recvMsg()"<<data;
    //���data
    QStringList list = data.split("&");
    QString success = (list[0].split("="))[1];
    if (success == "false")
    {
        //��¼ʧ��
        QMessageBox::information(this, "login", "��¼ʧ�ܣ��˺Ż��������!",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else
    {
        //��¼�ɹ� ,����user_id��user_url��friendInfo��message
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
        //����friendInfo �� Message
        QMap<int, userInfo> userinfo_map;
        QMap<int, QList<Message>> message_map;
        //qDebug() << friendInfo;
        //qDebug() << message;
        QStringList userList = friendInfo.split("/r");
        qDebug() << userList.size();
        
        for (int i = 0; i < userList.size()-1; ++i)
        {
            QString frined;
            if (i == 0) //��һ��Ԫ�ش���{{ }
            {
                frined = userList[i].mid(2, userList[i].size() - 3);
            }else if (i == userList.size() - 1) //���һ��Ԫ�ش���{ }}
            {
                frined = userList[i].mid(1, userList[i].size() - 3);
            }
            else //�������� { }
            {
                frined = userList[i].mid(1, userList[i].size() - 2);
            }
            //��ͨ�� ","���ָ���Ϣ
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
        QStringList firstList = message.split("/r/r",QString::SkipEmptyParts);
        for (int i = 0; i < firstList.size()-1; ++i)
        {
            //if (firstList[i] == nullptr) continue;
            //ͨ�� ","�ָ��ȡMessageList��uid
            QStringList secondList = firstList[i].split("/r");
            int message_id = 0;
            QList<Message> msg_list;
            for (int j = 0; j < secondList.size()-1; ++j)
            {
                int from_id=0;
                int to_id=0;
                QString msg_date="";
                QString img="";
                QString content="";
                QStringList thirdList = secondList[j].split(",");
                //qDebug() << "thirdList" + QString::number(i) << ":";
                for (auto it : thirdList)
                {
                    qDebug() << it;
                }
                //qDebug() << "**************************************";
                //qDebug() << "thirdList.size()" << thirdList.size();
                if (j == 0)
                {
                    //��ȡ message_id;
                    int num = 5;
                    if (i == 0)
                    {
                        num = 6;
                    }
                    message_id = thirdList[0].mid(num).toInt();
                        
                    //qDebug() <<" thirdList[0]"<< thirdList[0] << " message_id:" << message_id;
                    from_id = thirdList[1].mid(1).toInt();
                    to_id = thirdList[2].toInt();
                    msg_date = thirdList[3];
                    img = thirdList[4];
                    content = thirdList[5].mid(0, thirdList[5].size() - 1);
                }
                else
                {
                    from_id = thirdList[0].mid(1).toInt();
                    to_id = thirdList[1].toInt();
                    msg_date = thirdList[2];
                    img = thirdList[3];
                    content = thirdList[4].mid(0, thirdList[4].size() - 1);
                }
                msg_list.append(Message(from_id, to_id, msg_date, img, content));
            }

            //qDebug() << "message_id:" << message_id;
            message_map.insert(message_id, msg_list);
        }
        //��¼�ɹ����ź�
        //�����connect(loginWidget::socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
        disconnect(loginWidget::socket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
        emit loginUser(user_id, user_url, userinfo_map,message_map);
        this->close();
        
    }
}

void loginWidget::loginWindowClose()
{
    this->close();
}
loginWidget::~loginWidget()
{
   
}
