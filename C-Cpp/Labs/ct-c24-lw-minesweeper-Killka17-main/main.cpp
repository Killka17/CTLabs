#include "mainwindow.h"

#include <QApplication>

int main(int32_t argc, char *argv[])
{
	QApplication app(argc, argv);

	bool m_debug_mode = (argc > 1 && QString(argv[1]) == "dbg");

	MainWindow mainWindow(m_debug_mode);
	mainWindow.show();

	return app.exec();
}
