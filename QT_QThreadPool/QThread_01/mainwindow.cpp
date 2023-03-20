#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //1.创建子线程
    Generate *gen = new Generate;
    BubbleSort *bubble = new BubbleSort;
    QuickSort *quick = new QuickSort;
    //2.启动子线程
    connect(this,&MainWindow::starting,gen,&Generate::recvNum);
    connect(ui->startBtn,&QPushButton::clicked,this,[=](){
        emit starting(10000);
        gen->start();
    });

    //3.绑定线程
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::recvArray);
    connect(gen,&Generate::sendArray,quick,&QuickSort::recvArray);
    //3.接收子线程发送的数据并开启排序线程
    connect(gen,&Generate::sendArray,this,[=](QVector<int>list){
        bubble->start();
        quick->start();
        for(int i=0;i<list.size();++i)
        {
            ui->randomList->addItem(QString::number(list.at(i)));
        }
    });


    //显示到界面
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
        gen->quit();
        gen->wait();
        gen->deleteLater();//delete gen

        bubble->quit();
        bubble->wait();
        bubble->deleteLater();//delete bubble

        quick->quit();
        quick->wait();
        quick->deleteLater();//delete quick
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

