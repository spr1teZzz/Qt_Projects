#include "MyServer.h"
namespace Ui { class WidgetClass; }

#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

MyServer::MyServer(QObject *parent)
	: QTcpServer(parent)
{
    widget = static_cast<Widget*>(parent);
    //在线程内创建对象，槽函数在这个线程中执行
    this->sockethelper = new SocketHelper(this);
    //注册信号类型
    qRegisterMetaType<qintptr>("qintptr");
    //连接信号和槽
    connect(sockethelper, &SocketHelper::Create, sockethelper, &SocketHelper::CreateSocket);
    connect(sockethelper, &SocketHelper::AddList, this, &MyServer::AddInf);
    connect(sockethelper, &SocketHelper::RemoveList, this, &MyServer::RemoveInf);
}

MyServer::~MyServer()
{
    //释放所有socket
    while (list_information.count() > 0)
    {
        emit list_information[0].mysocket->DeleteSocket();
        list_information.removeAt(0);
    }
    //清空combox
    while (this->widget->ui->comboBox->count() > 1) {
        this->widget->ui->comboBox->removeItem(1);
    }

    //释放所有线程
    while (list_thread.count() > 0)
    {
        list_thread[0]->quit();
        list_thread[0]->wait();//等待退出
        list_thread[0]->deleteLater();//释放
        list_thread.removeAt(0);
    }
    //UI线程里的sockethelper
    sockethelper->disconnect();
    delete  this->sockethelper;//
}

void MyServer::SetThread(int num)
{
    for (int i = 0; i < num; i++)
    {
        list_thread.append(new MyThread(this));//新建线程
        list_thread[i]->ThreadLoad = 0;//线程负载初始0
        list_thread[i]->start();
    }
}

//获取负载最少的线程索引
//-1:UI线程
int MyServer::GetMinLoadThread()
{
    //只有1个子线程
    if (list_thread.count() == 1)
    {
        return 0;
    }
    //多个子线程
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
    //没有子线程
    return -1;
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    //获取负载最少的子线程索引
    int index = GetMinLoadThread();
    if (index != -1)//非UI线程时
    {
        //交给子线程运行
        emit list_thread[index]->sockethelper->Create(socketDescriptor, index);
    }
    else
    {
        //交给UI线程运行
        emit sockethelper->Create(socketDescriptor, index);
    }
}




void MyServer::AddInf(MySocket* mysocket, int index,int uid) 
{
    if (uid == 0)//新连接
    {
        SocketInformation inf;
        QString ip = mysocket->peerAddress().toString();
        quint16 port = mysocket->peerPort();
        QString str_inf = QString("[%1:%2 (未登录)]").arg(ip).arg(port);
        
        inf.uid = uid;
        inf.str_inf = str_inf;
        inf.mysocket = mysocket;
        inf.threadIndex = index;
        this->list_information.append(inf);
        this->widget->ui->comboBox->addItem(inf.str_inf, QVariant::fromValue(inf.mysocket));
    }
    else//登录
    {
        QString ip = mysocket->peerAddress().toString();
        quint16 port = mysocket->peerPort();
        QString str_inf = QString("[%1:%2 (uid:%3)]").arg(ip).arg(port).arg(uid);
        for (int i = 1; i < this->widget->ui->comboBox->count(); i++)
        {
            if (mysocket == this->widget->ui->comboBox->itemData(i).value<MySocket*>())
                this->widget->ui->comboBox->setItemText(i, str_inf);
        }
        
        //修改uid至list_information
        for (int i = 0; i < this->list_information.size(); ++i)
        {
            if (mysocket == this->list_information[i].mysocket)
            {
                qDebug() << "修改的uid:" << uid;
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

//服务器转发
void MyServer::Foward(int fid, int tid, QString msg)
{
    //通过tid查找绑定的socket
    QString data = "type=2&fid=" + QString::number(fid) + "&tid=" + QString::number(tid) + "&" + msg;
    QByteArray byteArray = data.toLocal8Bit();
    qDebug() << "Foward" << data;
    for (int i = 0; i < this->list_information.count(); i++)
    {
        if (this->list_information[i].uid == tid)
        {
            this->list_information[i].mysocket->WriteMessage(byteArray);
        }
    }
}
