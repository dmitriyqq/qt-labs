#include "mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(800, 600);
    setWindowTitle("calc");

    centralWidget = new QWidget();
    setCentralWidget(centralWidget);

    layout = new QGridLayout();

    QVector<QString> buttons = {
        "(", ")", "⌫", "/",
        "7", "8", "9", "*",
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "C",  "0", ".", "="
    };

    QSet<QString> highlightedButtons = {
        "(", ")", "⌫", "/", "C",
        "*", "-",  "+", ".", "="
    };

    output = new QLabel();
    input = new QTextEdit();

    layout->addWidget(input, 0, 0, 1, 4);
    layout->addWidget(output, 1, 0, 1, 4);

    input->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    output->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    output->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    output->setText(calculator.getResult());

    int row = 2;
    int col = 0;

    constexpr int NUMBER_COLUMNS = 4;

    for(const auto &text : buttons)
    {
        if (text.length()) {
            auto button = new QPushButton(text);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            if (highlightedButtons.find(text) != highlightedButtons.end()) {
                button->setStyleSheet("color: orange;");
            }
            layout->addWidget(button, row, col);

            connect(button, &QPushButton::released, this, &MainWindow::handleButton);
            buttonWidgets.push_back(button);
        }

        col++;
        if (col > NUMBER_COLUMNS - 1) {
            col = 0;
            row++;
        }
    }

    connect(input, &QTextEdit::textChanged, this, &MainWindow::handleTextEdit);
    connect(&calculator, &Calculator::resultChanged, output, &QLabel::setText);
    connect(this, &MainWindow::inputRecieved, &calculator, &Calculator::handleInput);
    connect(this, &MainWindow::newExpressionRecieved, &calculator, &Calculator::changeExpression);

    centralWidget->setLayout(layout);
}

void MainWindow::highlightOutput() {
    output->setStyleSheet("color: orange; font-size: 64px");
}

void MainWindow::resetOutput() {
    output->setStyleSheet("color: black; font-size: 48px");
}

MainWindow::~MainWindow()
{
    disconnect(input, &QTextEdit::textChanged, this, &MainWindow::handleTextEdit);
    disconnect(&calculator, &Calculator::resultChanged, output, &QLabel::setText);
    disconnect(this, &MainWindow::inputRecieved, &calculator, &Calculator::handleInput);
    disconnect(this, &MainWindow::newExpressionRecieved, &calculator, &Calculator::changeExpression);

    delete centralWidget;
    delete layout;

    for (auto button : buttonWidgets) {
       disconnect(button, &QPushButton::released, this, &MainWindow::handleButton);
       delete button;
    }

    delete input;
    delete output;
}

void MainWindow::handleButton()
{
    resetOutput();

    QObject *senderObj = sender();
    QPushButton *senderButton = (QPushButton*) senderObj;

    // special buttons
    if (senderButton->text() == "C") {
        input->clear();
    } else if (senderButton->text() == "=") {
        highlightOutput();
    } else if (senderButton->text() == "⌫") {
        input->setText(input->toPlainText().remove(-1, 1));
    } else {
        // notify calculator
        emit inputRecieved(senderButton->text());

        // maintain text input value
        input->setText(calculator.getExpression());
    }
}

void MainWindow::handleTextEdit()
{
    resetOutput();
    QObject *senderObj = sender();
    QTextEdit *senderTextEdit = (QTextEdit*) senderObj;

    emit newExpressionRecieved(senderTextEdit->toPlainText());
}
