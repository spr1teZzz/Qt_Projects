#pragma once
#include <qwidget.h>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QString>

#include <QDebug>
class loginWidget :
    public QWidget
{
    Q_OBJECT
public:
     loginWidget(QWidget* parent = nullptr);
    ~loginWidget();
    void btn_login();
signals:
    void loginUser(int, QString);
public slots:
    void loginWindowClose();
private:

    QLineEdit* LineEdit_username;
    QLineEdit* LineEdit_password;
};

