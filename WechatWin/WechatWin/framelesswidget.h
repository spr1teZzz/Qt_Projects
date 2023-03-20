#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

/**
 * �ޱ߿����� ����:feiyangqingyun(QQ:517216493) 2021-07-27
 * 1. ͬʱ֧��Qt4-Qt6���ײ�Qt4.7��Qt6.2��
 * 2. ͬʱ֧��mingw��msvc��gcc�ȡ�
 * 3. ͬʱ֧��windows��linux��mac��
 * 4. ͬʱ֧��QMainWindow��QWidget��QDialog��
 * 5. ʹ�÷�������򵥣�ֻ��Ҫ���̳����޸ļ��ɡ�
 * 6. �Զ�ʶ��˫����������Ӧ��
 * 7. �ޱ߿�������windows�²�������
 * 8. ��windows�¾����ƶ�����Ե�������ƶ�������ȫ�����ԡ�
 * 9. ���macϵͳ���ޱ߿���С�����ʧЧ��bug��
 * 10. ���ϵͳ���ߺ��ٴ����������±Ƶ�bug��
 * 11. �����ʱ����������ʾ��ʱ�������ˢ�µ�bug��
 * 12. ��������1�������ļ������Ĵ�����������300�С�
 * 13. ע����ϸ��ʾ���������ǳ��ʺ��Ķ���ѧϰ��
 * 14. ��Դ���伴�ã���֤����Qt�汾�������������У������κε�����
 */

#include <QWidget>

#ifdef quc
class Q_DECL_EXPORT FramelessWidget : public QWidget
#else
class FramelessWidget : public QWidget
#endif

{
    Q_OBJECT
public:
    explicit FramelessWidget(QWidget* parent = 0);

protected:
    //������ʾ��ʱ�򴥷�
    void showEvent(QShowEvent* event);

    //�¼�������ʶ���϶������
    void doWindowStateChange(QEvent* event);
    void doResizeEvent(QEvent* event);
    bool eventFilter(QObject* watched, QEvent* event);

    //����ϵͳ�¼������޸�ϵͳ���ߺ��ѳ����bug
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#else
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif

    //Qt4��д��
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef Q_OS_WIN
    bool winEvent(MSG* message, long* result);
#endif
#endif

private:
    //�߾�+���ƶ�+������
    int padding;
    bool moveEnable;
    bool resizeEnable;

    //�������ؼ�
    QWidget* titleBar;

    //����Ƿ���+��������+����ʱ��������
    bool mousePressed;
    QPoint mousePoint;
    QRect mouseRect;

    //����Ƿ���ĳ������+��������Ĵ�С
    //����Ϊ ���+�Ҳ�+�ϲ�+�²�+���ϲ�+���ϲ�+���²�+���²�
    QList<bool> pressedArea;
    QList<QRect> pressedRect;

    //��¼�Ƿ���С��
    bool isMin;
    //�洢����Ĭ�ϵ�����
    Qt::WindowFlags flags;

public Q_SLOTS:
    //���ñ߾�+���϶�+������
    void setPadding(int padding);
    void setMoveEnable(bool moveEnable);
    void setResizeEnable(bool resizeEnable);

    //���ñ������ؼ�
    void setTitleBar(QWidget* titleBar);

Q_SIGNALS:
    void titleDblClick();
    void windowStateChange(bool max);
};

#endif // FRAMELESSWIDGET_H
