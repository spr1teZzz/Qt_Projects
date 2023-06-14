#include "playerslider.h"

PlayerSlider::PlayerSlider(QWidget *parent)
	: QSlider(parent)
{
	m_bPressed = false;// 是否允许进度条的进度设置
}
// 进度条的进度设置
void PlayerSlider::setProgress(qint64 i64Progress)
{
    if (!m_bPressed)
        setValue(i64Progress);
}
// 按下
void PlayerSlider::mousePressEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton) {
        event->accept();
    }
    else {
        QSlider::mousePressEvent(event);
    }
}

void PlayerSlider::mouseMoveEvent(QMouseEvent* event){
    if (event->buttons() & Qt::LeftButton) {
        int newVal = this->minimum() + ((maximum() - minimum()) * event->x()) / width();
        setProgress(newVal);
        event->accept();
    }
    else {
        QSlider::mouseMoveEvent(event);
    }
}
// 抬起释放
void PlayerSlider::mouseReleaseEvent(QMouseEvent* e)
{
    m_bPressed = false;
    qint64 i64Pos = (qint64)value();
    emit sigProgress(i64Pos);// 发出位置改变信号
    QSlider::mouseReleaseEvent(e);//必须有这句，否则手动不能移动滑块
}
