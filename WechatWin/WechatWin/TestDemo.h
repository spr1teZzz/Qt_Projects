#pragma once
#include "framelesswidget.h"
#include <qwidget.h>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
class TestDemo  : public FramelessWidget
{
	Q_OBJECT

public:
	TestDemo(QWidget *parent = nullptr);
	~TestDemo();
};
