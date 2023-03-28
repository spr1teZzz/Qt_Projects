#include "Widget.h"

#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

Widget::Widget(QWidget *parent)
    : QWidget(parent),ui(new Ui::WidgetClass)
{
    ui->setupUi(this);
    //��ʾ����ip
    QString localip = Get_LocalIp();
    ui->lineEdit_IP->setText(localip);
    m_tcpServer = nullptr;
    m_tcpSocket = nullptr;

    //���ó�ʼ״̬�Ͽ����Ӳ�����
    ui->Btn_Disconnect->setEnabled(false);
    //���ö˿�����У��
    ui->lineEdit_Port->setValidator(new QIntValidator(0, 65535));
    //�󶨿�����ť
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
    QString pattern("[a-fA-F0-9]+");//����:����0-9��ĸa-f��A-Fƥ����ڵ���һ��
    QRegExp rx(pattern);
    str = str.replace(' ', "");//ɾ�����пո�
    if (rx.exactMatch(str))//ƥ��
    {
        bool ok;
        int length = str.length();
        if ((length % 2) == 0)//˫��
        {
            for (int i = 0; i < length; i += 2)
            {
                QString str_hex = str.mid(i, 2);//ÿ�����ַ���Ӧһ��hex�ַ���
                ba.append(static_cast<char>(str_hex.toInt(&ok, 16)));//hex�ַ���ת����ֵ
            }
        }
        else//����
        {
            for (int i = 0; i < length - 1; i += 2)
            {
                QString str_hex = str.mid(i, 2);//ÿ�����ַ���Ӧһ��hex�ַ���
                ba.append(static_cast<char>(str_hex.toInt(&ok, 16)));//hex�ַ���ת����ֵ
            }
            //���һ����������
            ba.append(static_cast<char>(str.mid(length - 1, 1).toInt(&ok, 16)));//hex�ַ���ת����ֵ
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
    //str= ba.toHex();//ֱ��ת���м�û�пո�
    for (int i = 0; i < ba.length(); i++)
    {
        unsigned char n = static_cast<unsigned char>((ba.at(i)));
        QString nhex = QByteArray::number(n, 16).toUpper();
        str.append(nhex);
        str.append(' ');//�ֽڼ�ӿո�
    }
}

QString Widget::Get_LocalIp()
{
    QString hostName = QHostInfo::localHostName();            //����������
    QHostInfo hostInfo = QHostInfo::fromName(hostName); //����IP��ַ
    QList<QHostAddress> addList = hostInfo.addresses();      //IP��ַ�б�
    for (int i = 0; i < addList.count(); i++)
    {
        QHostAddress aHost = addList.at(i); //ÿһ����һ��QHostAddress
        if (QAbstractSocket::IPv4Protocol == aHost.protocol())
        {
            return aHost.toString(); //��ʾ��Ip��ַ
        }
    }
    return QString("");
}

void Widget::start_listenServer()
{
    qDebug() << "start_listenServer";
    if (this->m_tcpServer == nullptr)//δ����
    {
        qDebug() << "δ����";
        bool ok = false;
        //��ȡ�����Ķ˿ں�
        quint16 port = ui->lineEdit_Port->text().toUShort(&ok);
        if (!ok)
        {
            QMessageBox::warning(this, "����", "�˿�������������������");
            return;
        }
        //��ȡ������Ip
        QHostAddress ip(ui->lineEdit_IP->text());
        ip.toIPv4Address(&ok);
        if (!ok)
        {
            QMessageBox::warning(this, "����", "ip������������������");
            return;
        }

        m_tcpServer = new MyServer(this);
        //�����߳�
        m_tcpServer->SetThread(ui->spinBox->value() - 1);
        //����1
        bool islisten = m_tcpServer->listen(ip, port);
        if (!islisten)
        {
            QMessageBox::warning(this, "����", m_tcpServer->errorString());
            m_tcpServer->close();
            m_tcpServer->deleteLater();//�ͷ�
            m_tcpServer = nullptr;
            return;
        }
        //����ui
        ui->textEdit_Recv->append("��ʼ����" + QString("[%1��%2]\r\n").arg(ui->lineEdit_IP->text()).arg(ui->lineEdit_Port->text()));//��Ϣ����ʾ��Ϣ
        ui->Btn_Start->setText("ֹͣ");
        ui->lineEdit_IP->setEnabled(false);
        ui->lineEdit_Port->setEnabled(false);
        ui->spinBox->setEnabled(false);
    }
    //ֹͣserver
    else
    {
        qDebug() << "ֹͣserver";
        m_tcpServer->close();
        delete m_tcpServer;
        m_tcpServer = nullptr;
        //����ui
        ui->textEdit_Recv->append("ֹͣ����" + QString("[%1��%2]\r\n").arg(ui->lineEdit_IP->text()).arg(ui->lineEdit_Port->text()));//��Ϣ����ʾ��Ϣ
        ui->Btn_Start->setText("����");
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
    //�ر�socket
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
        QMessageBox::information(this, "��ʾ", "û�н���TCP����");
        return;
    }
    if (ui->comboBox->count() == 1)
    {
        QMessageBox::information(this, "��ʾ", "û�������κοͻ���");
        return;
    }
    QByteArray byteArray;
    QString data = ui->textEdit_Send->toPlainText();
    byteArray = data.toLocal8Bit();
    int n = ui->comboBox->currentIndex();
    if (n == 0)//���͸���������
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
    //���͸�ѡ��Ŀͻ���
    else
    {
        MySocket* mysocket = ui->comboBox->itemData(n).value<MySocket*>();
        if (mysocket != nullptr)
        {
            emit mysocket->WriteMessage(byteArray);
        }
    }
    //��շ��Ͷ�
    ui->textEdit_Send->clear();
}
void Widget::clearRecv()
{
    ui->textEdit_Recv->clear();
}
void Widget::on_add_serverMessage(QString message)
{
    ui->textEdit_Recv->append(message);//��ʾ
    ui->textEdit_Recv->moveCursor(QTextCursor::End);
}


