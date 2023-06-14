#pragma once
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QLabel>
#include <qDebug>
#include <QImage>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QMovie>
#include <QPainter>
#include <QDateTime>
#include <QDir>
#include <QFileIconProvider>
#include "textlabel.h"
class MsgFrom  : public QWidget
{
	Q_OBJECT

public:
	MsgFrom(QString url, QWidget* parent = nullptr);
	~MsgFrom();

	enum User_Type {
		User_System,//系统
		User_Me,    //自己
		User_Other,   //用户
		User_Time,  //时间
	};
	void setTextSuccess();
	void setText(QString text, QString time, QSize allSize, User_Type userType);
	//指定字体下的最优大小的函数
	QSize getRealString(QString src);
	//计算聊天气泡界面中各个控件的位置和大小
	QSize fontRect(QString str);
	inline QString text() { return m_msg; }
	inline QString time() { return m_time; }
	inline User_Type userType() { return m_userType; }
protected:
	void paintEvent(QPaintEvent* event);
private:
	QString m_msg;
	QString m_time;
	QString m_curTime;

	QSize m_allSize;
	User_Type m_userType = User_System;

	int m_kuangWidth;
	int m_textWidth;
	int m_spaceWid;
	int m_lineHeight;

	QRect m_iconLeftRect;
	QRect m_iconRightRect;
	QRect m_sanjiaoLeftRect;
	QRect m_sanjiaoRightRect;
	QRect m_kuangLeftRect;
	QRect m_kuangRightRect;
	QRect m_textLeftRect;
	QRect m_textRightRect;
	QPixmap m_pixmap;
	QLabel* m_loading = Q_NULLPTR;
	QMovie* m_loadingMovie = Q_NULLPTR;
	bool m_isSending = false;
};
