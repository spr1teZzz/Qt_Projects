#pragma once

#include <QTextEdit>
#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QImageReader>
#include <QFileInfo>
#include <QTextDocument>
#include <QDialog>
#include <QLabel>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>
#include <QTextBlock>
#include <QVBoxLayout>
#include <QScrollArea>
#include <cstdlib>
#include <ctime>
#include <QScrollBar>
class MyTextEdit  : public QTextEdit
{
	Q_OBJECT

public:
	MyTextEdit(QWidget *parent=nullptr);
	~MyTextEdit();
protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void insertImage(const QImage& image);
    //void mousePressEvent(QMouseEvent* event) override;
    //void mouseDoubleClickEvent(QMouseEvent* event) override;
//public slots:
//    void onLinkClicked(const QUrl& link);

private:
    QLabel* m_imageLabel;
    int currentImagePosition;
};
