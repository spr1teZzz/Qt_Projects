#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>
//生成随机数
class Generate : public QThread
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
    void recvNum(int num);
protected:
    void run() override;
signals:
    void sendArray(QVector<int> num);
private:
    int m_num;
};

//冒泡排序子线程
class BubbleSort : public QThread
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void recvArray(QVector<int> num);
protected:
    void run() override;
signals:
    void finish(QVector<int> num);
private:
    QVector<int> m_list;
};

//快速排序子线程
class QuickSort : public QThread
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    void recvArray(QVector<int> num);
protected:
    void run() override;
private:
    void quickSort(QVector<int> &,int l, int r);
signals:
    void finish(QVector<int> num);
private:
    QVector<int> m_list;
};

#endif // MYTHREAD_H
