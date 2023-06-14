#pragma once

/**
 * ȫ�ֽ����ؼ�
 * 1. ����Ҽ������˵���
 * 2. ֧��ȫ�ֽ�����
 * 3. ֧�־ֲ�������
 * 4. ֧�ֽ�ͼ�����϶���
 * 5. ֧��ͼƬ���Ϊ��
 */

#include <QWidget>
#include <QMenu>
#include <QPoint>
#include <QSize>
#include <QMutex>
#include <QLabel>
#include "qmutex.h"
#include "qapplication.h"
#include "qpainter.h"
#include "qfiledialog.h"
#include "qevent.h"
#include "qdatetime.h"
#include "qstringlist.h"
#include "qdebug.h"
#include "colorwidget.h"
class Screen
{
public:
    enum STATUS { SELECT, MOV, SET_W_H };
    Screen() {}
    Screen(QSize size);

    void setStart(QPoint pos);
    void setEnd(QPoint pos);
    QPoint getStart();
    QPoint getEnd();

    QPoint getLeftUp();
    QPoint getRightDown();

    STATUS getStatus();
    void setStatus(STATUS status);

    int width();
    int height();

    //���������Ƿ��ڽ�ͼ������
    bool isInArea(QPoint pos);
    //�������ƶ���ͼ����
    void move(QPoint p);

private:
    //��¼ ��ͼ���� ���Ͻǡ����½�
    QPoint leftUpPos, rightDownPos;
    //��¼ ��꿪ʼλ�á�����λ��
    QPoint startPos, endPos;
    //��¼��Ļ��С
    int maxWidth, maxHeight;
    //����״̬: ѡ�������ƶ���������width height
    STATUS status;

    //�Ƚ���λ�ã��ж����Ͻǡ����½�
    void cmpPoint(QPoint& s, QPoint& e);

};

#ifdef quc
class Q_DECL_EXPORT ScreenWidget : public QWidget
#else
class ScreenWidget : public QWidget
#endif

{
    Q_OBJECT
public:
    static ScreenWidget* Instance();
    explicit ScreenWidget(QWidget* parent = 0);

private:
    static QScopedPointer<ScreenWidget> self;
    QMenu* menu;            //�Ҽ��˵�����
    Screen* screen;         //��������
    QPixmap* fullScreen;    //����ȫ��ͼ��
    QPixmap* bgScreen;      //ģ������ͼ
    QPoint movPos;          //����

signals:
    void colorwidget_signal();
    void mainShow_signal();
protected:
    void contextMenuEvent(QContextMenuEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
    void showEvent(QShowEvent*);
    void keyPressEvent(QKeyEvent* event);
private slots:
    void saveScreen();
    void saveFullScreen();
    void saveScreenOther();
    void saveFullOther();
    void quit();
};
