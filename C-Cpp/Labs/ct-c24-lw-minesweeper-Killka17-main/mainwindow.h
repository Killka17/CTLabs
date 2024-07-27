#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"

#include <QApplication>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QResizeEvent>
#include <QTranslator>
#include <filesystem>

class Board;

class MainWindow : public QMainWindow
{
	Q_OBJECT

  public:
	MainWindow(bool m_debug_mode, QWidget *parent = nullptr);
	~MainWindow();

  private slots:
	void startGame();
	void changeLanguage();
	void updateUI();

  private:
	void resizeEvent(QResizeEvent *event) override;
	void closeEvent(QCloseEvent *event) override;
	void loadGameState();
	QLineEdit *m_rows_input;
	QLineEdit *m_columns_input;
	QLineEdit *m_mines_input;
	QPushButton *m_start_button;
	QPushButton *m_change_lang_button;
	QLabel *m_rows_label;
	QLabel *m_columns_label;
	QLabel *m_mines_label;
	Board *m_field;
	bool m_debug_mode;
	QTranslator m_translator;
	bool m_is_english;
};

#endif	  // MAINWINDOW_H
