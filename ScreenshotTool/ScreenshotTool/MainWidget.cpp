#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidgetClass())
{
    ui->setupUi(this);
    connect(ui->Btn_start, &QPushButton::clicked, this, &MainWidget::Btn_start_clicked);
}

MainWidget::~MainWidget()
{
    delete ui;
    exit(0);
}

void MainWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_A && event->modifiers() == (Qt::AltModifier | Qt::ControlModifier)) {
        ScreenWidget::Instance()->showFullScreen();
        ColorWidget::Instance()->show();
    }
    else {
        QWidget::keyPressEvent(event); // 如果不是组合键，则调用基类的方法
    }
}

void MainWidget::Btn_start_clicked()
{
    ScreenWidget::Instance()->showFullScreen();
    ColorWidget::Instance()->show();
}   