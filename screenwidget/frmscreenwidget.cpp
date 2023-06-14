#include "frmscreenwidget.h"
#include "ui_frmscreenwidget.h"
#include "screenwidget.h"

frmScreenWidget::frmScreenWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmScreenWidget)
{
    ui->setupUi(this);
}

frmScreenWidget::~frmScreenWidget()
{
    delete ui;
    exit(0); 
}

void frmScreenWidget::on_pushButton_clicked()
{
    ScreenWidget::Instance()->showFullScreen();
}

void frmScreenWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A  &&  event->modifiers() == (Qt::AltModifier | Qt::ControlModifier)) {
       ScreenWidget::Instance()->showFullScreen();
    } else {
        QWidget::keyPressEvent(event); // 如果不是组合键，则调用基类的方法
    }
}
