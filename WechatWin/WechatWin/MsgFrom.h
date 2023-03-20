#pragma once
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QLabel>
#include <qDebug>
#include <QImage>
class MsgFrom  : public QWidget
{
	Q_OBJECT

public:
	MsgFrom(int user_id, int from_id, int to_id, QString image_url, QString msg_date, QString content, QWidget* parent = nullptr);
	~MsgFrom();
	int height = 50;
private:
	void initSend();
	void initReceive();
	QLabel* label_date;
	QLabel* label_content;
	QLabel* label_image;
};
