#include "playerslider.h"

PlayerSlider::PlayerSlider(QWidget *parent)
	: QSlider(parent)
{
	m_bPressed = false;// �Ƿ�����������Ľ�������
}
// �������Ľ�������
void PlayerSlider::setProgress(qint64 i64Progress)
{
    if (!m_bPressed)
        setValue(i64Progress);
}
// ����
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
// ̧���ͷ�
void PlayerSlider::mouseReleaseEvent(QMouseEvent* e)
{
    m_bPressed = false;
    qint64 i64Pos = (qint64)value();
    emit sigProgress(i64Pos);// ����λ�øı��ź�
    QSlider::mouseReleaseEvent(e);//��������䣬�����ֶ������ƶ�����
}
