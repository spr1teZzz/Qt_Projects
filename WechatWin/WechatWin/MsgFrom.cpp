#include "MsgFrom.h"

#define WIDTH 600
#define HEAD_WIDTH  40
#define HEAD_HEIGHT 40

MsgFrom::MsgFrom(int user_id,int from_id, int to_id, QString image_url, QString msg_date,QString content,QWidget* parent)
	: QWidget(parent)
{
	label_date = new QLabel(this);
	label_content = new QLabel(this);
	label_image = new QLabel(this);
	label_image->setStyleSheet("background-image:url(:/img/image/" + image_url + ");");
	label_image->setGeometry(0, 20, HEAD_WIDTH, HEAD_HEIGHT);
	//label_image->setPixmap(QPixmap::fromImage(image_url));
	msg_date = msg_date.mid(0, 4) + "年" + msg_date.mid(5, 2) + "月" + msg_date.mid(8, 2) 
		+ "日" + " " + msg_date.mid(11);
	label_date->setText(msg_date);
	label_date->setGeometry(200, 0, 200, 20);
	qDebug() <<"from_id:"<< from_id << " msg_date:" << msg_date << " content:" << content;
	label_date->setMaximumWidth(250);//设置最大宽度，注意自适应大小时可能小于这个宽度就换行
	label_content->setWordWrap(true);//允许自动换行
	label_content->setText(content);
	label_content->adjustSize();
	label_content->setAlignment(Qt::AlignLeft|Qt::AlignTop);//左上对齐 
	label_content->setStyleSheet("padding-top:3px,padding-right:5px;padding-left:5px;");
	label_content->resize(label_content->width()*1.2, label_content->height() * 1.6f);//把文本的高度调大些，因为控件加入QListyWidget中后文本会被缩短
	label_content->setTextInteractionFlags(Qt::TextSelectableByMouse);//设置鼠标可选中文本
	//label_content->resize(static_cast<int>(strlen(reinterpret_cast<char*>(label_content->text().data()))) * label_content->font().pointSize(),100);

	//从本人发出
	if (from_id == user_id)
	{
		initSend();
	}
	else//本人接收
	{
		initReceive();
	}
	resize(WIDTH, label_content->height()*1.2f > 50 ? label_content->height() * 1.6f : 50);
	height = label_date->height() + label_content->height()*1.6f;
	//this->resize(WIDTH, 200);
}

MsgFrom::~MsgFrom()
{

}

void MsgFrom::initSend()
{
	//发出
	label_image->move(WIDTH- HEAD_WIDTH, 20);
	label_content->move(WIDTH - HEAD_WIDTH - label_content->width()-10, 20);
}

void MsgFrom::initReceive()
{
	//接收
	label_content->move(HEAD_WIDTH, 20);
}
