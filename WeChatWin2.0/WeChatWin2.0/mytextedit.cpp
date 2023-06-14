#include "mytextedit.h"

MyTextEdit::MyTextEdit(QWidget *parent)
	: QTextEdit(parent)
{
    m_imageLabel = new QLabel(this);
    m_imageLabel->hide();
    srand(time(nullptr));
    QTextOption option;
    option.setFlags(QTextOption::IncludeTrailingSpaces | QTextOption::AddSpaceForLineAndParagraphSeparators);
    this->document()->setDefaultTextOption(option);
    this->setAcceptRichText(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setStyleSheet("border:none");
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //用户列表设置
    QFile file(":/qss/QTextEdit_scrollbar.qss");
    if (file.open(QFile::ReadOnly))
    {
        
        QString array = file.readAll();
        this->verticalScrollBar()->setStyleSheet(array);
        file.close();
    }
    else
    {
        qDebug() << "open scrollbar.qss failed";
    }
}

MyTextEdit::~MyTextEdit()
{

}
void MyTextEdit::dragEnterEvent(QDragEnterEvent* event)
{
    //QMimeData是一个可用于在剪贴板和拖放操作之间交换数据的类。
    //判断数据中是否包含URL&&获取第一个URL，然后检查其是否是本地文件
    if (event->mimeData()->hasUrls() && event->mimeData()->urls().first().isLocalFile()) {
        //接受建议的动作(拖拽操作)
        qDebug() << "dragEnterEvent";
        event->acceptProposedAction();
    }
}

void MyTextEdit::dragMoveEvent(QDragMoveEvent* event)
{
    //如果接受了拖拽动作，那么在接下来的 dropEvent() 函数中就可以进行相应的处理
    if (event->mimeData()->hasImage() || event->mimeData()->hasUrls()) {
        qDebug() << "dragMoveEvent";
        event->acceptProposedAction();
    }
}

void MyTextEdit::dropEvent(QDropEvent* event)
{
    //当拖拽事件结束并松开鼠标按钮时  循环来逐个插入这些URL对应的图片
    if (event->mimeData()->hasImage()) {
        QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
        int originalWidth = image.width();
        int originalHeight = image.height();
        qDebug() << "width:" << originalWidth << "height:" << originalHeight;
        // 计算新的宽度和高度
        int maxWidth = 300;  // 最大宽度为200
        int maxHeight = 300; // 最大高度为200
        int newWidth = originalWidth;
        int newHeight = originalHeight;
        if (originalWidth > maxWidth) {
            newWidth = maxWidth;
            newHeight = (newWidth * originalHeight) / originalWidth;
        }
        if (newHeight > maxHeight) {
            newHeight = maxHeight;
            newWidth = (newHeight * originalWidth) / originalHeight;
        }
        qDebug() << "newWidth:" << newWidth << "newHeight:" << newHeight;
        QSize newSize(newWidth, newHeight);
        QImage scaledImage = image.scaled(newSize, Qt::KeepAspectRatio);
        insertImage(scaledImage);
        event->acceptProposedAction();
    }
    else if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        for (const auto& url : urls) {
            if (url.isLocalFile()) {
                QImage image(url.toLocalFile());
                insertImage(image);
            }

        }
        event->acceptProposedAction();
    }
}

void MyTextEdit::insertImage(const QImage& image)
{
    if (image.isNull())
    {
        return;
    }
    QTextCursor cursor = this->textCursor();
    QTextDocument* document = this->document();

    // 生成随机数
    int randomNum = rand();
    QString imageName = QString("image_%1").arg(randomNum);
    document->addResource(QTextDocument::ImageResource, QUrl(imageName), image);
    cursor.insertImage(imageName);
    setTextCursor(cursor);
}