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
    //�û��б�����
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
    //QMimeData��һ���������ڼ�������ϷŲ���֮�佻�����ݵ��ࡣ
    //�ж��������Ƿ����URL&&��ȡ��һ��URL��Ȼ�������Ƿ��Ǳ����ļ�
    if (event->mimeData()->hasUrls() && event->mimeData()->urls().first().isLocalFile()) {
        //���ܽ���Ķ���(��ק����)
        qDebug() << "dragEnterEvent";
        event->acceptProposedAction();
    }
}

void MyTextEdit::dragMoveEvent(QDragMoveEvent* event)
{
    //�����������ק��������ô�ڽ������� dropEvent() �����оͿ��Խ�����Ӧ�Ĵ���
    if (event->mimeData()->hasImage() || event->mimeData()->hasUrls()) {
        qDebug() << "dragMoveEvent";
        event->acceptProposedAction();
    }
}

void MyTextEdit::dropEvent(QDropEvent* event)
{
    //����ק�¼��������ɿ���갴ťʱ  ѭ�������������ЩURL��Ӧ��ͼƬ
    if (event->mimeData()->hasImage()) {
        QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
        int originalWidth = image.width();
        int originalHeight = image.height();
        qDebug() << "width:" << originalWidth << "height:" << originalHeight;
        // �����µĿ�Ⱥ͸߶�
        int maxWidth = 300;  // �����Ϊ200
        int maxHeight = 300; // ���߶�Ϊ200
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

    // ���������
    int randomNum = rand();
    QString imageName = QString("image_%1").arg(randomNum);
    document->addResource(QTextDocument::ImageResource, QUrl(imageName), image);
    cursor.insertImage(imageName);
    setTextCursor(cursor);
}