#include "mainwindow.h"

MainWindow::MainWindow(bool m_debug_mode, QWidget *parent) :
	QMainWindow(parent), m_field(nullptr), m_debug_mode(m_debug_mode), m_is_english(true)
{
	QSettings settings("gameState.ini", QSettings::IniFormat);
	if (settings.contains("Board/need_to_load") && settings.value("Board/need_to_load") == true)
	{
		int32_t rows = settings.value("Board/rows").toInt();
		int32_t cols = settings.value("Board/cols").toInt();
		int32_t mines = settings.value("Board/mines").toInt();
		m_field = new Board(rows, cols, mines, m_debug_mode, m_is_english, this);
		m_field->loadGameState("gameState.ini");
		setCentralWidget(m_field);
	}
	else
	{
		QWidget *centralWidget = new QWidget(this);
		QVBoxLayout *layout = new QVBoxLayout(centralWidget);

		m_rows_label = new QLabel(tr("Rows:"), this);
		m_rows_input = new QLineEdit(this);
		m_rows_input->setText("10");
		m_rows_input->setValidator(new QIntValidator(1, 1000, this));

		m_columns_label = new QLabel(tr("Columns:"), this);
		m_columns_input = new QLineEdit(this);
		m_columns_input->setText("10");
		m_columns_input->setValidator(new QIntValidator(1, 1000, this));

		m_mines_label = new QLabel(tr("Mines:"), this);
		m_mines_input = new QLineEdit(this);
		m_mines_input->setText("10");
		m_mines_input->setValidator(new QIntValidator(1, 10000, this));

		m_start_button = new QPushButton(tr("Start Game"), this);

		m_change_lang_button = new QPushButton(tr("Change Language"), this);

		layout->addWidget(m_rows_label);
		layout->addWidget(m_rows_input);
		layout->addWidget(m_columns_label);
		layout->addWidget(m_columns_input);
		layout->addWidget(m_mines_label);
		layout->addWidget(m_mines_input);
		layout->addWidget(m_start_button);
		layout->addWidget(m_change_lang_button);

		centralWidget->setLayout(layout);
		setCentralWidget(centralWidget);

		connect(m_start_button, &QPushButton::clicked, this, &MainWindow::startGame);
		connect(m_change_lang_button, &QPushButton::clicked, this, &MainWindow::changeLanguage);
	}
}

MainWindow::~MainWindow()
{
	if (m_field)
	{
		delete m_field;
	}
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	QMainWindow::resizeEvent(event);

	QSize windowSize = event->size();
	int32_t new_size = qMax(windowSize.width(), windowSize.height());
	resize(new_size, new_size);
	QWidget::resizeEvent(event);
}

void MainWindow::startGame()
{
	int32_t rows = m_rows_input->text().toInt();
	int32_t columns = m_columns_input->text().toInt();
	int32_t mines = m_mines_input->text().toInt();

	if (rows <= 0 || columns <= 0 || mines <= 0 || mines >= rows * columns)
	{
		QMessageBox::warning(this, tr("Input Error"), tr("Please enter valid game settings."));
		return;
	}
	if (m_field)
	{
		delete m_field;
	}

	m_field = new Board(rows, columns, mines, m_debug_mode, m_is_english, this);
	setCentralWidget(m_field);

	QMessageBox::information(
		this,
		tr("Start Game"),
		tr("Starting game with %1 rows, %2 columns, and %3 mines.").arg(rows).arg(columns).arg(mines));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (m_field)
	{
		m_field->saveGameState("gameState.ini");
	}

	QMainWindow::closeEvent(event);
}

void MainWindow::changeLanguage()
{
	QString language = m_is_english ? "ru.qm" : "en.qm";
	m_is_english = !m_is_english;

	if (m_translator.load(":/translations/Lab4_" + language))
	{
		qApp->installTranslator(&m_translator);
		updateUI();
	}
}

void MainWindow::updateUI()
{
	m_mines_label->setText(tr("Mines:"));
	m_rows_label->setText(tr("Rows:"));
	m_columns_label->setText(tr("Columns:"));
	m_start_button->setText(tr("Start Game"));
	m_change_lang_button->setText(tr("Change Language"));
}
