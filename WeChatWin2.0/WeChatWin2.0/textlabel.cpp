#include "textlabel.h"

TextLabel::TextLabel(QWidget *parent)
	: QLabel(parent),m_maxWidth(-1)
{
	setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setWordWrap(true);
}

TextLabel::~TextLabel()
{

}
void TextLabel::setMaxWidth(int width)
{
    m_maxWidth = width;
}

QSize TextLabel::sizeHint() const
{
    QSize size = QLabel::sizeHint();
    if (m_maxWidth != -1) {
        size.setWidth(m_maxWidth);
    }
    return size;
}

void TextLabel::setText(const QString& text)
{
    QLabel::setText(text);
    adjustHeight();
}

void TextLabel::resizeEvent(QResizeEvent* event)
{
    QLabel::resizeEvent(event);
    adjustHeight();
}


void TextLabel::adjustHeight()
{
    QFontMetrics metrics(font());
    int textWidth = metrics.boundingRect(text()).width();
    int maxWidth = m_maxWidth == -1 ? width() : m_maxWidth;
    int lines = qCeil(static_cast<float>(textWidth) / static_cast<float>(maxWidth));
    int textHeight = metrics.height() * lines;
    setMinimumHeight(textHeight);
}