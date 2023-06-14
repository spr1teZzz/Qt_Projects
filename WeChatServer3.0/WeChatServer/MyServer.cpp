#include "MyServer.h"
namespace Ui { class WidgetClass; }

#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#define MAX_BYTES_TO_WRITE 65532

MyServer::MyServer(QObject *parent)
	: QTcpServer(parent)
{
    widget = static_cast<Widget*>(parent);
    //���߳��ڴ������󣬲ۺ���������߳���ִ��
    this->sockethelper = new SocketHelper(this);
    //ע���ź�����
    qRegisterMetaType<qintptr>("qintptr");
    //�����źźͲ�
    connect(sockethelper, &SocketHelper::Create, sockethelper, &SocketHelper::CreateSocket);
    connect(sockethelper, &SocketHelper::AddList, this, &MyServer::AddInf);
    connect(sockethelper, &SocketHelper::RemoveList, this, &MyServer::RemoveInf);
}

MyServer::~MyServer()
{
    //�ͷ�����socket
    while (list_information.count() > 0)
    {
        emit list_information[0].mysocket->DeleteSocket();
        list_information.removeAt(0);
    }
    //���combox
    while (this->widget->ui->comboBox->count() > 1) {
        this->widget->ui->comboBox->removeItem(1);
    }

    //�ͷ������߳�
    while (list_thread.count() > 0)
    {
        list_thread[0]->quit();
        list_thread[0]->wait();//�ȴ��˳�
        list_thread[0]->deleteLater();//�ͷ�
        list_thread.removeAt(0);
    }
    //UI�߳����sockethelper
    sockethelper->disconnect();
    delete  this->sockethelper;//
}

void MyServer::SetThread(int num)
{
    for (int i = 0; i < num; i++)
    {
        list_thread.append(new MyThread(this));//�½��߳�
        list_thread[i]->ThreadLoad = 0;//�̸߳��س�ʼ0
        list_thread[i]->start();
    }
}

//��ȡ�������ٵ��߳�����
//-1:UI�߳�
int MyServer::GetMinLoadThread()
{
    //ֻ��1�����߳�
    if (list_thread.count() == 1)
    {
        return 0;
    }
    //������߳�
    else if (list_thread.count() > 1)
    {
        int minload = list_thread[0]->ThreadLoad;
        int index = 0;
        for (int i = 1; i < list_thread.count(); i++)
        {
            if (list_thread[i]->ThreadLoad < minload)
            {
                index = i;
                minload = list_thread[i]->ThreadLoad;
            }
        }
        return index;
    }
    //û�����߳�
    return -1;
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    //��ȡ�������ٵ����߳�����
    int index = GetMinLoadThread();
    if (index != -1)//��UI�߳�ʱ
    {
        //�������߳�����
        emit list_thread[index]->sockethelper->Create(socketDescriptor, index);
    }
    else
    {
        //����UI�߳�����
        emit sockethelper->Create(socketDescriptor, index);
    }
}

void MyServer::AddInf(MySocket* mysocket, int index, int uid) 
{
    if (uid == 0)//������
    {
        SocketInformation inf;
        QString ip = mysocket->peerAddress().toString();
        quint16 port = mysocket->peerPort();
        QString str_inf = QString("[%1:%2 (δ��¼)]").arg(ip).arg(port);
        
        inf.uid = uid;
        inf.str_inf = str_inf;
        inf.mysocket = mysocket;
        inf.threadIndex = index;
        this->list_information.append(inf);
        this->widget->ui->comboBox->addItem(inf.str_inf, QVariant::fromValue(inf.mysocket));
    }
    else//��¼
    {
        QString ip = mysocket->peerAddress().toString();
        quint16 port = mysocket->peerPort();
        QString str_inf = QString("[%1:%2 (uid:%3)]").arg(ip).arg(port).arg(uid);

        //����socket����comboBox�ڵ�ѡ��,�޸�Ϊ����uid��str_inf
        for (int i = 1; i < this->widget->ui->comboBox->count(); i++)
        {
            if (mysocket == this->widget->ui->comboBox->itemData(i).value<MySocket*>())
                this->widget->ui->comboBox->setItemText(i, str_inf);
        }
        
        //�޸�uid��list_information
        for (int i = 0; i < this->list_information.size(); ++i)
        {
            if (mysocket == this->list_information[i].mysocket)
            {
                qDebug() << "�޸ĵ�uid:" << uid;
                this->list_information[i].uid = uid;
            }
        }

    }
}

void MyServer::RemoveInf(MySocket* mysocket)
{
    for (int i = 0; i < this->list_information.count(); i++)
    {
        if (this->list_information[i].mysocket == mysocket)
        {
            this->list_information.removeAt(i);
            this->widget->ui->comboBox->removeItem(i + 1);
            break;
        }
    }
}

//������ת��
void MyServer::Foward(int fid, int tid, QString msg)
{
    //ͨ��tid���Ұ󶨵�socket
    //"type=2@SPRITE@from=1@SPRITE@to=2@SPRITE@@FILE@sanct.log"
    QString prefix = QString("type=2%1from=%2%1to=%3%1").arg(SPLIT).arg(fid).arg(tid);
    //qDebug() << "Foward" << prefix;
    for (int i = 0; i < this->list_information.count(); i++)
    {
        if (this->list_information[i].uid == tid)
        {
            if (msg.startsWith(SE_FILE))
            {
                //��ϢΪ�ļ�
                QString fileName = msg.mid(sizeof(SE_FILE) - 1);
                QString curpath = QDir::currentPath();
                QDir dir(curpath);
                dir.cdUp();
                QString cleanPath = dir.filePath("");
                QString path = QString("%1/downFile/%2").arg(cleanPath).arg(fileName);
                //�����ļ�
                QFile file(path);
                if (!file.exists()) {
                    qDebug() << "File not exists";
                    return;
                }
                if (!file.open(QIODevice::ReadOnly)) {
                    qCritical() << file.errorString();
                    return;
                }
                //��ȡ�ļ���Ϣ
                QFileInfo fileInfo(path);
                qint64 fileSize = file.size();
                QByteArray fileData = file.readAll();
                file.close();
                QString message = prefix + QString("%1\t%2\t%3\t").arg(SE_FILE).arg(fileInfo.fileName()).arg(fileSize);
                //��ʼ�����ļ�
                qDebug() << "�ļ����ͳɹ�size:"<< fileSize;
                this->list_information[i].mysocket->write(message.toUtf8());
                this->list_information[i].mysocket->flush();
                this->list_information[i].mysocket->write(fileData);
                this->list_information[i].mysocket->flush();
                qDebug() << "File:"<<path<< " send successfully"; 
            }
            else if (msg.startsWith(SE_IMAGE))
            {
                QString fileName = msg.mid(sizeof(SE_IMAGE) - 1);
                QString curpath = QDir::currentPath() + "/..";
                QString path = QString("%1/downImage/%2").arg(curpath).arg(fileName);
                QImage image(path);
                QByteArray imageData;
                QBuffer buffer(&imageData);
                image.save(&buffer, "png", 50);
                imageData = imageData.toBase64();
                qint64  size = buffer.size();
                // ����ͼƬ����
                QString message = QString("%1\t%2\t%3\t").arg(SE_IMAGE).arg(fileName).arg(size);
                QString data = prefix + message;
                qDebug() << data;
                this->list_information[i].mysocket->write(data.toUtf8());
                this->list_information[i].mysocket->flush();
                this->list_information[i].mysocket->write(imageData);
                this->list_information[i].mysocket->flush();
            }
            else if (msg.startsWith(SE_TEXT))
            {
                QString text = msg.mid(sizeof(SE_TEXT) - 1);
                QByteArray byteArr = text.toUtf8();
                int size = byteArr.size();
                QString message = QString("%1\tNULL\t%2\t%3").arg(SE_TEXT).arg(size).arg(text);
                QString data = prefix + message;
                qDebug() << data;
                this->list_information[i].mysocket->write(data.toUtf8());
                this->list_information[i].mysocket->flush();
            }
        }
    }
}
