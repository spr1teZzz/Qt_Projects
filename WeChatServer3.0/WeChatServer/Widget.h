#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QButtonGroup>
#include <QHostInfo>
#include <QMessageBox>
#include "ui_Widget.h"
#include "MyServer.h"
#include "MySocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetClass; }
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = 0);
    ~Widget();
    Ui::WidgetClass *ui;

    bool m_serverHexSend;//tcp服务器hex发送标志
    bool HexStringToByte(QString& str, QByteArray& ba);//16进制字符串转字节数组
    void ByteToHexString(QString& str, QByteArray& ba);//字节数组转16进制字符串
    QString Get_LocalIp();//获取本地IP
public slots:
    void on_add_serverMessage(QString message);
    void start_listenServer();
    void IndexChanged(int index);
    void serverCloseSocket();
    void clearSend();
    void serverSend();
    void clearRecv();
private:
    MyServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;
};
