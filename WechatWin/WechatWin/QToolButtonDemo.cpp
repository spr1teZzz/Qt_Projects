#include "QToolButtonDemo.h"
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QMessageBox>
#include <QLabel>
#include <QPixmap>
QToolButtonDemo::QToolButtonDemo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initForm();
	signalSlotConnect();
}
// ��ʼ������
void QToolButtonDemo::initForm()
{
	//ui.verticalLayout->addSpacing(1);
	
	// ����toolbutton��ѡ��״̬
	ui.tlbDebug->setCheckable(true);
	ui.tlbExtern->setCheckable(true);
	ui.tlbLog->setCheckable(true);
	ui.tlbParam->setCheckable(true);
	ui.tlbChat->setCheckable(true);



	QIcon icon01(":img/image/01.png");
	ui.tlbChat->setIcon(icon01);


	// ����Ĭ��ѡ�г���
	ui.tlbChat->setChecked(true);
	ui.stackedWidget->setCurrentIndex(0);

	// ������չ�����˵�
	ui.tlbExtern->setPopupMode(QToolButton::InstantPopup);
	auto externMenu = new QMenu(ui.tlbExtern);
	auto controlAction = new QAction(QString::fromLocal8Bit("�豸����   "), externMenu);
	auto videoAction = new QAction(QString::fromLocal8Bit("��Ƶ���  "), externMenu);
	auto systemCopyAction = new QAction(QString::fromLocal8Bit("ϵͳ����  "), externMenu);

	// ��Ӳ˵�
	externMenu->addAction(controlAction);
	externMenu->addAction(videoAction);
	externMenu->addAction(systemCopyAction);

	// �����źŲ�����
	connect(controlAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
	connect(videoAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
	connect(systemCopyAction, SIGNAL(triggered()), this, SLOT(slotActionShow()));
	ui.tlbExtern->setMenu(externMenu);

}

// �źŲ�����
void QToolButtonDemo::signalSlotConnect()
{
	connect(ui.tlbChat, SIGNAL(clicked()), this, SLOT(slotToolButtonProgram()));
	connect(ui.tlbDebug, SIGNAL(clicked()), this, SLOT(slotToolButtonDebug()));
	connect(ui.tlbExtern, SIGNAL(clicked()), this, SLOT(slotToolButtonExtern()));
	connect(ui.tlbParam, SIGNAL(clicked()), this, SLOT(slotToolButtonParam()));
	connect(ui.tlbLog, SIGNAL(clicked()), this, SLOT(slotToolButtonLog()));
}


void QToolButtonDemo::slotToolButtonChat()
{
	selectToolButton(ui.tlbChat);
}

void QToolButtonDemo::slotToolButtonDebug()
{
	selectToolButton(ui.tlbDebug);
}

void QToolButtonDemo::slotToolButtonParam()
{
	selectToolButton(ui.tlbParam);
}

void QToolButtonDemo::slotToolButtonLog()
{
	selectToolButton(ui.tlbLog);
}

void QToolButtonDemo::slotToolButtonExtern()
{
	selectToolButton(ui.tlbExtern);
}

void QToolButtonDemo::slotActionShow()
{
	QMessageBox::information(this, QString::fromLocal8Bit("�����˵���ʾ"), QString::fromLocal8Bit("����ѡ�񴥷�"), QMessageBox::Yes);
}

// ����ѡ��
void QToolButtonDemo::selectToolButton(QToolButton* pTlb)
{
	if (ui.tlbChat == pTlb)
	{
		ui.stackedWidget->setCurrentIndex(0);
		ui.tlbChat->setChecked(true);
		ui.tlbDebug->setChecked(false);
		ui.tlbParam->setChecked(false);
		ui.tlbLog->setChecked(false);
		ui.tlbExtern->setChecked(false);

	}
	else if (ui.tlbDebug == pTlb)
	{
		ui.stackedWidget->setCurrentIndex(1);
		ui.tlbChat->setChecked(false);
		ui.tlbDebug->setChecked(true);
		ui.tlbParam->setChecked(false);
		ui.tlbLog->setChecked(false);
		ui.tlbExtern->setChecked(false);
	}
	else if (ui.tlbParam == pTlb)
	{
		ui.stackedWidget->setCurrentIndex(2);
		ui.tlbChat->setChecked(false);
		ui.tlbDebug->setChecked(false);
		ui.tlbParam->setChecked(true);
		ui.tlbLog->setChecked(false);
		ui.tlbExtern->setChecked(false);
	}
	else if (ui.tlbLog == pTlb)
	{
		ui.stackedWidget->setCurrentIndex(3);
		ui.tlbChat->setChecked(false);
		ui.tlbDebug->setChecked(false);
		ui.tlbParam->setChecked(false);
		ui.tlbLog->setChecked(true);
		ui.tlbExtern->setChecked(false);
	}
	else if (ui.tlbExtern == pTlb)
	{
		ui.stackedWidget->setCurrentIndex(4);
		ui.tlbChat->setChecked(false);
		ui.tlbDebug->setChecked(false);
		ui.tlbParam->setChecked(false);
		ui.tlbLog->setChecked(false);
		ui.tlbExtern->setChecked(true);
	}
}

QToolButtonDemo::~QToolButtonDemo()
{}
