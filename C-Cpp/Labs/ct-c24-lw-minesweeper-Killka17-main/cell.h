#ifndef DOT_H
#define DOT_H

#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QSettings>

class Cell : public QPushButton
{
	Q_OBJECT

  public:
	explicit Cell(int32_t i, int32_t j, QWidget *parent = nullptr);
	void swapFlag();
	void highlight();
	void valueInc();
	int32_t i();
	int32_t j();
	int32_t value();
	bool is_mine();
	void setMine();
	bool is_last_opened();
	void setLastOpened(bool flag);
	bool is_open();
	void setOpen();
	bool m_is_flag;
	void setTemporaryOpen(bool open);
	void deserialize(QSettings &settings);
	void serialize(QSettings &settings) const;

  signals:
	void clicked_left();
	void clicked_right();
	void clicked_middle();

  private:
	void paintEvent(QPaintEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	QPixmap m_imageFlag;
	QPixmap m_imageMine;
	QPixmap m_imageLastmine;
	int32_t m_i;
	int32_t m_j;
	int32_t m_value;
	bool m_isMine;
	bool m_isOpen;
	bool m_temporaryOpen;
	bool m_isLastOpened;
	bool m_isHighlighted;
};

#endif	  // DOT_H
