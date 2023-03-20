#include "loginwidget.h"
loginWidget::loginWidget(QWidget* parent) :QWidget(parent)
{


    //背景 设置成白色
    this->resize(280, 340);
    this->setWindowTitle(QStringLiteral("微信"));
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setFixedSize(this->geometry().size());

    //头像
    QLabel* img_label = new QLabel(this);
    img_label->setGeometry(100, 60, 80, 80);

    img_label->setStyleSheet("background-image:url(:/img/image/userImage2.png);Background-size:80px,80px;");
    //账号密码输入框
    LineEdit_username = new QLineEdit(this);
    LineEdit_password = new QLineEdit(this);
    LineEdit_password->setEchoMode(QLineEdit::Password);
    LineEdit_username->setGeometry(85, 190, 145, 25);
    LineEdit_password->setGeometry(85, 220, 145, 25);
    //账号密码显示
    QLabel* label_userId = new QLabel(this);
    QLabel* label_password = new QLabel(this);

    label_userId->setGeometry(40, 187, 40, 30);
    label_password->setGeometry(40, 217, 40, 30);
    QFont ft1;
    ft1.setPointSize(12);
    label_userId->setFont(ft1);
    label_password->setFont(ft1);
    label_userId->setText(QStringLiteral("账 号"));
    label_password->setText(QStringLiteral("密 码"));

    QPushButton* btn_login = new QPushButton(this);
    btn_login->setGeometry(40, 280, 200, 35);//
    btn_login->setStyleSheet("QPushButton{background-color: #07C160;border-radius: 2px;border-style: outset;}"
        "QPushButton:hover{background-color:#38CD7F ;}"
        "QPushButton:pressed{background-color:#07C160;");
    btn_login->setText(QStringLiteral("登 录"));
    QPalette btn_pal = btn_login->palette();             //startBtn是我已经定义好的QPushButton对象
    btn_pal.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
    btn_login->setPalette(btn_pal);

    //昵称
    QLabel* username = new QLabel(this);
    username->setText(QStringLiteral("向 北"));
    username->setGeometry(115, 140, 50, 30);
    QFont ft;
    ft.setPointSize(14);
    username->setFont(ft);

    //绑定登录按钮
    connect(btn_login, &QPushButton::clicked, this, &loginWidget::btn_login);
}
void loginWidget::btn_login()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "login");  //连接的MYSQL的数据库驱动
    db.setHostName("localhost");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("test");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("123456");            //密码
    db.open();

    //处理登录  发送信号
    QString username = LineEdit_username->text();
    QString password = LineEdit_password->text();
    QSqlQuery query(db);
    QString sql = "select * from wc_user where phone = '" + username + "'and password = '" + password+"' ;";
    qDebug() << sql;
    bool res = query.exec(sql);
    if (res)
    {
        qDebug() << "login success!";
        int uid = 0;
        QString image;
        while (query.next())
        {
            uid = query.value("uid").toInt();
            QString name = query.value("username").toString();
            QString pwd = query.value("password").toString();
            QString wechatid = query.value("wechatid").toString();
            QString phone = query.value("phone").toString();
            QString address = query.value("address").toString();
            image = query.value("image").toString();
            qDebug() << "uid:" << uid << " name:" << name << " password:" << pwd<<" phone:"<<phone<<" wechatid"<< wechatid<<" address"<< address
                <<" image"<< image;
        }
        emit loginWidget::loginUser(uid,image);
    }
    else qDebug() << "login failed!";
    db.close();
}

void loginWidget::loginWindowClose()
{
    this->close();
}
loginWidget::~loginWidget()
{
   
}