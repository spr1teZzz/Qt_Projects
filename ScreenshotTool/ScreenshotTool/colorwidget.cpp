#include "colorwidget.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
#include "qscreen.h"
#define deskGeometry qApp->primaryScreen()->geometry()
#define deskGeometry2 qApp->primaryScreen()->availableGeometry()
#else
#include "qdesktopwidget.h"
#define deskGeometry qApp->desktop()->geometry()
#define deskGeometry2 qApp->desktop()->availableGeometry()
#endif
#define SPACE 10
ColorWidget* ColorWidget::instance = 0;
ColorWidget* ColorWidget::Instance()
{
    //双重检查锁模式
    if (!instance) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!instance) {
            instance = new ColorWidget;
        }
    }

    return instance;
}
ColorWidget::ColorWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ColorWidgetClass())
{

	ui->setupUi(this);
    this->setMouseTracking(true);
    this->setFixedSize(100, 100);  // 设置窗口大小为固定宽高
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);  // 设置窗口无边框
    //每当定时器超时时，都会调用当前对象的showColorValue()函数进行更新
    timer = new QTimer(this);
    timer->setInterval(100);

    connect(timer, SIGNAL(timeout()), this, SLOT(showWidget()));
    timer->start();
    ui->label_Text->setStyleSheet("background:black;color:white");
}

ColorWidget::~ColorWidget()
{
	delete ui;
}
void ColorWidget::keyPressEvent(QKeyEvent* event)
{
    //截图和采色只能监视一个 所以要发信号给截图类，使其隐藏起来
    if (event->key() == Qt::Key_Escape) {
        this->close();
        emit esc_signal();
    }
}

void ColorWidget::mouseReleaseEvent(QMouseEvent*)
{
    this->close();
}

void ColorWidget::quit()
{
    qDebug() << "ColorWidget close";
    this->close();
}



void ColorWidget::showWidget()
{

    QPoint cursorPos = QCursor::pos();  // 获取鼠标位置
    int x = cursorPos.x();
    int y = cursorPos.y();
    QRect screenGeometry = QApplication::desktop()->screenGeometry();  // 获取屏幕的尺寸


    // 获取屏幕截图
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(QApplication::desktop()->winId(), x-20, y-10,40, 20);
    QPixmap zoomedPixmap = screenshot.scaled(100, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 将区域放大到 200x200 的大小

    QPainter painter(&zoomedPixmap); // 创建一个 QPainter 对象，并传入 QPixmap 对象
    painter.setPen(QPen(Qt::darkBlue, 3, Qt::SolidLine));  // 设置画笔
    painter.drawLine(zoomedPixmap.rect().center().x(), 0, zoomedPixmap.rect().center().x(), zoomedPixmap.height());  // 画一条中线
    painter.drawLine( 0, zoomedPixmap.rect().center().y(), zoomedPixmap.width(),zoomedPixmap.rect().center().y());  // 画一条中线
    painter.end();  // 结束画图过程
    ui->label_Img->setPixmap(zoomedPixmap);  // 在QLabel中显示放大后的像素

     //截取2*2的矩形面积,放在pixmap显示在
    QPixmap pixmap = screen->grabWindow(0, x, y, 3, 3);
    int red, green, blue;
    QString strDecimalValue, strHex;
    if (pixmap.isNull()) {
        return;
    }

    QImage image = pixmap.toImage();
    if (image.valid(0, 0)) {
        QColor color = image.pixel(0, 0);
        red = color.red();
        green = color.green();
        blue = color.blue();
        QString strRed = tr("%1").arg(red & 0xFF, 2, 16, QChar('0'));
        QString strGreen = tr("%1").arg(green & 0xFF, 2, 16, QChar('0'));
        QString strBlue = tr("%1").arg(blue & 0xFF, 2, 16, QChar('0'));

        strDecimalValue = tr("%1, %2, %3").arg(red).arg(green).arg(blue);
        strHex = tr("#%1%2%3").arg(strRed.toUpper()).arg(strGreen.toUpper()).arg(strBlue.toUpper());
    }

    QString str = tr("RGB\n%1\n%2").arg(strDecimalValue).arg(strHex);
    ui->label_Text->setText(str);
    if (x + SPACE + this->width() > screenGeometry.width())
    {
        x = x - this->width() - SPACE;
    }
    else
    {
        x = x + SPACE;
    }
    if (y + SPACE + this->width() > screenGeometry.height())
    {
        y = y - this->height() - SPACE;
    }
    else
    {
        y = y + SPACE;
    }
    this->move(x, y);
    this->update();
}

