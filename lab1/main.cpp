#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qApp->setStyleSheet(
                " QWidget { background-color: #FEFEFE; }"
                " QPushButton { background-color: yellow; font-size: 32px; border: 0.5px solid orange; }"
                " QTextEdit {font-size: 32px; border: 0.5px solid orange; color: orange;}"
                " QLabel {background-color: #DEDEDE; font-size: 48px; border: 0.5px solid orange;}"
    );

    w.show();
    return a.exec();
}
