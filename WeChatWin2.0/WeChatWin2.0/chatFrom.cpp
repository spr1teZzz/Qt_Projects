#include "chatFrom.h"

chatFrom::chatFrom(int uid, QString image, QString username, QString date, QString msg, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//����������uid,��֤���ʱ��ȡ,��ʽѡ������
	ui.label_uid->setVisible(false);
	ui.label_uid->setText(QString::number(uid));

	ui.label_image->setStyleSheet("background-image:url("+image+")");
	ui.label_name->setStyleSheet("background-color:#DADBDC;border:none;");
	ui.label_name->setText(username);

	//�ַ���ʡ�Դ���
	QFontMetrics fontWidth(ui.label_msg->font());//�õ�ÿ���ַ��Ŀ��
	QString elideNote = fontWidth.elidedText(msg, Qt::ElideRight, 120);//�����120����
	ui.label_msg->setText(elideNote);//��ʾʡ�Ժõ��ַ���
	ui.label_msg->setStyleSheet("background-color:#DADBDC;border:none;");
	
	//ʱ�䴦��
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString curDate = curDateTime.toString("yyyy-MM-dd");
	QString day = date.mid(0,10);
	//������ͬ,����ʾʱ��
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
