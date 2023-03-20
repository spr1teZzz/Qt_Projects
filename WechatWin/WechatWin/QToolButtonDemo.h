#pragma once

#include <QWidget>
#include "ui_QToolButtonDemo.h"
#include <QtWidgets/QToolButton> 
class QToolButtonDemo : public QWidget
{
	Q_OBJECT

public:
	QToolButtonDemo(QWidget *parent = nullptr);
	~QToolButtonDemo();
private:
	void initForm();
	void signalSlotConnect();
	void selectToolButton(QToolButton* pTlb);

private slots:
	void slotToolButtonChat();
	void slotToolButtonDebug();
	void slotToolButtonParam();
	void slotToolButtonLog(); 
	void slotToolButtonExtern();
	void slotActionShow();

private:
	Ui::QToolButtonDemoClass ui;
};
