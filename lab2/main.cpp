#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qApp->setStyleSheet(
            " QWidget { background-color: #FEFEFE; }"
            " MainWindow QPushButton { background-color: yellow; font-size: 32px; border: 0.5px solid orange; }"
            " QDialogButtonBox QPushButton { background-color: yellow; font-size: 32px; border: 0.5px solid orange; } "
    );

    return a.exec();
}
