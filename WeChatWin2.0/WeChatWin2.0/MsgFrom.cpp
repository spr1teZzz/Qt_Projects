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
	//���ͳɹ�
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
	//������ʾʱ��
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString curDate = curDateTime.toString("yyyy-MM-dd");
	QString day = m_curTime.mid(0, 10);
	//������ͬ,����ʾʱ��
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
	//		//���ط�����Ϣ
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
	//ָ�������µ����Ŵ�С�ĺ���
	QFontMetricsF fm(this->font());
	//���������иߣ�����������߶ȡ��м����κζ���ռ�ĸ߶�
	m_lineHeight = fm.lineSpacing();
	//����\n ����
	int nCount = src.count("\n");
	int nMaxWidth = 0;
	if (nCount == 0) {
		//û�л��з� �����ַ����Ŀ��
		nMaxWidth = fm.width(src);
		QString value = src;
		if (nMaxWidth > m_textWidth) {
			//���õ�m_textWidth С�ڵ�ǰ�ַ����Ŀ��
			nMaxWidth = m_textWidth;

			int size = m_textWidth / fm.width(" ");
			//�������
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
	m_msg = str;//�ַ�����Ϣ
	int minHei = 30;//�������ݵ���С�߶�
	int iconWH = 40;//ͷ��Ŀ�Ⱥ͸߶�
	int iconSpaceW = 20;//ͷ�������֮��Ŀ�϶���
	int iconRectW = 5;//ͷ�������֮��ľ��ο���
	int iconTMPH = 10;//ͷ�������֮�����ʱ�߶�
	int sanJiaoW = 6;//���ݼ�ǵĿ��
	int kuangTMP = 20;//���ݺʹ���֮��ľ���
	int textSpaceRect = 12;//���ݺʹ���֮��ľ���

	//�������ݵĿ�Ⱥ��ı����ݵĿ��
	m_kuangWidth = this->width() - kuangTMP - 2 * (iconWH + iconSpaceW + iconRectW);
	m_textWidth = m_kuangWidth - 2 * textSpaceRect;
	m_spaceWid = this->width() - m_textWidth;
	m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
	m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

	//�������ݵĿ�Ⱥ��ı����ݵĿ�ȡ�
	QSize size = getRealString(m_msg); // ������size
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
	//�����ı����ݵ�λ�úʹ�С
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
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//�����
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(Qt::gray));

	if (m_userType == User_Type::User_Other) { // �û�
		//ͷ��
		painter.drawPixmap(m_iconLeftRect, m_pixmap);

		//��ӱ�
		QColor col_KuangB(234, 234, 234);
		painter.setBrush(QBrush(col_KuangB));
		painter.drawRoundedRect(m_kuangLeftRect.x() - 1, m_kuangLeftRect.y() - 1, m_kuangLeftRect.width() + 2, m_kuangLeftRect.height() + 2, 4, 4);
		//��
		QColor col_Kuang(255, 255, 255);
		painter.setBrush(QBrush(col_Kuang));
		painter.drawRoundedRect(m_kuangLeftRect, 4, 4);

		//����
		QPointF points[3] = {
			QPointF(m_sanjiaoLeftRect.x(), 30),
			QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 25),
			QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 35),
		};
		QPen pen;
		pen.setColor(col_Kuang);
		painter.setPen(pen);
		painter.drawPolygon(points, 3);

		//���Ǽӱ�
		QPen penSanJiaoBian;
		penSanJiaoBian.setColor(col_KuangB);
		painter.setPen(penSanJiaoBian);
		painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 24));
		painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 36));

		//����
		QPen penText;
		penText.setColor(QColor(51, 51, 51));
		painter.setPen(penText);
		QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
		option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
		painter.setFont(this->font());
		painter.drawText(m_textLeftRect, m_msg, option);
	}
	else if (m_userType == User_Type::User_Me) { // �Լ�
   //ͷ��
		painter.drawPixmap(m_iconRightRect, m_pixmap);

		//��
		QColor col_Kuang(75, 164, 242);
		painter.setBrush(QBrush(col_Kuang));
		painter.drawRoundedRect(m_kuangRightRect, 4, 4);

		//����
		QPointF points[3] = {
			QPointF(m_sanjiaoRightRect.x() + m_sanjiaoRightRect.width(), 30),
			QPointF(m_sanjiaoRightRect.x(), 25),
			QPointF(m_sanjiaoRightRect.x(), 35),
		};
		QPen pen;
		pen.setColor(col_Kuang);
		painter.setPen(pen);
		painter.drawPolygon(points, 3);

		//����
		QPen penText;
		penText.setColor(Qt::white);
		painter.setPen(penText);
		QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
		option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
		painter.setFont(this->font());
		painter.drawText(m_textRightRect, m_msg, option);
	}
	else if (m_userType == User_Type::User_Time) { // ʱ��
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


