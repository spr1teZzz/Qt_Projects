#ifndef FRMSCREENWIDGET_H
#define FRMSCREENWIDGET_H

#include <QWidget>
#include <QKeyEvent>
namespace Ui {
class frmScreenWidget;
}

class frmScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmScreenWidget(QWidget *parent = 0);
    ~frmScreenWidget();

private slots:
    void on_pushButton_clicked();
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::frmScreenWidget *ui;
};

#endif // FRMSCREENWIDGET_H
