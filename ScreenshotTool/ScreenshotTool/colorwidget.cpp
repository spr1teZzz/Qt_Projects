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
    //˫�ؼ����ģʽ
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
    this->setFixedSize(100, 100);  // ���ô��ڴ�СΪ�̶����
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);  // ���ô����ޱ߿�
    //ÿ����ʱ����ʱʱ��������õ�ǰ�����showColorValue()�������и���
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
    //��ͼ�Ͳ�ɫֻ�ܼ���һ�� ����Ҫ���źŸ���ͼ�࣬ʹ����������
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

    QPoint cursorPos = QCursor::pos();  // ��ȡ���λ��
    int x = cursorPos.x();
    int y = cursorPos.y();
    QRect screenGeometry = QApplication::desktop()->screenGeometry();  // ��ȡ��Ļ�ĳߴ�


    // ��ȡ��Ļ��ͼ
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(QApplication::desktop()->winId(), x-20, y-10,40, 20);
    QPixmap zoomedPixmap = screenshot.scaled(100, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // ������Ŵ� 200x200 �Ĵ�С

    QPainter painter(&zoomedPixmap); // ����һ�� QPainter ���󣬲����� QPixmap ����
    painter.setPen(QPen(Qt::darkBlue, 3, Qt::SolidLine));  // ���û���
    painter.drawLine(zoomedPixmap.rect().center().x(), 0, zoomedPixmap.rect().center().x(), zoomedPixmap.height());  // ��һ������
    painter.drawLine( 0, zoomedPixmap.rect().center().y(), zoomedPixmap.width(),zoomedPixmap.rect().center().y());  // ��һ������
    painter.end();  // ������ͼ����
    ui->label_Img->setPixmap(zoomedPixmap);  // ��QLabel����ʾ�Ŵ�������

     //��ȡ2*2�ľ������,����pixmap��ʾ��
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

