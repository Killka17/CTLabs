#include "board.h"

Board::Board(int32_t rows, int32_t cols, int32_t mines, bool m_debug_mode, bool m_is_english, QWidget *parent) :
	QWidget(parent), m_isGameActive(true), m_is_english2(m_is_english), m_n(rows), n_n(cols), m_mineNumber(mines),
	m_lastOpenedDot(nullptr), m_debug_mode(m_debug_mode)
{
	m_board = new Cell **[m_n];
	for (int32_t i = 0; i < m_n; ++i)
	{
		m_board[i] = new Cell *[n_n];
		for (int32_t j = 0; j < n_n; ++j)
		{
			m_board[i][j] = new Cell(i, j, this);
		}
	}

	QGridLayout *layout = new QGridLayout(this);
	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			layout->addWidget(m_board[i][j], i, j, 1, 1);
			connect(m_board[i][j], SIGNAL(clicked_left()), this, SLOT(clickedLeft()));
			connect(m_board[i][j], SIGNAL(clicked_right()), this, SLOT(clickRight()));
			connect(m_board[i][j], SIGNAL(clicked_middle()), this, SLOT(clickedMiddle()));
		}
	}

	restart_button = new QPushButton("Restart Game", this);
	layout->addWidget(restart_button, m_n, 0, 1, n_n);
	connect(restart_button, &QPushButton::clicked, this, &Board::restartGame);

	languageButton = new QPushButton("Change Language", this);
	layout->addWidget(languageButton, m_n + 2, 0, 1, n_n);
	connect(languageButton, &QPushButton::clicked, this, &Board::switchLanguage);

	if (m_debug_mode)
	{
		show_mines_button = new QPushButton("Show Mines", this);
		layout->addWidget(show_mines_button, m_n + 1, 0, 1, n_n);
		connect(show_mines_button, &QPushButton::clicked, this, &Board::toggleShowMines);
	}
	if (!m_is_english2)
	{
		m_is_english2 = true;
		switchLanguage();
	}
}

Board::~Board()
{
	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			delete m_board[i][j];
		}
		delete[] m_board[i];
	}
	delete[] m_board;
}
void Board::restartGame()
{
	int32_t newRows = QInputDialog::getInt(this, tr("Restart Game"), tr("Enter number of rows:"), m_n, 1, 1000, 1);

	int32_t newCols = QInputDialog::getInt(this, tr("Restart Game"), tr("Enter number of columns:"), n_n, 1, 1000, 1);

	int32_t newMines =
		QInputDialog::getInt(this, tr("Restart Game"), tr("Enter number of mines:"), m_mineNumber, 1, newRows * newCols - 1, 1);

	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			delete m_board[i][j];
		}
		delete[] m_board[i];
	}
	delete[] m_board;

	m_n = newRows;
	n_n = newCols;
	m_mineNumber = newMines;
	m_isGameActive = true;
	m_first_cell = true;
	m_lastOpenedDot = nullptr;

	m_board = new Cell **[m_n];
	for (int32_t i = 0; i < m_n; ++i)
	{
		m_board[i] = new Cell *[n_n];
		for (int32_t j = 0; j < n_n; ++j)
		{
			m_board[i][j] = new Cell(i, j, this);
		}
	}

	QGridLayout *layout = qobject_cast< QGridLayout * >(this->layout());
	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			layout->addWidget(m_board[i][j], i, j, 1, 1);
			connect(m_board[i][j], SIGNAL(clicked_left()), this, SLOT(clickedLeft()));
			connect(m_board[i][j], SIGNAL(clicked_right()), this, SLOT(clickRight()));
			connect(m_board[i][j], SIGNAL(clicked_middle()), this, SLOT(clickedMiddle()));
		}
	}

	layout->addWidget(restart_button, m_n, 0, 1, n_n);

	if (m_debug_mode)
	{
		if (!show_mines_button)
		{
			show_mines_button = new QPushButton("Show Mines", this);
			connect(show_mines_button, &QPushButton::clicked, this, &Board::toggleShowMines);
		}
		layout->addWidget(show_mines_button, m_n + 1, 0, 1, n_n);
	}
	need_to_load = true;
	layout->update();
	update();
}

bool Board::isValidCell(int32_t i, int32_t j)
{
	return i >= 0 && j >= 0 && i < m_n && j < n_n;
}

void Board::openDot(int32_t i, int32_t j)
{
	if (!isValidCell(i, j))
		return;
	Cell *p = m_board[i][j];
	if (p->is_open())
		return;
	if (p->m_is_flag)
		return;

	if (m_first_cell)
	{
		setMines(i, j);
		m_first_cell = false;
	}

	if (m_lastOpenedDot != nullptr)
	{
		m_lastOpenedDot->setLastOpened(false);
	}
	m_board[i][j]->setLastOpened(true);
	m_lastOpenedDot = p;
	p->setOpen();
	if (p->value())
		return;

	openDot(i - 1, j);
	openDot(i + 1, j);
	openDot(i, j - 1);
	openDot(i, j + 1);
}

void Board::setMines(int32_t firstI, int32_t firstJ)
{
	for (int32_t i = 0; i < m_mineNumber;)
	{
		int32_t x = QRandomGenerator::global()->bounded(m_n);
		int32_t y = QRandomGenerator::global()->bounded(n_n);
		if (m_board[x][y]->is_mine() || (x == firstI && y == firstJ))
		{
			continue;
		}
		else
		{
			m_board[x][y]->setMine();
			++i;
		}
	}

	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			if (m_board[i][j]->is_mine())
			{
				if (isValidCell(i - 1, j - 1))
					m_board[i - 1][j - 1]->valueInc();
				if (isValidCell(i - 1, j))
					m_board[i - 1][j]->valueInc();
				if (isValidCell(i - 1, j + 1))
					m_board[i - 1][j + 1]->valueInc();
				if (isValidCell(i, j - 1))
					m_board[i][j - 1]->valueInc();
				if (isValidCell(i, j + 1))
					m_board[i][j + 1]->valueInc();
				if (isValidCell(i + 1, j - 1))
					m_board[i + 1][j - 1]->valueInc();
				if (isValidCell(i + 1, j))
					m_board[i + 1][j]->valueInc();
				if (isValidCell(i + 1, j + 1))
					m_board[i + 1][j + 1]->valueInc();
			}
		}
	}
}

bool Board::m_is_win()
{
	int32_t n = m_n * n_n - m_mineNumber;
	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			if (m_board[i][j]->is_open() && !m_board[i][j]->is_mine())
			{
				--n;
			}
		}
	}
	return n == 0;
}

void Board::clickRight()
{
	if (!m_isGameActive)
		return;
	Cell *t = qobject_cast< Cell * >(sender());
	if (t->is_open())
		return;
	t->swapFlag();
}

void Board::clickedMiddle()
{
	if (!m_isGameActive)
		return;
	Cell *t = qobject_cast< Cell * >(sender());
	int32_t i = t->i();
	int32_t j = t->j();
	int32_t counter = 0;
	QList< QPair< int32_t, int32_t > > unopenedCells;
	for (int32_t x = i - 1; x <= i + 1; ++x)
	{
		for (int32_t y = j - 1; y <= j + 1; ++y)
		{
			if (isValidCell(x, y))
			{
				if (m_board[x][y]->m_is_flag && (!(m_board[x][y]->is_mine())))
				{
					m_board[x][y]->highlight();
					counter++;
				}
				else if (!(m_board[x][y]->m_is_flag) && m_board[x][y]->is_mine())
				{
					m_board[x][y]->highlight();
					counter++;
				}
				else
				{
					unopenedCells.append(QPair< int32_t, int32_t >(x, y));
				}
			}
		}
	}
	if (counter == 0)
	{
		for (const auto &cell : unopenedCells)
		{
			openDot(cell.first, cell.second);
		}
	}
}

void Board::openAll()
{
	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			m_board[i][j]->setOpen();
		}
	}
}

void Board::clickedLeft()
{
	if (!m_isGameActive)
		return;
	Cell *t = qobject_cast< Cell * >(sender());
	if (t->is_open())
		return;
	if (t->m_is_flag)
		return;

	openDot(t->i(), t->j());

	if (t->is_mine())
	{
		m_isGameActive = false;
		need_to_load = false;
		t->setLastOpened(true);
		QMessageBox::information(this, tr("Lose"), tr("You hit a mine!"));
		openAll();
		emit finished();
		return;
	}

	if (m_is_win())
	{
		m_isGameActive = false;
		need_to_load = false;
		QMessageBox::information(this, tr("Win"), tr("You win!"));
		openAll();
		emit finished();
		return;
	}
}

void Board::toggleShowMines()
{
	static bool m_show_mines = false;
	m_show_mines = !m_show_mines;
	if (m_show_mines)
	{
		show_mines_button->setText(tr("Hide Mines"));
	}
	else
	{
		show_mines_button->setText(tr("Show Mines"));
	}

	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			if (m_board[i][j]->is_mine())
			{
				m_board[i][j]->setTemporaryOpen(m_show_mines);
			}
		}
	}
}

void Board::serialize(QSettings &settings) const
{
	if (!need_to_load)
	{
		settings.setValue("need_to_load", false);
		return;
	}
	settings.beginGroup("Board");
	settings.setValue("english", m_is_english2);
	settings.setValue("need_to_load", need_to_load);
	settings.setValue("rows", m_n);
	settings.setValue("cols", n_n);
	settings.setValue("mines", m_mineNumber);
	settings.setValue("isGameActive", m_isGameActive);
	settings.setValue("firstCell", m_first_cell);
	settings.setValue("lastOpenedDot", m_lastOpenedDot ? m_lastOpenedDot->i() * n_n + m_lastOpenedDot->j() : -1);

	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			m_board[i][j]->serialize(settings);
		}
	}
	settings.endGroup();
}

void Board::deserialize(QSettings &settings)
{
	settings.beginGroup("Board");
	m_n = settings.value("rows").toInt();
	n_n = settings.value("cols").toInt();
	m_is_english2 = settings.value("english").toBool();
	m_mineNumber = settings.value("mines").toInt();
	m_isGameActive = settings.value("isGameActive").toBool();
	m_first_cell = settings.value("firstCell").toBool();
	int32_t lastOpenedIndex = settings.value("lastOpenedDot").toInt();
	m_lastOpenedDot = lastOpenedIndex != -1 ? m_board[lastOpenedIndex / n_n][lastOpenedIndex % n_n] : nullptr;

	for (int32_t i = 0; i < m_n; ++i)
	{
		for (int32_t j = 0; j < n_n; ++j)
		{
			m_board[i][j]->deserialize(settings);
		}
	}
	settings.endGroup();
}

void Board::saveGameState(const QString &filename)
{
	QSettings settings(filename, QSettings::IniFormat);
	settings.clear();
	serialize(settings);
}

void Board::loadGameState(const QString &filename)
{
	QSettings settings(filename, QSettings::IniFormat);
	deserialize(settings);
	if (!m_is_english2)
	{
		m_is_english2 = true;
		switchLanguage();
	}
}

void Board::switchLanguage()
{
	QString lang = m_is_english2 ? "ru.qm" : "en.qm";
	m_is_english2 = !m_is_english2;

	if (m_translator.load(":/translations/Lab4_" + lang))
	{
		qApp->installTranslator(&m_translator);
	}

	restart_button->setText(tr("Restart Game"));
	languageButton->setText(tr("Change Language"));
	if (m_debug_mode)
	{
		if (!m_first_cell)
		{
			if (m_show_mines)
			{
				m_show_mines = !m_show_mines;
				show_mines_button->setText(tr("Hide Mines"));
			}
			else
			{
				show_mines_button->setText(tr("Show Mines"));
				m_show_mines = !m_show_mines;
			}
		}
		else
		{
			show_mines_button->setText(tr("Show Mines"));
		}
	}
}
