#pragma once
#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"
#include "Client.h"
#include "chatFrom.h"
#include "loginwidget.h"
#include "MsgFrom.h"
#include <qdebug.h>
#include <QString>
#include <QTextCodec>
#include <qdesktopwidget.h>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidgetItem>
#include <QDateTime>
#include <qimage.h>
#include <QLayout>
#include <QMenu>
#include <QPair>
#include <QVector>
#include <QMouseEvent>
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    QMap<int, userInfo> userinfo_map;
    QMap<int, QList<Message>> message_map;
    int user_uid;
    QString user_url;
    Client *send_client;
	QPoint curPos;
	bool isPressed;
	bool isMaxWin;
signals:
    void closeLoginWindow();
public slots:
    void rcvLogin(int, QString, QMap<int, userInfo>, QMap<int, QList<Message>>);
    void updateShowList(QString);

	void slotToolButtonChat();
	void slotToolButtonAddressBook();
	void slotToolButtonCollect();
	void slotToolButtonFile();
	void slotToolButtonFriends();
	void slotToolButtonLook();
	void slotToolButtonSearch();
	void slotToolButtonProgram();
	void slotToolButtonPhone();
	void slotToolButtonSettings();
	void slotActionShow();
	void closeWindow();
	void minWindow();
	void maxWindow();
	void topWindow();
	void selectListWidgetItem(QListWidgetItem* item);
private:


    Ui::MainWidgetClass ui;
	int label_uid;
    void initForm();
    void signalSlotConnect();
    void selectToolButton(QToolButton* toolButton);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
};

//class listwidgetItem :public QListWidgetItem
//{
//public:
//	bool operator<(const QListWidgetItem& other) const
//	{
//		QWidget* Widget = ui.listWidget->itemWidget(this);
//		QLabel* label_name = Widget->findChild<QLabel*>("label_name");
//		double a, b;
//		a = this->data(Qt::UserRole).toDouble();
//		b = other.data(Qt::UserRole).toDouble();
//		return a < b;
//	}
//};
