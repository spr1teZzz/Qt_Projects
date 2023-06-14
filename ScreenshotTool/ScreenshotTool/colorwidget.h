#pragma once

#include <QWidget>
#include <QMutex>
#include <QKeyEvent>
#include <QApplication>
#include <qdesktopwidget.h>
#include <qDebug>
#include <QTimer>
#include <QScreen>
#include <QtGui>
#include <QLabel>
#include <QPainter>
#include "ui_ColorWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ColorWidgetClass; };
QT_END_NAMESPACE

class ColorWidget : public QWidget
{
	Q_OBJECT

public:
	ColorWidget(QWidget *parent = nullptr);
	~ColorWidget();
	static ColorWidget* Instance();

signals:
	void esc_signal();
protected:
	void keyPressEvent(QKeyEvent* event);
	void mouseReleaseEvent(QMouseEvent*);
private slots:
	void showWidget();
public slots:
	void quit();
private:
	Ui::ColorWidgetClass *ui;
	static ColorWidget* instance;
	QTimer* timer;
};
