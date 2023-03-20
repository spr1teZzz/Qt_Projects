#pragma once

#include <QWidget>
#include "ui_chatFrom.h"
#include<QString>
#include<qDebug>
#include<QDateTime>
class chatFrom : public QWidget
{
	Q_OBJECT

public:
	chatFrom(int uid,QString image, QString username, QString date, QString msg,QWidget *parent = nullptr);
	~chatFrom();

private:
	Ui::chatFromClass ui;
};
