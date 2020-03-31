#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTableView>
#include <QSql>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtSql/QSqlRecord>
#include "StampDialog.h"
#include "PhilatelyModel.h"
#include "DialogDelegate.h"
#include <QHeaderView>
#include "ImageDelegate.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTableView *table;
    PhilatelyModel *model;
    QGridLayout *layout;
    QWidget *widget;
    QPushButton *createStampButton;
    QPushButton *deleteStampButton;
    StampDialog *dialog;
    DialogDelegate *dialogDelegate;
    ImageDelegate *imageDelegate;
public:
    explicit MainWindow(QWidget *parent = nullptr)
    {
        setMinimumWidth(800);
        setMinimumHeight(600);
        setWindowTitle("Справочник филателиста");

        widget = new QWidget();
        layout = new QGridLayout();
        table = new QTableView();

        widget->setLayout(layout);

        createStampButton = new QPushButton("Добавить марку");
        deleteStampButton = new QPushButton("Удалить марку");

        layout->addWidget(table, 0, 0, 1, 2);
        layout->addWidget(createStampButton, 1, 0, 1, 1);
        layout->addWidget(deleteStampButton, 1, 1, 1, 1);

        QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
        sdb.setDatabaseName("philately.sqlite");
        model = new PhilatelyModel(sdb);
        table->setModel(model);

        QHeaderView *verticalHeader = table->verticalHeader();
        verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
        verticalHeader->setDefaultSectionSize(100);

        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        dialogDelegate = new DialogDelegate(nullptr, this);
        table->setItemDelegate(dialogDelegate);

        imageDelegate = new ImageDelegate();
        table->setItemDelegateForColumn(5, imageDelegate);

        dialog = new StampDialog();

        connect(createStampButton, &QPushButton::clicked, this, &MainWindow::handleCreateStampButtonClick);
        connect(deleteStampButton, &QPushButton::clicked, this, &MainWindow::handleDeleteStampButtonClick);
        connect(dialog, &StampDialog::accepted, this, &MainWindow::handleStampCreated);

        setCentralWidget(widget);
    }

    ~MainWindow() override {
        delete dialog;
        delete dialogDelegate;
        delete imageDelegate;
        delete layout;
        delete createStampButton;
        delete deleteStampButton;
        delete widget;
        delete table;
        delete model;
    };

private slots:
    void handleCreateStampButtonClick() {
        dialog->setStamp(StampModel());
        dialog->show();
    }

    void handleDeleteStampButtonClick() {
        QModelIndex selectedStamp = table->currentIndex();
        model->deleteStamp(selectedStamp.row());
    }

    void handleStampCreated() {
        auto stamp = dialog->getStamp();
        model->createStamp(stamp);
    }
};
#endif // MAINWINDOW_H
