#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>

#include "Calculator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

signals:
    void inputRecieved(const QString&);
    void newExpressionRecieved(const QString&);

private slots:
    void handleButton();
    void handleTextEdit();
private:
    void highlightOutput();
    void resetOutput();

    Calculator calculator;
    QVector<QPushButton*> buttonWidgets;

    QTextEdit* input;
    QLabel* output;
    QWidget* centralWidget;
    QGridLayout* layout;

};

#endif // MAINWINDOW_H
