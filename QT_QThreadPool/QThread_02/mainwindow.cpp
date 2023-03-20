#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QThread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //1.创建子线程
    QThread *t1 = new QThread;
    QThread *t2 = new QThread;
    QThread *t3 = new QThread;

    //2.创建任务类的对象
    Generate *gen = new Generate;
    BubbleSort *bubble = new BubbleSort;
    QuickSort *quick = new QuickSort;

    //3.将任务对象移动到某个子线程中
    gen->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);

    //4.启动子线程
    connect(this,&MainWindow::starting,gen,&Generate::working);
    connect(ui->startBtn,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        t1->start();
    });

    //5.绑定线程
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::working);
    connect(gen,&Generate::sendArray,quick,&QuickSort::working);

    //6.接收子线程发送的数据并开启排序线程
    connect(gen,&Generate::sendArray,this,[=](QVector<int>list){
        t2->start();
        t3->start();
        for(int i=0;i<list.size();++i)
        {
            ui->randomList->addItem(QString::number(list.at(i)));
        }
    });


    //7.显示到界面
    connect(bubble,&BubbleSort::finish,this,[=](QVector<int>list){
        for(int i=0;i<list.size();++i)
        {
            ui->bubbleList->addItem(QString::number(list.at(i)));
        }
    });
    connect(quick,&QuickSort::finish,this,[=](QVector<int>list){
        for(int i=0;i<list.size();++i)
        {
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });

    //回收资源
    connect(this,&MainWindow::destroyed,this,[=](){
        t1->quit();
        t1->wait();
        t1->deleteLater();//delete t1

        t2->quit();
        t2->wait();
        t2->deleteLater();//delete t2

        t3->quit();
        t3->wait();
        t3->deleteLater();//delete t3

        gen->deleteLater();
        bubble->deleteLater();
        quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

