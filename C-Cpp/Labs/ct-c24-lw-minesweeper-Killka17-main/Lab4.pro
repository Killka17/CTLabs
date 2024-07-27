TEMPLATE = app
TARGET = Lab4
HEADERS += cell.h board.h mainwindow.h
SOURCES += cell.cpp Board.cpp main.cpp mainwindow.cpp
QT += widgets

RESOURCES += \
    resources.qrc

TRANSLATIONS += Lab4_en.ts \
                Lab4_ru.ts \

CONFIG += c++20
