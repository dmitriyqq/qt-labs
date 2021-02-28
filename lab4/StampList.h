#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include <QtSql>
#include "StampModel.hpp"

class StampsList: public QSqlQueryModel
{
    Q_OBJECT

    Q_PROPERTY(QSqlQueryModel* philatelyModel READ getModel CONSTANT)
    Q_PROPERTY(bool IsConnectionOpen READ isConnectionOpen CONSTANT)

public:
    const char* SQL_SELECT = "SELECT name, country, year, numberIssued FROM Stamps S";

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Qt::UserRole + 1] = "stampName";
        roles[Qt::UserRole + 2] = "stampCountry";
        roles[Qt::UserRole + 3] = "stampYear";
        roles[Qt::UserRole + 4] = "stampNumberIssued";
        roles[Qt::UserRole + 5] = "stampId";
        return roles;
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
        QVariant value = QSqlQueryModel::data(index, role);
        if(role < Qt::UserRole-1)
        {
            value = QSqlQueryModel::data(index, role);
        }
        else
        {
            int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
        return value;
    }

    explicit StampsList() {
        QSqlDatabase::removeDatabase("myConnection");

        db = QSqlDatabase::addDatabase("QODBC3", "myConnection");

        QString connectString = "Driver={SQL Server Native Client 11.0};";
        connectString.append("Server=localhost;");
        connectString.append("Database=stamps;");

        db.setDatabaseName(connectString);
         _isConnectionOpen = true;

        if(!db.open("sa", "Password1"))
        {
            qDebug() << db.lastError().text();
            _isConnectionOpen = false;
        }



        refresh();
    }

    void refresh() {
        this->setQuery(SQL_SELECT,db);
    }

    Q_INVOKABLE void add(
        const QString& name,
        const QString& country,
        const int year,
        const int count
    ) {
        QSqlQuery query(db);
        QString strQuery= QString("INSERT INTO stamps (name, country, year, numberIssued) VALUES ('%1', '%2', %3, %4)")
            .arg(name)
            .arg(country)
            .arg(year)
            .arg(count);



        if (!query.exec(strQuery)) {
            qDebug() << lastError().text() << " query: " << strQuery;
        }

        refresh();
    }

    Q_INVOKABLE void del(const int index) {
        QSqlQuery query(db);
        QString strQuery= QString("DELETE FROM Stamps WHERE Id = %1")
            .arg(index);
        query.exec(strQuery);

        refresh();
    }

    Q_INVOKABLE void edit(
            const int index,
            const QString& name,
            const QString& country,
            const int year,
            const int count
    ) {
        QSqlQuery query(db);
        QString strQuery= QString("UPDATE Stamps SET name = '%1',country = '%2',year = %3,numberIssued = %4 WHERE Id = %5")
            .arg(name)
            .arg(country)
            .arg(year)
            .arg(count)
            .arg(index);
        query.exec(strQuery);

        refresh();
    }

signals:

public slots:

private:
    QSqlDatabase db;

    QSqlQueryModel *getModel() {
        return this;
    }

    bool _isConnectionOpen;
    bool isConnectionOpen() {
        return _isConnectionOpen;
    }
};

#endif // STUDENTLIST_H
