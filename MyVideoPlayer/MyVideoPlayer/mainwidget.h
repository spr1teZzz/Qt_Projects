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
    void region(const QPoint& currentGlobalPoint);  //鼠标的位置,改变光标
protected:
    //鼠标按下移动及释放事件
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);
private slots:
    void window_close();
    void play_video();
    void OnSetMediaFile(void);//载入视频文件
    void OnSlider(qint64); // 信号内容的位置已更改为位置，以毫秒表示，进度条也要变
    void OnDurationChanged(qint64);// 信号表示内容的持续时间已更改为时长，以毫秒表示，进度条 的最大值和最小值
    void OnStateChanged(QMediaPlayer::State);// Player对象的状态已经改变
    void onItemClicked(QListWidgetItem*);//监听文件点击事件
    void voice_control(int value);//设置音量大小
    void muteAndrecover();//静音设置
    void window_max();//窗口最大化
private:
    Ui::MainWidgetClass *ui;
    void soltInit();//初始化槽函数
    void uiInit();//界面初始化
    void showFiles(QString);//显示当前文件夹
    QMediaPlayer* player;
    bool playFlag;// 播放/暂停标志
    bool loadFlag;// 加载文件标志
    bool voiceFlag;// 音量标志
    bool maxFlag;//窗口化标志
    QPoint m_movePoint;  //鼠标的位置
    bool isLeftPressDown;  // 判断左键是否按下
    Direction dir;        // 窗口大小改变时，记录改变方向
    QPoint m_dragPosition;
    QString m_currentPath;//当前路径

};
