#pragma once

#include <QObject>
#include <QSlider>
#include <QMouseEvent>

class PlayerSlider  : public QSlider
{
    Q_OBJECT
signals:
    void sigProgress(qint64 i64Pos);

public:
    PlayerSlider(QWidget* parent = 0);

    bool    m_bPressed;
    void    setProgress(qint64);

    void    mousePressEvent(QMouseEvent* e)override;// ����
    void    mouseMoveEvent(QMouseEvent* e)override;// �ƶ�
    void    mouseReleaseEvent(QMouseEvent* e)override;// ̧���ͷ�
};
