#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qApp->setStyleSheet(" QWidget { background-color: blue;} QPushButton { background-color: yellow; font-size: 24px; border: 2px dashed red; } QLabel {background-color: aquamarine; font-size: 48px; border: 0.5px solid orange;}");

    w.show();
    return a.exec();
}
