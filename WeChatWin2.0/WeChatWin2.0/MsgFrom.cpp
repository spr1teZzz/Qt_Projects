#include "MsgFrom.h"

#define WIDTH 600
#define MSG_WIDTH 350
#define HEAD_WIDTH  40
#define HEAD_HEIGHT 40

MsgFrom::MsgFrom(QString url,QWidget* parent)
	: QWidget(parent)
{
	QFont te_font = this->font();
	te_font.setFamily("MicrosoftYaHei");
	te_font.setPointSize(12);
	m_pixmap = QPixmap(":/img/image/" + url);
	this->setFont(te_font);
	m_loadingMovie = new QMovie(this);
	m_loadingMovie->setFileName(":/img/image/loading.gif");
	m_loading = new QLabel(this);
	m_loading->setMovie(m_loadingMovie);
	m_loading->resize(16, 16);
	m_loading->setAttribute(Qt::WA_TranslucentBackground, true);
	m_loading->setAutoFillBackground(false);
}

MsgFrom::~MsgFrom()
{
}

void MsgFrom::setTextSuccess()
{
	//发送成功
	m_loading->hide();
	m_loadingMovie->stop();
	m_isSending = true;
}

void MsgFrom::setText(QString text, QString time, QSize allSize, User_Type userType)
{
	m_msg = text;
	m_userType = userType;
	m_time = time;
	m_curTime = time;
	//处理显示时间
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString curDate = curDateTime.toString("yyyy-MM-dd");
	QString day = m_curTime.mid(0, 10);
	//日期相同,则显示时间
	QString hour = m_curTime.mid(11, 5);

	if (day == curDate)
	{

		m_curTime = hour;
	}
	else if (day != nullptr)
	{
		m_curTime = day.mid(2, 2) + "/" + day.mid(5, 2) + "/" + day.mid(8, 2);
	}
	m_allSize = allSize;
	//if (userType == User_Me) {
	//	if (!m_isSending) {
	//		//加载发送消息
	//		m_loading->move(m_kuangRightRect.x() - m_loading->width() - 10, m_kuangRightRect.y() + m_kuangRightRect.height() / 2 - m_loading->height() / 2);
	//		m_loading->show();
	//		m_loadingMovie->start();
	//	}
	//}
	//else {
	//	m_loading->hide();
	//}

	this->update();
}

QSize MsgFrom::getRealString(QString src)
{
	//指定字体下的最优大小的函数
	QFontMetricsF fm(this->font());
	//返回字体行高，即包含字体高度、行间距和任何额外空间的高度
	m_lineHeight = fm.lineSpacing();
	//计算\n 数量
	int nCount = src.count("\n");
	int nMaxWidth = 0;
	if (nCount == 0) {
		//没有换行符 返回字符串的宽度
		nMaxWidth = fm.width(src);
		QString value = src;
		if (nMaxWidth > m_textWidth) {
			//设置的m_textWidth 小于当前字符串的宽度
			nMaxWidth = m_textWidth;

			int size = m_textWidth / fm.width(" ");
			//获得行数
			int num = fm.width(value) / m_textWidth;
			int ttmp = num * fm.width(" ");
			num = (fm.width(value)) / m_textWidth;
			nCount += num;
			QString temp = "";
			for (int i = 0; i < num; i++) {
				temp += value.mid(i * size, (i + 1) * size) + "\n";
			}
			src.replace(value, temp);
		}
	}
	else {
		for (int i = 0; i < (nCount + 1); i++) {
			QString value = src.split("\n").at(i);
			nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
			if (fm.width(value) > m_textWidth) {
				nMaxWidth = m_textWidth;
				int size = m_textWidth / fm.width(" ");
				int num = fm.width(value) / m_textWidth;
				num = ((i + num) * fm.width(" ") + fm.width(value)) / m_textWidth;
				nCount += num;
				QString temp = "";
				for (int i = 0; i < num; i++) {
					temp += value.mid(i * size, (i + 1) * size) + "\n";
				}
				src.replace(value, temp);
			}
		}
	}
	return QSize(nMaxWidth + m_spaceWid, (nCount + 1) * m_lineHeight + 2 * m_lineHeight);
}

QSize MsgFrom::fontRect(QString str)
{
	m_msg = str;//字符串消息
	int minHei = 30;//聊天气泡的最小高度
	int iconWH = 40;//头像的宽度和高度
	int iconSpaceW = 20;//头像和气泡之间的空隙宽度
	int iconRectW = 5;//头像和气泡之间的矩形框宽度
	int iconTMPH = 10;//头像和气泡之间的临时高度
	int sanJiaoW = 6;//气泡尖角的宽度
	int kuangTMP = 20;//气泡和窗口之间的距离
	int textSpaceRect = 12;//气泡和窗口之间的距离

	//计算气泡的宽度和文本内容的宽度
	m_kuangWidth = this->width() - kuangTMP - 2 * (iconWH + iconSpaceW + iconRectW);
	m_textWidth = m_kuangWidth - 2 * textSpaceRect;
	m_spaceWid = this->width() - m_textWidth;
	m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
	m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

	//计算气泡的宽度和文本内容的宽度。
	QSize size = getRealString(m_msg); // 整个的size
	//qDebug() << "fontRect Size:" << size;
	int hei = size.height() < minHei ? minHei : size.height();
	m_sanjiaoLeftRect = QRect(iconWH + iconSpaceW + iconRectW, m_lineHeight / 2, sanJiaoW, hei - m_lineHeight);
	m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight / 2, sanJiaoW, hei - m_lineHeight);

	if (size.width() < (m_textWidth + m_spaceWid)) {
		m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * textSpaceRect, hei - m_lineHeight);
		m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2 * textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
			m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * textSpaceRect, hei - m_lineHeight);
	}
	else {
		m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight / 4 * 3, m_kuangWidth, hei - m_lineHeight);
		m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight / 4 * 3, m_kuangWidth, hei - m_lineHeight);
	}
	//计算文本内容的位置和大小
	m_textLeftRect.setRect(m_kuangLeftRect.x() + textSpaceRect, m_kuangLeftRect.y() + iconTMPH,
		m_kuangLeftRect.width() - 2 * textSpaceRect, m_kuangLeftRect.height() - 2 * iconTMPH);
	m_textRightRect.setRect(m_kuangRightRect.x() + textSpaceRect, m_kuangRightRect.y() + iconTMPH,
		m_kuangRightRect.width() - 2 * textSpaceRect, m_kuangRightRect.height() - 2 * iconTMPH);

	return QSize(size.width(), hei);
}

void MsgFrom::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(Qt::gray));

	if (m_userType == User_Type::User_Other) { // 用户
		//头像
		painter.drawPixmap(m_iconLeftRect, m_pixmap);

		//框加边
		QColor col_KuangB(234, 234, 234);
		painter.setBrush(QBrush(col_KuangB));
		painter.drawRoundedRect(m_kuangLeftRect.x() - 1, m_kuangLeftRect.y() - 1, m_kuangLeftRect.width() + 2, m_kuangLeftRect.height() + 2, 4, 4);
		//框
		QColor col_Kuang(255, 255, 255);
		painter.setBrush(QBrush(col_Kuang));
		painter.drawRoundedRect(m_kuangLeftRect, 4, 4);

		//三角
		QPointF points[3] = {
			QPointF(m_sanjiaoLeftRect.x(), 30),
			QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 25),
			QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 35),
		};
		QPen pen;
		pen.setColor(col_Kuang);
		painter.setPen(pen);
		painter.drawPolygon(points, 3);

		//三角加边
		QPen penSanJiaoBian;
		penSanJiaoBian.setColor(col_KuangB);
		painter.setPen(penSanJiaoBian);
		painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 24));
		painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 36));

		//内容
		QPen penText;
		penText.setColor(QColor(51, 51, 51));
		painter.setPen(penText);
		QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
		option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
		painter.setFont(this->font());
		painter.drawText(m_textLeftRect, m_msg, option);
	}
	else if (m_userType == User_Type::User_Me) { // 自己
   //头像
		painter.drawPixmap(m_iconRightRect, m_pixmap);

		//框
		QColor col_Kuang(75, 164, 242);
		painter.setBrush(QBrush(col_Kuang));
		painter.drawRoundedRect(m_kuangRightRect, 4, 4);

		//三角
		QPointF points[3] = {
			QPointF(m_sanjiaoRightRect.x() + m_sanjiaoRightRect.width(), 30),
			QPointF(m_sanjiaoRightRect.x(), 25),
			QPointF(m_sanjiaoRightRect.x(), 35),
		};
		QPen pen;
		pen.setColor(col_Kuang);
		painter.setPen(pen);
		painter.drawPolygon(points, 3);

		//内容
		QPen penText;
		penText.setColor(Qt::white);
		painter.setPen(penText);
		QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
		option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
		painter.setFont(this->font());
		painter.drawText(m_textRightRect, m_msg, option);
	}
	else if (m_userType == User_Type::User_Time) { // 时间
		QPen penText;
		penText.setColor(QColor(153, 153, 153));
		painter.setPen(penText);
		QTextOption option(Qt::AlignCenter);
		option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
		QFont te_font = this->font();
		te_font.setFamily("MicrosoftYaHei");
		te_font.setPointSize(10);
		painter.setFont(te_font);
		painter.drawText(this->rect(), m_curTime, option);
	}
}


