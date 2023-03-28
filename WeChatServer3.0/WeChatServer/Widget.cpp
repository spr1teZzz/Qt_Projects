#include "Widget.h"

#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

Widget::Widget(QWidget *parent)
    : QWidget(parent),ui(new Ui::WidgetClass)
{
    ui->setupUi(this);
    //显示本地ip
    QString localip = Get_LocalIp();
    ui->lineEdit_IP->setText(localip);
    m_tcpServer = nullptr;
    m_tcpSocket = nullptr;

    //设置初始状态断开连接不可用
    ui->Btn_Disconnect->setEnabled(false);
    //设置端口输入校验
    ui->lineEdit_Port->setValidator(new QIntValidator(0, 65535));
    //绑定开启按钮
    connect(ui->Btn_Start, &QPushButton::clicked, this, &Widget::start_listenServer);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(IndexChanged(int)));
    connect(ui->Btn_Disconnect, &QPushButton::clicked, this, &Widget::serverCloseSocket);
    connect(ui->Btn_ClearSend, &QPushButton::clicked, this, &Widget::clearSend);
    connect(ui->Btn_SendMsg, &QPushButton::clicked, this, &Widget::serverSend);
    connect(ui->Btn_ClearRecv, &QPushButton::clicked, this, &Widget::clearRecv);
}
Widget::~Widget()
{
    qDebug() << "~Widget";
    if (m_tcpServer != nullptr)
    {
        m_tcpServer->close();
        delete m_tcpServer;
    }

    if (m_tcpSocket != nullptr)
    {
        m_tcpSocket->abort();
        delete m_tcpSocket;
    }
    delete ui;
}

bool Widget::HexStringToByte(QString& str, QByteArray& ba)
{
    QString pattern("[a-fA-F0-9]+");//正则:数字0-9字母a-f、A-F匹配大于等于一次
    QRegExp rx(pattern);
    str = str.replace(' ', "");//删除所有空格
    if (rx.exactMatch(str))//匹配
    {
        bool ok;
        int length = str.length();
        if ((length % 2) == 0)//双数
        {
            for (int i = 0; i < length; i += 2)
            {
                QString str_hex = str.mid(i, 2);//每两个字符对应一个hex字符串
                ba.append(static_cast<char>(str_hex.toInt(&ok, 16)));//hex字符串转整数值
            }
        }
        else//单数
        {
            for (int i = 0; i < length - 1; i += 2)
            {
                QString str_hex = str.mid(i, 2);//每两个字符对应一个hex字符串
                ba.append(static_cast<char>(str_hex.toInt(&ok, 16)));//hex字符串转整数值
            }
            //最后一个单独处理
            ba.append(static_cast<char>(str.mid(length - 1, 1).toInt(&ok, 16)));//hex字符串转整数值
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Widget::ByteToHexString(QString& str, QByteArray& ba)
{
    //str= ba.toHex();//直接转换中间没有空格
    for (int i = 0; i < ba.length(); i++)
    {
        unsigned char n = static_cast<unsigned char>((ba.at(i)));
        QString nhex = QByteArray::number(n, 16).toUpper();
        str.append(nhex);
        str.append(' ');//字节间加空格
    }
}

QString Widget::Get_LocalIp()
{
    QString hostName = QHostInfo::localHostName();            //本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName); //本机IP地址
    QList<QHostAddress> addList = hostInfo.addresses();      //IP地址列表
    for (int i = 0; i < addList.count(); i++)
    {
        QHostAddress aHost = addList.at(i); //每一项是一个QHostAddress
        if (QAbstractSocket::IPv4Protocol == aHost.protocol())
        {
            return aHost.toString(); //显示出Ip地址
        }
    }
    return QString("");
}

void Widget::start_listenServer()
{
    qDebug() << "start_listenServer";
    if (this->m_tcpServer == nullptr)//未连接
    {
        qDebug() << "未连接";
        bool ok = false;
        //获取监听的端口号
        quint16 port = ui->lineEdit_Port->text().toUShort(&ok);
        if (!ok)
        {
            QMessageBox::warning(this, "错误", "端口设置有误，请重新输入");
            return;
        }
        //获取监听的Ip
        QHostAddress ip(ui->lineEdit_IP->text());
        ip.toIPv4Address(&ok);
        if (!ok)
        {
            QMessageBox::warning(this, "错误", "ip设置有误，请重新输入");
            return;
        }

        m_tcpServer = new MyServer(this);
        //设置线程
        m_tcpServer->SetThread(ui->spinBox->value() - 1);
        //监听1
        bool islisten = m_tcpServer->listen(ip, port);
        if (!islisten)
        {
            QMessageBox::warning(this, "错误", m_tcpServer->errorString());
            m_tcpServer->close();
            m_tcpServer->deleteLater();//释放
            m_tcpServer = nullptr;
            return;
        }
        //更新ui
        ui->textEdit_Recv->append("开始监听" + QString("[%1：%2]\r\n").arg(ui->lineEdit_IP->text()).arg(ui->lineEdit_Port->text()));//消息框提示信息
        ui->Btn_Start->setText("停止");
        ui->lineEdit_IP->setEnabled(false);
        ui->lineEdit_Port->setEnabled(false);
        ui->spinBox->setEnabled(false);
    }
    //停止server
    else
    {
        qDebug() << "停止server";
        m_tcpServer->close();
        delete m_tcpServer;
        m_tcpServer = nullptr;
        //更新ui
        ui->textEdit_Recv->append("停止监听" + QString("[%1：%2]\r\n").arg(ui->lineEdit_IP->text()).arg(ui->lineEdit_Port->text()));//消息框提示信息
        ui->Btn_Start->setText("监听");
        ui->lineEdit_IP->setEnabled(true);
        ui->lineEdit_Port->setEnabled(true);
        ui->spinBox->setEnabled(true);
    }
}
void Widget::IndexChanged(int index)
{
    ui->Btn_Disconnect->setEnabled(0 == index ? false : true);
}
void Widget::serverCloseSocket()
{
    int index = ui->comboBox->currentIndex();
    if (index == 0) return;
    //关闭socket
    emit m_tcpServer->list_information[index - 1].mysocket->DeleteSocket();
}
void Widget::clearSend()
{
    ui->textEdit_Send->clear();
}
void Widget::serverSend()
{
    if (m_tcpServer != nullptr && !m_tcpServer->isListening())
    {
        QMessageBox::information(this, "提示", "没有建立TCP连接");
        return;
    }
    if (ui->comboBox->count() == 1)
    {
        QMessageBox::information(this, "提示", "没有连接任何客户端");
        return;
    }
    QByteArray byteArray;
    QString data = ui->textEdit_Send->toPlainText();
    byteArray = data.toLocal8Bit();
    int n = ui->comboBox->currentIndex();
    if (n == 0)//发送给所有连接
    {
        for (int i = 1; i < ui->comboBox->count(); i++)
        {
            MySocket* mysocket = ui->comboBox->itemData(i).value<MySocket*>();
            if (mysocket != nullptr)
            {
                emit mysocket->WriteMessage(byteArray);
            }
        }
    }
    //发送给选择的客户端
    else
    {
        MySocket* mysocket = ui->comboBox->itemData(n).value<MySocket*>();
        if (mysocket != nullptr)
        {
            emit mysocket->WriteMessage(byteArray);
        }
    }
    //清空发送端
    ui->textEdit_Send->clear();
}
void Widget::clearRecv()
{
    ui->textEdit_Recv->clear();
}
void Widget::on_add_serverMessage(QString message)
{
    ui->textEdit_Recv->append(message);//显示
    ui->textEdit_Recv->moveCursor(QTextCursor::End);
}


