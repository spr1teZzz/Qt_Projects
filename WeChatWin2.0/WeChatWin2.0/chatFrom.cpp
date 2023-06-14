#include "chatFrom.h"
#define SE_IMAGE "@IMAGE@"
#define SE_FILE "@FILE@"
#define SE_TEXT "@TEXT@"

chatFrom::chatFrom(int uid, QString image, QString username, QString date, QString msg, QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);
	//����������uid,��֤���ʱ��ȡ,��ʽѡ������
	ui.label_uid->setVisible(false);
	ui.label_uid->setText(QString::number(uid));

	ui.label_image->setStyleSheet("background-image:url("+image+")");
	ui.label_name->setStyleSheet("background-color:transparent;border:none;");
	ui.label_name->setText(username);

	//�ж�msg������
	//�ַ���ʡ�Դ���

	if (msg.startsWith(SE_TEXT))
	{
		msg = msg.mid(6);
		QFontMetrics fontWidth(ui.label_msg->font());//�õ�ÿ���ַ��Ŀ��
		QString elideNote=fontWidth.elidedText(msg, Qt::ElideRight, 120);//�����120����
		ui.label_msg->setText(elideNote);
	}
	else if (msg.startsWith(SE_FILE))
	{
		//�ļ�����
		ui.label_msg->setText("[�ļ�]");
	}
	else if (msg.startsWith(SE_IMAGE))
	{
		//ͼƬ����
		ui.label_msg->setText("[ͼƬ]");
	}
	
	ui.label_msg->setStyleSheet("background-color: transparent;border:none;");
	
	//ʱ�䴦��
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString curDate = curDateTime.toString("yyyy-MM-dd");
	QString day = date.mid(0,10);
	//������ͬ,����ʾʱ��
	QString hour = date.mid(11, 5);
	//qDebug() <<"curDate:"<<curDate<<" day:"<< day<<" hour : "<<hour;

	if (day == curDate)
	{

		date = hour;
	}
	else if(day != nullptr)
	{
		date = day.mid(2,2)+"/"+ day.mid(5, 2)+"/"+ day.mid(8, 2);
	}
	ui.label_date->setText(date);
	ui.label_date->setStyleSheet("background-color: transparent;border:none;");

	//����δ����Ϣlabel
	unread_count = 0;
	label_unread = new QLabel(ui.label_image);
	label_unread->resize(20, 20);
	label_unread->setAlignment(Qt::AlignRight);
	label_unread->move(ui.label_image->width() - label_unread->width(), 0);
	QPixmap pix(20, 20);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//�����
	painter.setPen(Qt::transparent);
	painter.setBrush(Qt::red);
	painter.drawEllipse(pix.rect());
	QTextOption textop;
	textop.setAlignment(Qt::AlignCenter);
	painter.setPen(Qt::white);
	painter.drawText(pix.rect(), QString::number(unread_count), textop);
	label_unread->setPixmap(pix);
	if (unread_count > 0)
	{
		label_unread->show();
	}
	else
	{
		label_unread->hide();
	}
}

chatFrom::~chatFrom()
{

}

void chatFrom::setCount(int count)
{
	 unread_count = count;
	 if (unread_count > 0)
	 {
		 QPixmap pix(20, 20);
		 pix.fill(Qt::transparent);
		 QPainter painter(&pix);
		 painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//�����
		 painter.setPen(Qt::transparent);
		 painter.setBrush(Qt::red);
		 painter.drawEllipse(pix.rect());
		 QTextOption textop;
		 textop.setAlignment(Qt::AlignCenter);
		 painter.setPen(Qt::white);
		 painter.drawText(pix.rect(), QString::number(unread_count), textop);
		 label_unread->setPixmap(pix);
		 label_unread->show();
	 }
}

int chatFrom::getCount()
{
	return unread_count;
}

void chatFrom::have_read()
{
	unread_count = 0;
	label_unread->hide();
}
