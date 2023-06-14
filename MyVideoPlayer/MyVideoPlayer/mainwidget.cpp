#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWidgetClass())
{
    ui->setupUi(this);
    // 去掉标题栏,去掉工具栏，窗口置顶
    setWindowFlags(Qt::CustomizeWindowHint);
    //setWindowFlags(  Qt::WindowStaysOnTopHint);
    //this->setStyleSheet("background-color:#1E1E1E");
    //初始化播放器
    player = new QMediaPlayer();
    //初始化播放按钮:点击播放
    playFlag = false;
    //这里的文件路径是本地的视频文件全路径 根据自己的情况来设置
    //player是刚刚建立的播放器变量
    player->setVideoOutput(ui->widget_video);
    ui->widget_video->setAutoFillBackground(true);
    //文件加载初始化
    loadFlag = true;
    //音量标志初始化
    voiceFlag = true;
    //窗口化标志初始化
    maxFlag = false;
    ui->slider_video->setEnabled(false);
    m_currentPath = QDir::currentPath();
    showFiles(m_currentPath);
    soltInit();
    uiInit();
}
MainWidget::~MainWidget()
{
    delete player;
    delete ui;
}

void MainWidget::soltInit()
{
    connect(ui->Btn_Close, &QPushButton::clicked, this, &MainWidget::window_close);
    connect(ui->Btn_Min, &QPushButton::clicked, this, [&]() {
        this->showMinimized();
        });
    connect(ui->Btn_Max, &QPushButton::clicked, this, &MainWidget::window_max);
    connect(ui->Btn_StartAndStop, &QPushButton::clicked, this, &MainWidget::play_video);
    connect(ui->Btn_loadFile, &QPushButton::clicked, this, &MainWidget::OnSetMediaFile);  
    // Player对象的状态已经改变。
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(OnStateChanged(QMediaPlayer::State)));

    // 信号内容的位置已更改为位置，以毫秒表示，进度条也要变
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(OnSlider(qint64)));
    // 信号表示内容的持续时间已更改为时长，以毫秒表示，进度条 的最大值和最小值
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(OnDurationChanged(qint64)));
    // 进度条：鼠标移动位置
    connect(ui->slider_video, SIGNAL(sigProgress(qint64)), player, SLOT(setPosition(qint64)));

    //文件显示点击事件
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWidget::onItemClicked);
            
    //音量监控
    connect(ui->slider_voice, &QSlider::sliderMoved, this, &MainWidget::voice_control);
    connect(ui->Btn_voiceIcon, &QPushButton::clicked, this, &MainWidget::muteAndrecover);

    //倍速设置
    connect(ui->Btn_speed1, &QPushButton::clicked, this, [&]() {
        player->setPlaybackRate(0.5);
        });
    connect(ui->Btn_speed2, &QPushButton::clicked, this, [&]() {
        player->setPlaybackRate(1.0);
        });
    connect(ui->Btn_speed3, &QPushButton::clicked, this, [&]() {
        player->setPlaybackRate(1.2);
        });
    connect(ui->Btn_speed4, &QPushButton::clicked, this, [&]() {
        player->setPlaybackRate(1.5);
        });
    connect(ui->Btn_speed5, &QPushButton::clicked, this, [&]() {
        player->setPlaybackRate(2.0);
        });

   
}

void MainWidget::onItemClicked(QListWidgetItem*item)
{
    QString path = item->data(Qt::UserRole).toString();
    qDebug() << "onItemClicked path:" << path;
    if (path == "Disc")
    {
        ui->listWidget->clear();
        QFileInfoList drives = QDir::drives();
        for (const auto& drive : drives)
        {
            QListWidgetItem* item = new QListWidgetItem(drive.absoluteFilePath(), ui->listWidget);
            item->setData(Qt::UserRole, drive.absoluteFilePath());
            item->setIcon(QIcon(":/icon/img/disc.png"));
        }
    }
    else
    {
        QFileInfo fileInfo(path);
        if (fileInfo.isDir() || fileInfo.isRoot()) {
            m_currentPath = path;
            showFiles(path);
        }
        else {
            player->setMedia(QUrl::fromLocalFile(path));// 设置媒体信息
            loadFlag = true;
            ui->slider_video->setValue(0);//进度条数字在0(开始位置)
            setWindowTitle(path);
            player->setPosition(0); // 将播放位置设置为起始位置
            player->pause(); // 暂停播放
        }
    }
}

void MainWidget::voice_control(int value)
{
    //声音控制
    player->setVolume(value);
    if (value == 0)
    {
        voiceFlag = false;
        ui->Btn_voiceIcon->setIcon(QIcon(":/icon/img/volumeClose.png"));
    }
    else
    {
        voiceFlag = true;
        ui->Btn_voiceIcon->setIcon(QIcon(":/icon/img/volumeOpen.png"));
    }
}

void MainWidget::muteAndrecover()
{
    //静音和恢复
    if (voiceFlag)
    {
        player->setVolume(0);
        ui->slider_voice->setValue(0);
        ui->Btn_voiceIcon->setIcon(QIcon(":/icon/img/volumeClose.png"));
    }
    else
    {
        player->setVolume(50);
        ui->slider_voice->setValue(50);
        ui->Btn_voiceIcon->setIcon(QIcon(":/icon/img/volumeOpen.png"));
    }
    voiceFlag = !voiceFlag;
}

void MainWidget::window_max()
{
    if (!maxFlag)
    {
        this->showMaximized();
    }
    else
    {
        this->showNormal();
    }
    maxFlag = !maxFlag;
}

void MainWidget::showFiles(QString path)
{
    ui->listWidget->clear();
    QDir dir(path);
    if (!dir.isRoot())
    {
        QDir parentDir = dir;
        parentDir.cdUp(); // 切换到当前目录的上一级目录
        QString parentDirPath = parentDir.absolutePath(); // 获取上一级目录的绝对路径
        QListWidgetItem* item = new QListWidgetItem("..", ui->listWidget);
        item->setData(Qt::UserRole, parentDirPath);
        item->setIcon(QIcon(":/icon/img/folder.png"));
    }
    else
    {
        QListWidgetItem* item = new QListWidgetItem("..", ui->listWidget);
        item->setData(Qt::UserRole, "Disc");
        item->setIcon(QIcon(":/icon/img/folder.png"));
    }
    QFileInfoList list = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name);
    for (const auto& info : list) {

        if (info.isDir()) {
            QListWidgetItem* item = new QListWidgetItem(info.fileName(), ui->listWidget);
            item->setData(Qt::UserRole, info.filePath());
            item->setIcon(QIcon(":/icon/img/folder.png"));
        }
        else if(info.suffix().toLower() == "mp4") {
            QListWidgetItem* item = new QListWidgetItem(info.fileName(), ui->listWidget);
            item->setData(Qt::UserRole, info.filePath());
            item->setIcon(QIcon(":/icon/img/file.png"));
        }
    }
}

void MainWidget::uiInit()
{
    setWindowIcon(QIcon(":/icon/img/playerIcon.png"));
    ui->slider_voice->setValue(50);
    ui->Btn_Last->setIcon(QIcon(":/icon/img/last.png"));
    ui->Btn_Next->setIcon(QIcon(":/icon/img/next.png"));
    ui->Btn_StartAndStop->setIcon(QIcon(":/icon/img/play.png"));
    ui->Btn_loadFile->setIcon(QIcon(":/icon/img/openFile.png"));
    ui->Btn_Min->setIcon(QIcon(":/icon/img/min.png"));
    ui->Btn_Max->setIcon(QIcon(":/icon/img/max.png"));
    ui->Btn_Close->setIcon(QIcon(":/icon/img/close.png"));
    ui->Btn_voiceIcon->setIcon(QIcon(":/icon/img/volumeOpen.png"));
}

//重载函数
void MainWidget::region(const QPoint& currentGlobalPoint)
{
    // 获取窗体在屏幕上的位置区域，topLeft为坐上角点，rightButton为右下角点
    QRect rect = this->rect();

    QPoint topLeft = this->mapToGlobal(rect.topLeft()); //将左上角的(0,0)转化为全局坐标
    QPoint rightButton = this->mapToGlobal(rect.bottomRight());

    int x = currentGlobalPoint.x(); //当前鼠标的坐标
    int y = currentGlobalPoint.y();

    if (((topLeft.x() + PADDING >= x) && (topLeft.x() <= x))
        && ((topLeft.y() + PADDING >= y) && (topLeft.y() <= y)))
    {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置光标形状
    }
    else if (((x >= rightButton.x() - PADDING) && (x <= rightButton.x()))
        && ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
    {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
        && ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
    {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
        && ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING)))
    {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if ((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
    {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if ((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
    {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING))
    {
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if ((y <= rightButton.y()) && (y >= rightButton.y() - PADDING))
    {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}


//三个鼠标事件的重写
//鼠标按下事件
void MainWidget::mousePressEvent(QMouseEvent* event)
{
    switch (event->button())
    {
    case Qt::LeftButton:
        isLeftPressDown = true;

        if (dir != NONE)
        {
            this->mouseGrabber(); //返回当前抓取鼠标输入的窗口
        }
        else
        {
            m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
            //globalPos()鼠标位置，topLeft()窗口左上角的位置
        }
        break;
    case Qt::RightButton:
        this->setWindowState(Qt::WindowMinimized);
        break;
    default:
        MainWidget::mousePressEvent(event);
    }
}

//鼠标移动事件
void MainWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint globalPoint = event->globalPos();   //鼠标全局坐标

    QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
    QPoint topLeft = mapToGlobal(rect.topLeft());
    QPoint bottomRight = mapToGlobal(rect.bottomRight());

    if (this->windowState() != Qt::WindowMaximized)
    {
        if (!isLeftPressDown)  //没有按下左键时
        {
            this->region(globalPoint); //窗口大小的改变——判断鼠标位置，改变光标形状
        }
        else
        {
            if (dir != NONE)
            {
                QRect newRect(topLeft, bottomRight); //定义一个矩形  拖动后最大1000*1618

                switch (dir)
                {
                case LEFT:

                    if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
                    {
                        newRect.setLeft(topLeft.x());  //小于界面的最小宽度时，设置为左上角横坐标为窗口x
                        //只改变左边界
                    }
                    else
                    {
                        newRect.setLeft(globalPoint.x());
                    }
                    break;
                case RIGHT:
                    newRect.setWidth(globalPoint.x() - topLeft.x());  //只能改变右边界
                    break;
                case UP:
                    if (bottomRight.y() - globalPoint.y() <= this->minimumHeight())
                    {
                        newRect.setY(topLeft.y());
                    }
                    else
                    {
                        newRect.setY(globalPoint.y());
                    }
                    break;
                case DOWN:
                    newRect.setHeight(globalPoint.y() - topLeft.y());
                    break;
                case LEFTTOP:
                    if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
                    {
                        newRect.setX(topLeft.x());
                    }
                    else
                    {
                        newRect.setX(globalPoint.x());
                    }

                    if (bottomRight.y() - globalPoint.y() <= this->minimumHeight())
                    {
                        newRect.setY(topLeft.y());
                    }
                    else
                    {
                        newRect.setY(globalPoint.y());
                    }
                    break;
                case RIGHTTOP:
                    if (globalPoint.x() - topLeft.x() >= this->minimumWidth())
                    {
                        newRect.setWidth(globalPoint.x() - topLeft.x());
                    }
                    else
                    {
                        newRect.setWidth(bottomRight.x() - topLeft.x());
                    }
                    if (bottomRight.y() - globalPoint.y() >= this->minimumHeight())
                    {
                        newRect.setY(globalPoint.y());
                    }
                    else
                    {
                        newRect.setY(topLeft.y());
                    }
                    break;
                case LEFTBOTTOM:
                    if (bottomRight.x() - globalPoint.x() >= this->minimumWidth())
                    {
                        newRect.setX(globalPoint.x());
                    }
                    else
                    {
                        newRect.setX(topLeft.x());
                    }
                    if (globalPoint.y() - topLeft.y() >= this->minimumHeight())
                    {
                        newRect.setHeight(globalPoint.y() - topLeft.y());
                    }
                    else
                    {
                        newRect.setHeight(bottomRight.y() - topLeft.y());
                    }
                    break;
                case RIGHTBOTTOM:
                    newRect.setWidth(globalPoint.x() - topLeft.x());
                    newRect.setHeight(globalPoint.y() - topLeft.y());
                    break;
                default:
                    break;
                }
                this->setGeometry(newRect);
            }
            else
            {
                move(event->globalPos() - m_movePoint); //移动窗口
                event->accept();
            }
        }
    }
}

//鼠标释放事件
void MainWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftPressDown = false;
        if (dir != NONE)
        {
            this->releaseMouse(); //释放鼠标抓取
            this->setCursor(QCursor(Qt::ArrowCursor));
            dir = NONE; //热心网友指正
        }
    }
}

//槽函数
void MainWidget::window_close()
{
    this->close();
}
void MainWidget::resizeEvent(QResizeEvent* event)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    int width = this->width();
    int height = this->height();

    ui->widget_video->setGeometry(10,30,width-250,height-100);
    ui->listWidget->setGeometry(30 + ui->widget_video->width()+5, 30, 230, height - 70);
    ui->Btn_Last->setGeometry(160, height - 40, 40, 40);
    ui->Btn_StartAndStop->setGeometry(200, height - 40, 40, 40);
    ui->Btn_Next->setGeometry(240, height - 40, 40, 40);
    ui->Btn_loadFile->setGeometry(280, height - 40, 40, 40);

    ui->Btn_Min->setGeometry(width - 90, 0,30,30);
    ui->Btn_Max->setGeometry(width - 60, 0, 30, 30);
    ui->Btn_Close->setGeometry(width - 30, 0, 30, 30);
    ui->slider_video->setGeometry(10, ui->widget_video->height() + 40, width - 500, 20);
    ui->label_curTime->setGeometry(10 + ui->slider_video->width() + 10, ui->slider_video->y(), 50, 20);
    ui->label_maxTime->setGeometry(10 + ui->slider_video->width() + 10 + 50 + 5, ui->slider_video->y(), 50, 20);
    ui->label_3->setGeometry(10 + ui->slider_video->width()+60, ui->slider_video->y(),5,20);
    ui->Btn_voiceIcon->setGeometry(ui->label_maxTime->x() + 60, ui->label_maxTime->y(), 20, 20);
    ui->slider_voice->setGeometry(ui->Btn_voiceIcon->x() + 30, ui->Btn_voiceIcon->y(), 100,20 );

    //speed
    ui->Btn_speed1->setGeometry(ui->label_curTime->x(), height - 30, 50, 20);
    ui->Btn_speed2->setGeometry(ui->label_curTime->x()+50, height - 30, 50, 20);
    ui->Btn_speed3->setGeometry(ui->label_curTime->x()+100, height - 30, 50, 20);
    ui->Btn_speed4->setGeometry(ui->label_curTime->x()+150, height - 30, 50, 20);
    ui->Btn_speed5->setGeometry(ui->label_curTime->x()+200, height - 30, 50, 20);
}
void MainWidget::play_video()
{
    if (player->state() == QMediaPlayer::State::StoppedState)
    {
        //未加载视频
        return;
    }

    if (playFlag)
    {
        //正在播放
        playFlag = false;
        //改变图标
        ui->Btn_StartAndStop->setIcon(QIcon(":/icon/img/play.png"));
        //暂停
        player->pause();
    }
    else
    {
        //未播放
        playFlag = true;
        //改变图标
        ui->Btn_StartAndStop->setIcon(QIcon(":/icon/img/pause.png"));
        //开始播放
        player->play();
    }

}

void MainWidget::OnSetMediaFile(void)
{
    //添加视频文件
    QFileDialog dialog(this);//文件选择窗口
    dialog.setFileMode(QFileDialog::AnyFile);//设置文件模式(文件/文件夹)：任意文件，无论是否存在
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();// 存所有选择的文件

    if (!fileNames.empty())
    {
        qDebug() << "fileName:" << fileNames[0];
        player->setMedia(QUrl::fromLocalFile(fileNames[0]));// 设置媒体信息
        loadFlag = true;
        ui->slider_video->setValue(0);//进度条数字在0(开始位置)
        player->setPosition(0); // 将播放位置设置为起始位置
        player->pause(); // 暂停播放
        setWindowTitle(fileNames[0]);
    }
}


void MainWidget::OnSlider(qint64 i64Pos)
{
    qDebug() << "OnSlider:" << i64Pos;
    // 自定义的位置移动==setValue(i64Pos);
    ui->slider_video->setProgress(i64Pos);
    QTime time = QTime::fromMSecsSinceStartOfDay(i64Pos);
    ui->label_curTime->setText(time.toString("hh:mm:ss"));
}

void MainWidget::OnDurationChanged(qint64 i64Duration)
{
    if (i64Duration > 0 && loadFlag) // 最大值>0并且 已经载入还没设置进度条最大值
    {
        qDebug() << "i64Duration:" << i64Duration;
        ui->slider_video->setRange(0, i64Duration);
        //ui->label_curTime->setText(QString::number(0));
        QTime time = QTime::fromMSecsSinceStartOfDay(i64Duration);
        ui->label_maxTime->setText(time.toString("hh:mm:ss"));
        loadFlag = false;// 不能再设置进度条最大值
    }
}

// Player对象的状态已经改变
void MainWidget::OnStateChanged(QMediaPlayer::State enumState)
{
    
    if (QMediaPlayer::StoppedState == enumState)//停止
    {
        qDebug() << "StoppedState";
        ui->slider_video->setEnabled(false);
        ui->Btn_StartAndStop->setIcon(QIcon(":/icon/img/play.png"));
        player->setPosition(0); // 将播放位置设置为起始位置
        player->pause(); // 暂停播放
        playFlag = false;
    }
    else if (QMediaPlayer::PlayingState == enumState)// 播放
    {
        qDebug() << "PlayingState";
        ui->slider_video->setEnabled(true);
    }
    else if (QMediaPlayer::PausedState == enumState)
    {
        qDebug() << "PausedState";
    }
    else if (QMediaPlayer::LoadingMedia == enumState)
    {
        qDebug() << "LoadingMedia";
    }
    else if (QMediaPlayer::BufferingMedia == enumState)
    {
        qDebug() << "BufferingMedia";
    }
    else if (QMediaPlayer::EndOfMedia == enumState)
    {
        qDebug() << "EndOfMedia";
    }
    else if (QMediaPlayer::InvalidMedia == enumState)
    {
        qDebug() << "InvalidMedia";
    }
    else if (QMediaPlayer::BufferedMedia == enumState)
    {
        
        qDebug() << "BufferedMedia";
    }
    else if (QMediaPlayer::NoMedia == enumState)
    {
        //没有媒体
        qDebug() << "NoMedia";
    }
}