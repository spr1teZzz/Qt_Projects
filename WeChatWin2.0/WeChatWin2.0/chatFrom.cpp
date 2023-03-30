#include "chatFrom.h"

chatFrom::chatFrom(int uid, QString image, QString username, QString date, QString msg, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//处理传过来的uid,保证点击时获取,样式选择隐藏
	ui.label_uid->setVisible(false);
	ui.label_uid->setText(QString::number(uid));

	ui.label_image->setStyleSheet("background-image:url("+image+")");
	ui.label_name->setStyleSheet("background-color:#DADBDC;border:none;");
	ui.label_name->setText(username);

	//字符串省略处理
	QFontMetrics fontWidth(ui.label_msg->font());//得到每个字符的宽度
	QString elideNote = fontWidth.elidedText(msg, Qt::ElideRight, 120);//最大宽度120像素
	ui.label_msg->setText(elideNote);//显示省略好的字符串
	ui.label_msg->setStyleSheet("background-color:#DADBDC;border:none;");
	
	//时间处理
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString curDate = curDateTime.toString("yyyy-MM-dd");
	QString day = date.mid(0,10);
	//日期相同,则显示时间
	QString hour = date.mid(11, 5);
	qDebug() <<"curDate:"<<curDate<<" day:"<< day<<" hour : "<<hour;

	if (day == curDate)
	{

		date = hour;
	}
	else if(day != nullptr)
	{
		date = day.mid(2,2)+"/"+ day.mid(5, 2)+"/"+ day.mid(8, 2);
	}
	ui.label_date->setText(date);
	ui.label_date->setStyleSheet("background-color:#DADBDC;border:none;");
}

chatFrom::~chatFrom()
{}
