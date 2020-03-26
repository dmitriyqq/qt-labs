#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto main_widget = new QWidget();
    setCentralWidget(main_widget);

    auto layout = new QGridLayout();

    std::vector<QString> buttons = { "%", "CE", "C", "DEL",  "1/x", "x^2", "sqrt", "/", "7", "8", "9", "*", "4", "5", "6", "-", "1", "2", "3", "+", "+/-", "0", ".", "="};

    label = new QLabel();

    layout->addWidget(label, 0, 0, 1, 4);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QFont font = label->font();
    font.setPointSize(32);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter | Qt::AlignRight);

    int row = 1;
    int col = 0;
    for(const auto &text : buttons)
    {
        auto button = new QPushButton(text);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(button, row, col);

        connect(button, SIGNAL (released()), this, SLOT (handleButton()));

        col++;
        if (col > 3) {
            col = 0;
            row++;
        }
    }

    main_widget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    QObject *senderObj = sender();
    QPushButton *senderButton = (QPushButton*) senderObj;
    qDebug() << "Pushed button: " << senderButton->text();

    auto b = senderButton->text();

    if (b == "+" || b == "/" || b == "-" || b == "*") {
        accumulator = label->text().toDouble();
        label->setText("");
        operation = b;
    } else if (b == "="){
        auto operB = label->text().toDouble();
        if (operation == "+") {
            label->setText(QString::number(operB + accumulator));
        } else if (operation == "-") {
            label->setText(QString::number(accumulator - operB));
        } else if (operation == "/") {
            if (operB != 0) {
                label->setText(QString::number(operB / accumulator));
            }
        } else if (operation == "*") {
            label->setText(QString::number(operB * accumulator));
        }
    } else if (b == "CE" || b == "C") {
        label->setText("");
    } else if (b == "x^2") {
        auto t = label->text().toDouble();
        label->setText(QString::number(t * t));
    } else if (b == "1/x") {
        auto t = label->text().toDouble();
        label->setText(QString::number(t / t));
    } else if (b == "sqrt") {
        auto t = label->text().toDouble();
        label->setText(QString::number(std::sqrt(t)));
    } else if (b == "DEL") {
        auto t = label->text();
        label->setText(t.remove(t.size() - 1, 1));
    }
    else if (b == "0" && label->text() == "") {

    } else
    {
        label->setText(label->text() + b);
    }

}
