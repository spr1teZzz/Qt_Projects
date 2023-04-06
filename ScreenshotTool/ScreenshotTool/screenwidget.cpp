#pragma execution_character_set("utf-8")
#include "screenwidget.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
#include "qscreen.h"
#define deskGeometry qApp->primaryScreen()->geometry()
#define deskGeometry2 qApp->primaryScreen()->availableGeometry()
#else
#include "qdesktopwidget.h"
#define deskGeometry qApp->desktop()->geometry()
#define deskGeometry2 qApp->desktop()->availableGeometry()
#endif

#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))

Screen::Screen(QSize size)
{
    maxWidth = size.width();
    maxHeight = size.height();

    startPos = QPoint(-1, -1);
    endPos = startPos;
    leftUpPos = startPos;
    rightDownPos = startPos;
    status = SELECT;
}

int Screen::width()
{
    return maxWidth;
}

int Screen::height()
{
    return maxHeight;
}

Screen::STATUS Screen::getStatus()
{
    return status;
}

void Screen::setStatus(STATUS status)
{
    this->status = status;
}

void Screen::setEnd(QPoint pos)
{
    endPos = pos;
    leftUpPos = startPos;
    rightDownPos = endPos;
    cmpPoint(leftUpPos, rightDownPos);
}

void Screen::setStart(QPoint pos)
{
    startPos = pos;
}

QPoint Screen::getEnd()
{
    return endPos;
}

QPoint Screen::getStart()
{
    return startPos;
}

QPoint Screen::getLeftUp()
{
    return leftUpPos;
}

QPoint Screen::getRightDown()
{
    return rightDownPos;
}

bool Screen::isInArea(QPoint pos)
{
    if (pos.x() > leftUpPos.x() && pos.x() < rightDownPos.x() && pos.y() > leftUpPos.y() && pos.y() < rightDownPos.y()) {
        return true;
    }

    return false;
}

void Screen::move(QPoint p)
{
    int lx = leftUpPos.x() + p.x();
    int ly = leftUpPos.y() + p.y();
    int rx = rightDownPos.x() + p.x();
    int ry = rightDownPos.y() + p.y();

    if (lx < 0) {
        lx = 0;
        rx -= p.x();
    }

    if (ly < 0) {
        ly = 0;
        ry -= p.y();
    }

    if (rx > maxWidth) {
        rx = maxWidth;
        lx -= p.x();
    }

    if (ry > maxHeight) {
        ry = maxHeight;
        ly -= p.y();
    }

    leftUpPos = QPoint(lx, ly);
    rightDownPos = QPoint(rx, ry);
    startPos = leftUpPos;
    endPos = rightDownPos;
}

void Screen::cmpPoint(QPoint& leftTop, QPoint& rightDown)
{
    QPoint l = leftTop;
    QPoint r = rightDown;

    if (l.x() <= r.x()) {
        if (l.y() <= r.y()) {
        }
        else {
            leftTop.setY(r.y());
            rightDown.setY(l.y());
        }
    }
    else {
        if (l.y() < r.y()) {
            leftTop.setX(r.x());
            rightDown.setX(l.x());
        }
        else {
            QPoint tmp;
            tmp = leftTop;
            leftTop = rightDown;
            rightDown = tmp;
        }
    }
}

QScopedPointer<ScreenWidget> ScreenWidget::self;
ScreenWidget* ScreenWidget::Instance()
{
    if (self.isNull()) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull()) {
            self.reset(new ScreenWidget);
        }
    }

    return self.data();
}

ScreenWidget::ScreenWidget(QWidget* parent) : QWidget(parent)
{
    //this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);

    menu = new QMenu(this);
    menu->addAction("保存当前截图", this, SLOT(saveScreen()));
    menu->addAction("保存全屏截图", this, SLOT(saveFullScreen()));
    menu->addAction("截图另存为", this, SLOT(saveScreenOther()));
    menu->addAction("全屏另存为", this, SLOT(saveFullOther()));
    menu->addAction("退出截图", this, SLOT(quit()));

    //取得屏幕大小
    screen = new Screen(deskGeometry.size());
    //保存全屏图像
    fullScreen = new QPixmap();

    //绑定colorWidget内的退出信号
    connect(ColorWidget::Instance(), &ColorWidget::esc_signal, this, &ScreenWidget::quit);

    //绑定colorWidget内的退出信号
    connect(this, &ScreenWidget::colorwidget_signal, ColorWidget::Instance(), &ColorWidget::quit);
    //this->setMouseTracking(true);
}

void ScreenWidget::paintEvent(QPaintEvent*)
{
    int x = screen->getLeftUp().x();
    int y = screen->getLeftUp().y();
    int w = screen->getRightDown().x() - x;
    int h = screen->getRightDown().y() - y;

    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawPixmap(0, 0, *bgScreen);
    if (w != 0 && h != 0) {
        painter.drawPixmap(x, y, fullScreen->copy(x, y, w, h));
    }

    painter.drawRect(x, y, w, h);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    int draw_pos_x = x + 2;
    int draw_pos_y = y - 8;

    if (draw_pos_x > fullScreen->width())
    {
        draw_pos_x -= 4;
    }

    if (draw_pos_y < 0)
    {
        draw_pos_y += 20;
    }
    painter.drawText(draw_pos_x, draw_pos_y , tr(" %1 x %2 ").arg(w).arg(h));
}

void ScreenWidget::showEvent(QShowEvent*)
{
    QPoint point(-1, -1);
    screen->setStart(point);
    screen->setEnd(point);
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    QScreen* pscreen = QApplication::primaryScreen();
    *fullScreen = pscreen->grabWindow(0, 0, 0, screen->width(), screen->height());
#else
    * fullScreen = fullScreen->grabWindow(0, 0, 0, screen->width(), screen->height());
#endif
    bgScreen = new QPixmap(*fullScreen);
}

void ScreenWidget::saveScreen()
{
    int x = screen->getLeftUp().x();
    int y = screen->getLeftUp().y();
    int w = screen->getRightDown().x() - x;
    int h = screen->getRightDown().y() - y;

    QString fileName = QString("%1/screen_%2.png").arg(qApp->applicationDirPath()).arg(STRDATETIME);
    fullScreen->copy(x, y, w, h).save(fileName, "png");
    close();
}

void ScreenWidget::saveFullScreen()
{
    QString fileName = QString("%1/full_%2.png").arg(qApp->applicationDirPath()).arg(STRDATETIME);
    fullScreen->save(fileName, "png");
    close();
}

void ScreenWidget::saveScreenOther()
{
    QString name = QString("%1.png").arg(STRDATETIME);
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", name, "png Files (*.png)");

    //取消
    if (fileName == "")
    {
        return;
    }

    if (!fileName.endsWith(".png")) {
        fileName += ".png";
    }

    if (fileName.length() > 0) {
        int x = screen->getLeftUp().x();
        int y = screen->getLeftUp().y();
        int w = screen->getRightDown().x() - x;
        int h = screen->getRightDown().y() - y;
        fullScreen->copy(x, y, w, h).save(fileName, "png");
        close();
    }
}

void ScreenWidget::saveFullOther()
{
    QString name = QString("%1.png").arg(STRDATETIME);
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", name, "png Files (*.png)");

    //取消
    if (fileName == "")
    {
        return;
    }

    if (!fileName.endsWith(".png")) {
        fileName += ".png";
    }

    if (fileName.length() > 0) {
        fullScreen->save(fileName, "png");
        close();
    }
}

void ScreenWidget::quit()
{
    screen->setStatus(Screen::SELECT);
    this->hide();
}

void ScreenWidget::mouseMoveEvent(QMouseEvent* e)
{
    if (screen->getStatus() == Screen::SELECT) {
        screen->setEnd(e->pos());
    }
    else if (screen->getStatus() == Screen::MOV) {
        QPoint p(e->x() - movPos.x(), e->y() - movPos.y());
        screen->move(p);
        movPos = e->pos();
    }
    this->update();
}

void ScreenWidget::mousePressEvent(QMouseEvent* e)
{
    int status = screen->getStatus();
    if (status == Screen::SELECT) {
        screen->setStart(e->pos());
        //设置背景颜色改变
        QPixmap pix(screen->width(), screen->height());
        pix.fill((QColor(160, 160, 160, 200)));
        QPainter p(bgScreen);
        p.drawPixmap(0, 0, pix);
    }
    else if (status == Screen::MOV) {
        if (screen->isInArea(e->pos()) == false) {
            screen->setStart(e->pos());
            screen->setStatus(Screen::SELECT);
        }
        else {
            movPos = e->pos();
            this->setCursor(Qt::SizeAllCursor);
        }
    }
    this->update();
}

void ScreenWidget::mouseReleaseEvent(QMouseEvent*)
{
    qDebug() << "ScreenWidget release";
    emit colorwidget_signal();
    //结束位置和起始位置未改变则全屏选中
    if (screen->getEnd().x() == -1 && screen->getEnd().y() == -1)
    {
        screen->setStart(QPoint(0, 0));
        screen->setEnd(QPoint(screen->width(), screen->height()));

        this->update();
    }
    if (screen->getStatus() == Screen::SELECT) {
        screen->setStatus(Screen::MOV);
    }
    else if (screen->getStatus() == Screen::MOV) {
        this->setCursor(Qt::ArrowCursor);
    }
}

void ScreenWidget::contextMenuEvent(QContextMenuEvent*)
{
    this->setCursor(Qt::ArrowCursor);
    menu->exec(cursor().pos());
}

void ScreenWidget::keyPressEvent(QKeyEvent* event)
{
    //截图和采色只能监视一个
    if (event->key() == Qt::Key_Escape) {
        screen->setStatus(Screen::SELECT);
        this->hide();
    }
}

