#pragma once

#include <QtWidgets/QMainWindow>
#include <qDebug>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QTime>
#include <QFileDialog>
#include <QScreen>
#include <QDir>
#include <QMessageBox>
#include <QVideoFrame>
#include "ui_mainwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidgetClass; };
QT_END_NAMESPACE

#define PADDING 2
enum Direction { UP = 0, DOWN = 1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void region(const QPoint& currentGlobalPoint);  //����λ��,�ı���
protected:
    //��갴���ƶ����ͷ��¼�
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
private slots:
    void window_close();
    void play_video();
    void OnSetMediaFile(void);//������Ƶ�ļ�
    void OnSlider(qint64); // �ź����ݵ�λ���Ѹ���Ϊλ�ã��Ժ����ʾ��������ҲҪ��
    void OnDurationChanged(qint64);// �źű�ʾ���ݵĳ���ʱ���Ѹ���Ϊʱ�����Ժ����ʾ�������� �����ֵ����Сֵ
    void OnStateChanged(QMediaPlayer::State);// Player�����״̬�Ѿ��ı�
    void onItemClicked(QListWidgetItem*);//�����ļ�����¼�
    void voice_control(int value);//����������С
    void muteAndrecover();//��������
    void window_max();//�������
private:
    Ui::MainWidgetClass *ui;
    void soltInit();//��ʼ���ۺ���
    void uiInit();//�����ʼ��
    void showFiles(QString);//��ʾ��ǰ�ļ���
    QMediaPlayer* player;
    bool playFlag;// ����/��ͣ��־
    bool loadFlag;// �����ļ���־
    bool voiceFlag;// ������־
    bool maxFlag;//���ڻ���־
    QPoint m_movePoint;  //����λ��
    bool isLeftPressDown;  // �ж�����Ƿ���
    Direction dir;        // ���ڴ�С�ı�ʱ����¼�ı䷽��
    QPoint m_dragPosition;
    QString m_currentPath;//��ǰ·��

};
