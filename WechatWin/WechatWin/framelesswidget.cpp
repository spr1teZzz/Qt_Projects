#include "framelesswidget.h"
#include "qdatetime.h"
#include "qevent.h"
#include "qdebug.h"

#ifdef Q_OS_WIN
#include "windows.h"
#include "windowsx.h"
#pragma comment (lib,"user32.lib")
#endif

#define TIMEMS qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))

FramelessWidget::FramelessWidget(QWidget* parent) : QWidget(parent)
{
    padding = 8;
    moveEnable = true;
    resizeEnable = true;

    mousePressed = false;
    mousePoint = QPoint(0, 0);
    mouseRect = QRect(0, 0, 0, 0);

    for (int i = 0; i < 8; ++i) {
        pressedArea << false;
        pressedRect << QRect(0, 0, 0, 0);
    }

    isMin = false;
    flags = this->windowFlags();
    titleBar = 0;

    //���ñ���͸�� �ٷ���5.3�Ժ�ų����޸� WA_TranslucentBackground+FramelessWindowHint ���治���Ƶ�bug
#if (QT_VERSION >= QT_VERSION_CHECK(5,3,0))
    this->setAttribute(Qt::WA_TranslucentBackground);
#endif
    //�����ޱ߿�����
    this->setWindowFlags(flags | Qt::FramelessWindowHint);
    //��װ�¼�������ʶ���϶�
    this->installEventFilter(this);

    //�������Բ���win����Ч��,�ƶ�����Ե����������󻯵�
    //�����Ժ�������������Ҫ������������Ϣ����ȥ��
#ifdef Q_OS_WIN
    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
#endif
}

void FramelessWidget::showEvent(QShowEvent* event)
{
    //�����ʱ����������ʾ��ʱ�������ˢ�µ�bug
    setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);
}

void FramelessWidget::doWindowStateChange(QEvent* event)
{
    //����󻯲����ƶ����϶���С
    if (windowState() == Qt::WindowNoState) {
        moveEnable = true;
        resizeEnable = true;
    }
    else {
        moveEnable = false;
        resizeEnable = false;
    }

    //���������С���ȸı��¼�,�Ա�����ϸ��Ķ�Ӧ����Ϣ�������Ͻ�ͼ�������
    emit windowStateChange(!moveEnable);

    //���macϵͳ���ޱ߿���С��ʧЧ��bug
#ifdef Q_OS_MACOS
    if (windowState() & Qt::WindowMinimized) {
        isMin = true;
    }
    else {
        if (isMin) {
            //�����ޱ߿�����
            this->setWindowFlags(flags | Qt::FramelessWindowHint);
            this->setVisible(true);
            isMin = false;
        }
    }
#endif
}

void FramelessWidget::doResizeEvent(QEvent* event)
{
    //��winϵͳ���ޱ߿�����,winϵͳ���Ѿ�������nativeEvent����������
    //Ϊ�β�ͳһ�ü���ķ�ʽ��Ϊ��win���������ʽ��������ᷢ���õ�
#ifndef Q_OS_WIN
    if (event->type() == QEvent::Resize) {
        //���¼���˸���������,�����������û��о��Ǽ�����������Ƿ���ĳһ��������
        int width = this->width();
        int height = this->height();

        //����������
        pressedRect[0] = QRect(0, padding, padding, height - padding * 2);
        //�Ҳ��������
        pressedRect[1] = QRect(width - padding, padding, padding, height - padding * 2);
        //�ϲ��������
        pressedRect[2] = QRect(padding, 0, width - padding * 2, padding);
        //�²��������
        pressedRect[3] = QRect(padding, height - padding, width - padding * 2, padding);

        //���Ͻ��������
        pressedRect[4] = QRect(0, 0, padding, padding);
        //���Ͻ��������
        pressedRect[5] = QRect(width - padding, 0, padding, padding);
        //���½��������
        pressedRect[6] = QRect(0, height - padding, padding, padding);
        //���½��������
        pressedRect[7] = QRect(width - padding, height - padding, padding, padding);
    }
    else if (event->type() == QEvent::HoverMove) {
        //���ö�Ӧ�����״,�����������������������,��Ϊ���������û�а��µ�ʱ��ʶ��
        QHoverEvent* hoverEvent = (QHoverEvent*)event;
        QPoint point = hoverEvent->pos();
        if (resizeEnable) {
            if (pressedRect.at(0).contains(point)) {
                this->setCursor(Qt::SizeHorCursor);
            }
            else if (pressedRect.at(1).contains(point)) {
                this->setCursor(Qt::SizeHorCursor);
            }
            else if (pressedRect.at(2).contains(point)) {
                this->setCursor(Qt::SizeVerCursor);
            }
            else if (pressedRect.at(3).contains(point)) {
                this->setCursor(Qt::SizeVerCursor);
            }
            else if (pressedRect.at(4).contains(point)) {
                this->setCursor(Qt::SizeFDiagCursor);
            }
            else if (pressedRect.at(5).contains(point)) {
                this->setCursor(Qt::SizeBDiagCursor);
            }
            else if (pressedRect.at(6).contains(point)) {
                this->setCursor(Qt::SizeBDiagCursor);
            }
            else if (pressedRect.at(7).contains(point)) {
                this->setCursor(Qt::SizeFDiagCursor);
            }
            else {
                this->setCursor(Qt::ArrowCursor);
            }
        }

        //���ݵ�ǰ���λ��,����XY���ƶ��˶���
        int offsetX = point.x() - mousePoint.x();
        int offsetY = point.y() - mousePoint.y();

        //���ݰ��´���λ���ж��Ƿ����ƶ��ؼ���������ؼ�
        if (moveEnable && mousePressed) {
            this->move(this->x() + offsetX, this->y() + offsetY);
        }

        if (resizeEnable) {
            int rectX = mouseRect.x();
            int rectY = mouseRect.y();
            int rectW = mouseRect.width();
            int rectH = mouseRect.height();

            if (pressedArea.at(0)) {
                int resizeW = this->width() - offsetX;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + offsetX, rectY, resizeW, rectH);
                }
            }
            else if (pressedArea.at(1)) {
                this->setGeometry(rectX, rectY, rectW + offsetX, rectH);
            }
            else if (pressedArea.at(2)) {
                int resizeH = this->height() - offsetY;
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(rectX, this->y() + offsetY, rectW, resizeH);
                }
            }
            else if (pressedArea.at(3)) {
                this->setGeometry(rectX, rectY, rectW, rectH + offsetY);
            }
            else if (pressedArea.at(4)) {
                int resizeW = this->width() - offsetX;
                int resizeH = this->height() - offsetY;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
                }
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
                }
            }
            else if (pressedArea.at(5)) {
                int resizeW = rectW + offsetX;
                int resizeH = this->height() - offsetY;
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
                }
            }
            else if (pressedArea.at(6)) {
                int resizeW = this->width() - offsetX;
                int resizeH = rectH + offsetY;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
                }
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y(), resizeW, resizeH);
                }
            }
            else if (pressedArea.at(7)) {
                int resizeW = rectW + offsetX;
                int resizeH = rectH + offsetY;
                this->setGeometry(this->x(), this->y(), resizeW, resizeH);
            }
        }
    }
    else if (event->type() == QEvent::MouseButtonPress) {
        //��ס��갴�µ�����+��������
        QMouseEvent* mouseEvent = (QMouseEvent*)event;
        mousePoint = mouseEvent->pos();
        mouseRect = this->geometry();

        //�жϰ��µ��ֱ�������λ��
        if (pressedRect.at(0).contains(mousePoint)) {
            pressedArea[0] = true;
        }
        else if (pressedRect.at(1).contains(mousePoint)) {
            pressedArea[1] = true;
        }
        else if (pressedRect.at(2).contains(mousePoint)) {
            pressedArea[2] = true;
        }
        else if (pressedRect.at(3).contains(mousePoint)) {
            pressedArea[3] = true;
        }
        else if (pressedRect.at(4).contains(mousePoint)) {
            pressedArea[4] = true;
        }
        else if (pressedRect.at(5).contains(mousePoint)) {
            pressedArea[5] = true;
        }
        else if (pressedRect.at(6).contains(mousePoint)) {
            pressedArea[6] = true;
        }
        else if (pressedRect.at(7).contains(mousePoint)) {
            pressedArea[7] = true;
        }
        else {
            mousePressed = true;
        }
    }
    else if (event->type() == QEvent::MouseMove) {
        //�ĳ���HoverMoveʶ��
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        //�ָ�����
        this->setCursor(Qt::ArrowCursor);
        mousePressed = false;
        for (int i = 0; i < 8; ++i) {
            pressedArea[i] = false;
        }
    }
#endif
}

bool FramelessWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this) {
        if (event->type() == QEvent::WindowStateChange) {
            doWindowStateChange(event);
        }
        else {
            doResizeEvent(event);
        }
    }
    else if (watched == titleBar) {
        //˫������������˫���źŸ�������
        //����� *result = HTCAPTION; ��־λҲ���Զ�ʶ��˫��������
#ifndef Q_OS_WIN
        if (event->type() == QEvent::MouseButtonDblClick) {
            emit titleDblClick();
        }
        else if (event->type() == QEvent::NonClientAreaMouseButtonDblClick) {
            emit titleDblClick();
        }
#endif
    }

    return QWidget::eventFilter(watched, event);
}

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
bool FramelessWidget::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
#else
bool FramelessWidget::nativeEvent(const QByteArray& eventType, void* message, long* result)
#endif
{
    if (eventType == "windows_generic_MSG") {
#ifdef Q_OS_WIN
        MSG* msg = static_cast<MSG*>(message);
        //qDebug() << TIMEMS << "nativeEvent" << msg->wParam << msg->message;

        //��ͬ����Ϣ���ͺͲ������в�ͬ�Ĵ���
        if (msg->message == WM_NCCALCSIZE) {
            *result = 0;
            return true;
        }
        else if (msg->message == WM_SYSKEYDOWN) {
            //����alt������
        }
        else if (msg->message == WM_SYSKEYUP) {
            //����alt���ɿ�
        }
        else if (msg->message == WM_NCHITTEST) {
            //��������Ӧ����Ļ����
            //�����ʼ�õ� LOWORD HIWORD �ڶ���Ļ��ʱ���������
            //�ٷ�˵�������� https://docs.microsoft.com/zh-cn/windows/win32/inputdev/wm-nchittest
            long x = GET_X_LPARAM(msg->lParam);
            long y = GET_Y_LPARAM(msg->lParam);
            QPoint pos = mapFromGlobal(QPoint(x, y));

            //�жϵ�ǰ���λ�����ĸ�����
            bool left = pos.x() < padding;
            bool right = pos.x() > width() - padding;
            bool top = pos.y() < padding;
            bool bottom = pos.y() > height() - padding;

            //����ƶ����ĸ���,�����Ϣ�ǵ�����ƶ���������������ʱ�򷢳���
            *result = 0;
            if (resizeEnable) {
                if (left && top) {
                    *result = HTTOPLEFT;
                }
                else if (left && bottom) {
                    *result = HTBOTTOMLEFT;
                }
                else if (right && top) {
                    *result = HTTOPRIGHT;
                }
                else if (right && bottom) {
                    *result = HTBOTTOMRIGHT;
                }
                else if (left) {
                    *result = HTLEFT;
                }
                else if (right) {
                    *result = HTRIGHT;
                }
                else if (top) {
                    *result = HTTOP;
                }
                else if (bottom) {
                    *result = HTBOTTOM;
                }
            }

            //�ȴ��������
            if (0 != *result) {
                return true;
            }

            //ʶ��������϶���������ȫ��Ч��
            if (titleBar && titleBar->rect().contains(pos)) {
                QWidget* child = titleBar->childAt(pos);
                if (!child) {
                    *result = HTCAPTION;
                    return true;
                }
            }
        }
        else if (msg->wParam == PBT_APMSUSPEND && msg->message == WM_POWERBROADCAST) {
            //ϵͳ���ߵ�ʱ���Զ���С�����Թ�ܳ�����ܳ��ֵ�����
            this->showMinimized();
        }
        else if (msg->wParam == PBT_APMRESUMEAUTOMATIC) {
            //���߻��Ѻ��Զ���
            this->showNormal();
        }
#endif
    }
    else if (eventType == "NSEvent") {
#ifdef Q_OS_MACOS
#endif
    }
    else if (eventType == "xcb_generic_event_t") {
#ifdef Q_OS_LINUX
#endif
    }
    return false;
}

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef Q_OS_WIN
bool FramelessWidget::winEvent(MSG* message, long* result)
{
    return nativeEvent("windows_generic_MSG", message, result);
}
#endif
#endif

void FramelessWidget::setPadding(int padding)
{
    this->padding = padding;
}

void FramelessWidget::setMoveEnable(bool moveEnable)
{
    this->moveEnable = moveEnable;
}

void FramelessWidget::setResizeEnable(bool resizeEnable)
{
    this->resizeEnable = resizeEnable;
}

void FramelessWidget::setTitleBar(QWidget* titleBar)
{
    this->titleBar = titleBar;
    this->titleBar->installEventFilter(this);
}


