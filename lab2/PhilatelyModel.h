#ifndef TESTCMAKE_PHILATELYMODEL_H
#define TESTCMAKE_PHILATELYMODEL_H

#include <QtSql/QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>

class PhilatelyModel : public QSqlTableModel {
public:
    explicit PhilatelyModel(QSqlDatabase db):
        QSqlTableModel(nullptr, db)
    {
        if (!db.open()) {
            auto error = db.lastError();
            qDebug() << "Could not open database" << error.text();
        }

        auto query = new QSqlQuery("select * from stamps", db);
        if (!query->exec()) {
            qDebug() << "Table does not exists, creating it";

            query->finish();

            db.exec("CREATE TABLE \"stamps\" ("
                     "\"id\"INTEGER PRIMARY KEY AUTOINCREMENT,"
                     "\"name\"TEXT,"
                     "\"country\"TEXT,"
                     "\"year\"NUMERIC,"
                     "\"numberIssued\"INTEGER,"
                     "\"imageUrl\"TEXT)");
        } else {
            query->finish();
            qDebug() << "Table exists already";
        }

        setTable("stamps");
        setEditStrategy(QSqlTableModel::OnManualSubmit);
        qDebug() << "select statement:" << selectStatement();
        select();
    }

public:
    void createStamp(const StampModel &stamp) {
        QSqlRecord newRecord = record();
        newRecord.setValue("name", stamp.name);
        newRecord.setValue("country", stamp.country);
        newRecord.setValue("year", stamp.year);
        newRecord.setValue("numberIssued", stamp.numberIssued);
        newRecord.setValue("imageUrl", stamp.imageUrl);

        if (insertRecord(-1, newRecord)) {
            qDebug() << "record could be inserted";
        } else {
            qDebug() << "record could not be inserted";
        }

        if (submitAll()) {
            qDebug() << "insert was submitted " << lastError().text();
        } else {
            qDebug() << "insert was not Submitted " << lastError().text();
        }
    }

    void deleteStamp(int row) {
        if (deleteRowFromTable(row)) {
            qDebug() << "deleted";
        } else {
            qDebug() << "delete rejected";
        }

        if (submitAll()) {
            qDebug() << "delete submitted " << lastError().text();
        } else {
            qDebug() << "delete was not Submitted " << lastError().text();
        }
    }

};


#endif //TESTCMAKE_PHILATELYMODEL_H
