#include "cell.h"

Cell::Cell(int32_t i, int32_t j, QWidget *parent) :
	QPushButton(parent), m_is_flag(false), m_i(i), m_j(j), m_value(0), m_isMine(false), m_isOpen(false),
	m_temporaryOpen(false), m_isLastOpened(false), m_isHighlighted(false)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(30, 30);

	m_imageFlag = QPixmap(":/images/flag.png");
	m_imageMine = QPixmap(":/images/mine.png");
	m_imageLastmine = QPixmap(":/images/lastMine.png");
}

int32_t Cell::i()
{
	return m_i;
}
int32_t Cell::j()
{
	return m_j;
}

int32_t Cell::value()
{
	return m_value;
}
void Cell::valueInc()
{
	++m_value;
}

bool Cell::is_mine()
{
	return m_isMine;
}
void Cell::setMine()
{
	m_isMine = true;
	repaint();
}

void Cell::setLastOpened(bool flag)
{
	m_isLastOpened = flag;
}
bool Cell::is_last_opened()
{
	return m_isLastOpened;
}

bool Cell::is_open()
{
	return m_isOpen;
}
void Cell::setOpen()
{
	m_isOpen = true;
	repaint();
}

void Cell::swapFlag()
{
	m_is_flag = !m_is_flag;
	repaint();
}

void Cell::highlight()
{
	m_isHighlighted = !m_isHighlighted;
	repaint();
}

void Cell::setTemporaryOpen(bool open)
{
	m_temporaryOpen = open;
	repaint();
}

void Cell::paintEvent(QPaintEvent *event)
{
	if (is_open() && is_mine() == false && 0 == m_value)
		return;
	QPushButton::paintEvent(event);
	QPainter p(this);
	if (is_open() || m_temporaryOpen)
	{
		if (is_mine())
		{
			if (is_last_opened())
			{
				p.drawPixmap(0, 0, width(), height(), m_imageLastmine);
			}
			else
			{
				p.drawPixmap(0, 0, width(), height(), m_imageMine);
			}
			return;
		}
		setText(QString::number(m_value));
		return;
	}
	if (m_is_flag)
	{
		p.drawPixmap(0, 0, width(), height(), m_imageFlag);
	}

	if (m_isHighlighted)
	{
		p.setPen(QPen(Qt::red, 2));
		p.drawRect(0, 0, width() - 1, height() - 1);
	}
}

void Cell::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
		emit clicked_left();
	if (e->button() == Qt::RightButton)
		emit clicked_right();
	if (e->button() == Qt::MiddleButton)
		emit clicked_middle();
}

void Cell::serialize(QSettings &settings) const
{
	QString key = QString("Dot_%1_%2").arg(m_i).arg(m_j);
	settings.beginGroup(key);
	settings.setValue("i", m_i);
	settings.setValue("j", m_j);
	settings.setValue("value", m_value);
	settings.setValue("is_mine", m_isMine);
	settings.setValue("is_open", m_isOpen);
	settings.setValue("isFlag", m_is_flag);
	settings.setValue("is_last_opened", m_isLastOpened);
	settings.endGroup();
}

void Cell::deserialize(QSettings &settings)
{
	QString key = QString("Dot_%1_%2").arg(m_i).arg(m_j);
	settings.beginGroup(key);
	m_value = settings.value("value").toInt();
	m_isMine = settings.value("is_mine").toBool();
	m_isOpen = settings.value("is_open").toBool();
	m_is_flag = settings.value("isFlag").toBool();
	m_isLastOpened = settings.value("is_last_opened").toBool();
	settings.endGroup();
	repaint();
}
