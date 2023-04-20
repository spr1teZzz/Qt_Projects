#pragma once

#include <QWidget>
#include "ui_chatFrom.h"
#include<QString>
#include<qDebug>
#include<QDateTime>
#include <QLabel>
#include <QPainter>
class chatFrom : public QWidget
{
	Q_OBJECT

public:
	chatFrom(int uid,QString image, QString username, QString date, QString msg,QWidget *parent = nullptr);
	~chatFrom();
	//����δ����Ϣ����
	void setCount(int count);
	int getCount();
	//�Ѷ�����
	void have_read();
private:
	QLabel* label_unread;
	int unread_count;
	Ui::chatFromClass ui;
};
