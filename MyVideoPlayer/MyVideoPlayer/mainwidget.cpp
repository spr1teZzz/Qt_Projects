#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWidgetClass())
{
    ui->setupUi(this);
    // ȥ��������,ȥ���������������ö�
    setWindowFlags(Qt::CustomizeWindowHint);
    //setWindowFlags(  Qt::WindowStaysOnTopHint);
    //this->setStyleSheet("background-color:#1E1E1E");
    //��ʼ��������
    player = new QMediaPlayer();
    //��ʼ�����Ű�ť:�������
    playFlag = false;
    //������ļ�·���Ǳ��ص���Ƶ�ļ�ȫ·�� �����Լ������������
    //player�Ǹոս����Ĳ���������
    player->setVideoOutput(ui->widget_video);
    ui->widget_video->setAutoFillBackground(true);
    //�ļ����س�ʼ��
    loadFlag = true;
    //������־��ʼ��
    voiceFlag = true;
    //���ڻ���־��ʼ��
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
    // Player�����״̬�Ѿ��ı䡣
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(OnStateChanged(QMediaPlayer::State)));

    // �ź����ݵ�λ���Ѹ���Ϊλ�ã��Ժ����ʾ��������ҲҪ��
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(OnSlider(qint64)));
    // �źű�ʾ���ݵĳ���ʱ���Ѹ���Ϊʱ�����Ժ����ʾ�������� �����ֵ����Сֵ
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(OnDurationChanged(qint64)));
    // ������������ƶ�λ��
    connect(ui->slider_video, SIGNAL(sigProgress(qint64)), player, SLOT(setPosition(qint64)));

    //�ļ���ʾ����¼�
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWidget::onItemClicked);
            
    //�������
    connect(ui->slider_voice, &QSlider::sliderMoved, this, &MainWidget::voice_control);
    connect(ui->Btn_voiceIcon, &QPushButton::clicked, this, &MainWidget::muteAndrecover);

    //��������
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
            player->setMedia(QUrl::fromLocalFile(path));// ����ý����Ϣ
            loadFlag = true;
            ui->slider_video->setValue(0);//������������0(��ʼλ��)
            setWindowTitle(path);
            player->setPosition(0); // ������λ������Ϊ��ʼλ��
            player->pause(); // ��ͣ����
        }
    }
}

void MainWidget::voice_control(int value)
{
    //��������
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
    //�����ͻָ�
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
        parentDir.cdUp(); // �л�����ǰĿ¼����һ��Ŀ¼
        QString parentDirPath = parentDir.absolutePath(); // ��ȡ��һ��Ŀ¼�ľ���·��
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

//���غ���
void MainWidget::region(const QPoint& currentGlobalPoint)
{
    // ��ȡ��������Ļ�ϵ�λ������topLeftΪ���Ͻǵ㣬rightButtonΪ���½ǵ�
    QRect rect = this->rect();

    QPoint topLeft = this->mapToGlobal(rect.topLeft()); //�����Ͻǵ�(0,0)ת��Ϊȫ������
    QPoint rightButton = this->mapToGlobal(rect.bottomRight());

    int x = currentGlobalPoint.x(); //��ǰ��������
    int y = currentGlobalPoint.y();

    if (((topLeft.x() + PADDING >= x) && (topLeft.x() <= x))
        && ((topLeft.y() + PADDING >= y) && (topLeft.y() <= y)))
    {
        // ���Ͻ�
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // ���ù����״
    }
    else if (((x >= rightButton.x() - PADDING) && (x <= rightButton.x()))
        && ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
    {
        // ���½�
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
        && ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
    {
        //���½�
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
        && ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING)))
    {
        // ���Ͻ�
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if ((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
    {
        // ���
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if ((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
    {
        // �ұ�
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING))
    {
        // �ϱ�
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if ((y <= rightButton.y()) && (y >= rightButton.y() - PADDING))
    {
        // �±�
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        // Ĭ��
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}


//��������¼�����д
//��갴���¼�
void MainWidget::mousePressEvent(QMouseEvent* event)
{
    switch (event->button())
    {
    case Qt::LeftButton:
        isLeftPressDown = true;

        if (dir != NONE)
        {
            this->mouseGrabber(); //���ص�ǰץȡ�������Ĵ���
        }
        else
        {
            m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
            //globalPos()���λ�ã�topLeft()�������Ͻǵ�λ��
        }
        break;
    case Qt::RightButton:
        this->setWindowState(Qt::WindowMinimized);
        break;
    default:
        MainWidget::mousePressEvent(event);
    }
}

//����ƶ��¼�
void MainWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint globalPoint = event->globalPos();   //���ȫ������

    QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
    QPoint topLeft = mapToGlobal(rect.topLeft());
    QPoint bottomRight = mapToGlobal(rect.bottomRight());

    if (this->windowState() != Qt::WindowMaximized)
    {
        if (!isLeftPressDown)  //û�а������ʱ
        {
            this->region(globalPoint); //���ڴ�С�ĸı䡪���ж����λ�ã��ı�����״
        }
        else
        {
            if (dir != NONE)
            {
                QRect newRect(topLeft, bottomRight); //����һ������  �϶������1000*1618

                switch (dir)
                {
                case LEFT:

                    if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
                    {
                        newRect.setLeft(topLeft.x());  //С�ڽ������С���ʱ������Ϊ���ϽǺ�����Ϊ����x
                        //ֻ�ı���߽�
                    }
                    else
                    {
                        newRect.setLeft(globalPoint.x());
                    }
                    break;
                case RIGHT:
                    newRect.setWidth(globalPoint.x() - topLeft.x());  //ֻ�ܸı��ұ߽�
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
                move(event->globalPos() - m_movePoint); //�ƶ�����
                event->accept();
            }
        }
    }
}

//����ͷ��¼�
void MainWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftPressDown = false;
        if (dir != NONE)
        {
            this->releaseMouse(); //�ͷ����ץȡ
            this->setCursor(QCursor(Qt::ArrowCursor));
            dir = NONE; //��������ָ��
        }
    }
}

//�ۺ���
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
        //δ������Ƶ
        return;
    }

    if (playFlag)
    {
        //���ڲ���
        playFlag = false;
        //�ı�ͼ��
        ui->Btn_StartAndStop->setIcon(QIcon(":/icon/img/play.png"));
        //��ͣ
        player->pause();
    }
    else
    {
        //δ����
        playFlag = true;
        //�ı�ͼ��
        ui->Btn_StartAndStop->setIcon(QIcon(":/icon/img/pause.png"));
        //��ʼ����
        player->play();
    }

}

void MainWidget::OnSetMediaFile(void)
{
    //�����Ƶ�ļ�
    QFileDialog dialog(this);//�ļ�ѡ�񴰿�
    dialog.setFileMode(QFileDialog::AnyFile);//�����ļ�ģʽ(�ļ�/�ļ���)�������ļ��������Ƿ����
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();// ������ѡ����ļ�

    if (!fileNames.empty())
    {
        qDebug() << "fileName:" << fileNames[0];
        player->setMedia(QUrl::fromLocalFile(fileNames[0]));// ����ý����Ϣ
        loadFlag = true;
        ui->slider_video->setValue(0);//������������0(��ʼλ��)
        player->setPosition(0); // ������λ������Ϊ��ʼλ��
        player->pause(); // ��ͣ����
        setWindowTitle(fileNames[0]);
    }
}


void MainWidget::OnSlider(qint64 i64Pos)
{
    qDebug() << "OnSlider:" << i64Pos;
    // �Զ����λ���ƶ�==setValue(i64Pos);
    ui->slider_video->setProgress(i64Pos);
    QTime time = QTime::fromMSecsSinceStartOfDay(i64Pos);
    ui->label_curTime->setText(time.toString("hh:mm:ss"));
}

void MainWidget::OnDurationChanged(qint64 i64Duration)
{
    if (i64Duration > 0 && loadFlag) // ���ֵ>0���� �Ѿ����뻹û���ý��������ֵ
    {
        qDebug() << "i64Duration:" << i64Duration;
        ui->slider_video->setRange(0, i64Duration);
        //ui->label_curTime->setText(QString::number(0));
        QTime time = QTime::fromMSecsSinceStartOfDay(i64Duration);
        ui->label_maxTime->setText(time.toString("hh:mm:ss"));
        loadFlag = false;// ���������ý��������ֵ
    }
}

// Player�����״̬�Ѿ��ı�
void MainWidget::OnStateChanged(QMediaPlayer::State enumState)
{
    
    if (QMediaPlayer::StoppedState == enumState)//ֹͣ
    {
        qDebug() << "StoppedState";
        ui->slider_video->setEnabled(false);
        ui->Btn_StartAndStop->setIcon(QIcon(":/icon/img/play.png"));
        player->setPosition(0); // ������λ������Ϊ��ʼλ��
        player->pause(); // ��ͣ����
        playFlag = false;
    }
    else if (QMediaPlayer::PlayingState == enumState)// ����
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
        //û��ý��
        qDebug() << "NoMedia";
    }
}