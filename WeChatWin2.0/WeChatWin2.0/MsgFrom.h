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
		User_System,//ϵͳ
		User_Me,    //�Լ�
		User_Other,   //�û�
		User_Time,  //ʱ��
	};
	void setTextSuccess();
	void setText(QString text, QString time, QSize allSize, User_Type userType);
	//ָ�������µ����Ŵ�С�ĺ���
	QSize getRealString(QString src);
	//�����������ݽ����и����ؼ���λ�úʹ�С
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
