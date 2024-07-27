#ifndef FIELD_H
#define FIELD_H

#include "cell.h"

#include <QApplication>
#include <QGridLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QRandomGenerator>
#include <QSettings>
#include <QSize>
#include <QTime>
#include <QTranslator>
#include <QWidget>

class Cell;

class Board : public QWidget
{
	Q_OBJECT

  public:
	Board(int32_t rows, int32_t cols, int32_t mines, bool m_debug_mode, bool m_is_english, QWidget *parent = nullptr);
	~Board();

	void toggleShowMines();
	void loadGameState(const QString &filename);
	void saveGameState(const QString &filename);
	bool m_isGameActive;
	bool need_to_load = true;

  protected slots:
	void clickedLeft();
	void clickRight();
	void clickedMiddle();
	void restartGame();

  signals:
	void finished();

  private:
	QPushButton *restart_button;
	QPushButton *show_mines_button;
	QTranslator m_translator;
	bool m_is_english2;
	QPushButton *languageButton;
	bool m_show_mines;
	int32_t m_n;
	int32_t n_n;
	int32_t m_mineNumber;
	bool m_first_cell;
	Cell *m_lastOpenedDot;
	void openAll();
	bool isValidCell(int32_t i, int32_t j);
	void openDot(int32_t i, int32_t j);
	bool m_is_win();
	void setMines(int32_t a, int32_t b);
	Cell ***m_board;
	bool m_debug_mode;
	void deserialize(QSettings &settings);
	void serialize(QSettings &settings) const;
	void retranslateUI();
	void switchLanguage();
};

#endif	  // FIELD_H
