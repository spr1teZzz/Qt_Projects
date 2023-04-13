#pragma once

#include <QLabel>
#include <QFontMetrics>
#include <QtMath>
class TextLabel  : public QLabel
{
	Q_OBJECT

public:
	TextLabel(QWidget *parent=nullptr);
	~TextLabel();

	void setMaxWidth(int width);
	QSize sizeHint() const override;
	virtual void setText(const QString& text);
protected:
	void resizeEvent(QResizeEvent* event) override;
private:
	int m_maxWidth;
	void adjustHeight();
};
