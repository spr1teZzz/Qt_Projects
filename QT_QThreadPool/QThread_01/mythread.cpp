#include "mythread.h"
#include <QElapsedTimer>//计算程序运行时间的头文件
#include <QDebug>
Generate::Generate(QObject *parent) : QThread(parent)
{

}

void Generate::recvNum(int num)
{
    m_num = num;
}

void Generate::run()
{
    qDebug()<<"生成随机数的线程的线程地址:"<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for(int i=0;i<m_num;++i)
    {
        list.push_back(qrand()%100000);
    }
    int milsec = time.elapsed();//执行程序所要的时间
    qDebug()<<"生成"<<m_num<<"个随机数共用时:"<<milsec<<"毫秒";
    emit sendArray(list);
}

BubbleSort::BubbleSort(QObject *parent):QThread(parent)
{

}

void BubbleSort::recvArray(QVector<int> num)
{
    m_list = num;
}

void BubbleSort::run()
{
    qDebug()<<"冒泡排序线程地址:"<<QThread::currentThread();
    QElapsedTimer time;
     time.start();
     int temp;
     for (int i = 0; i < m_list.size()-1;i++) {                  //共进行9步
         for (int j = 0; j < m_list.size()-1-i;j++) {      //在每一步进行10-i次两两比较
             if (m_list[j] > m_list[j + 1]) {
                 temp = m_list[j];
                 m_list[j] = m_list[j + 1];
                 m_list[j + 1] = temp;
             }
         }
     }
    int milsec = time.elapsed();//执行程序所要的时间
    qDebug()<<"冒泡排序共用时:"<<milsec<<"毫秒";
    emit finish(m_list);
}

QuickSort::QuickSort(QObject *parent):QThread(parent)
{

}

void QuickSort::recvArray(QVector<int> num)
{
    m_list = num;
}

void QuickSort::run()
{
    qDebug()<<"快速排序线程地址:"<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quickSort(m_list,0,m_list.size()-1);
    int milsec = time.elapsed();//执行程序所要的时间
    qDebug()<<"快速排序共用时:"<<milsec<<"毫秒";
    emit finish(m_list);
}


//快速排序（从小到大）
void QuickSort::quickSort(QVector<int> &arr,int left, int right)
{
    if(left >= right)
        return;
    int i, j, base, temp;
    i = left, j = right;
    base = arr[left];  //取最左边的数为基准数
    while (i < j)
    {
        while (arr[j] >= base && i < j)
            j--;
        while (arr[i] <= base && i < j)
            i++;
        if(i < j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    //基准数归位
    arr[left] = arr[i];
    arr[i] = base;
    quickSort(arr,left, i - 1 );//递归左边
    quickSort(arr,i + 1, right);//递归右边
}
