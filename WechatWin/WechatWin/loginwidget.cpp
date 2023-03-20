#include "loginwidget.h"
loginWidget::loginWidget(QWidget* parent) :QWidget(parent)
{


    //���� ���óɰ�ɫ
    this->resize(280, 340);
    this->setWindowTitle(QStringLiteral("΢��"));
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setFixedSize(this->geometry().size());

    //ͷ��
    QLabel* img_label = new QLabel(this);
    img_label->setGeometry(100, 60, 80, 80);

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
    label_userId->setText(QStringLiteral("�� ��"));
    label_password->setText(QStringLiteral("�� ��"));

    QPushButton* btn_login = new QPushButton(this);
    btn_login->setGeometry(40, 280, 200, 35);//
    btn_login->setStyleSheet("QPushButton{background-color: #07C160;border-radius: 2px;border-style: outset;}"
        "QPushButton:hover{background-color:#38CD7F ;}"
        "QPushButton:pressed{background-color:#07C160;");
    btn_login->setText(QStringLiteral("�� ¼"));
    QPalette btn_pal = btn_login->palette();             //startBtn�����Ѿ�����õ�QPushButton����
    btn_pal.setColor(QPalette::ButtonText, Qt::white);    //���ð�ť�ϵ�������ɫ�������Ͽ��ԣ�ʵ���Ͼ��ǿ���
    btn_login->setPalette(btn_pal);

    //�ǳ�
    QLabel* username = new QLabel(this);
    username->setText(QStringLiteral("�� ��"));
    username->setGeometry(115, 140, 50, 30);
    QFont ft;
    ft.setPointSize(14);
    username->setFont(ft);

    //�󶨵�¼��ť
    connect(btn_login, &QPushButton::clicked, this, &loginWidget::btn_login);
}
void loginWidget::btn_login()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "login");  //���ӵ�MYSQL�����ݿ�����
    db.setHostName("localhost");         //������
    db.setPort(3306);                    //�˿�
    db.setDatabaseName("test");          //���ݿ���
    db.setUserName("root");              //�û���
    db.setPassword("123456");            //����
    db.open();

    //�����¼  �����ź�
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