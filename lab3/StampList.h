#ifndef STUDENTLIST_H
#define STUDENTLIST_H


#include <QAbstractListModel>
#include <QVariant>
#include <QList>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QDebug>
#include "StampModel.hpp"

class StampList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* philatelyModel READ getModel CONSTANT)
    Q_PROPERTY(QStringListModel* countriesModel READ getCountriesModel CONSTANT)
private:
    QList<StampModel> stampsList;
    QStringListModel* countries;

    QAbstractListModel* getModel() {
        return this;
    }

public:
    StampList() {
        QStringList list;
        list.append("Poland");
        list.append("United Kingdom");
        list.append("Yemen");
        list.append("USA");
        list.append("Ukraine");
        list.append("Russia");
        countries = new QStringListModel(list);
    }

    ~StampList() override {
        delete countries;
    }


    QStringListModel* getCountriesModel() const {
        return countries;
    }


    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return stampsList.size();
    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
        if (index.row() < 0 || index.row() >= stampsList.size())
             return QVariant();
        switch (role) {
                case name:
                    return QVariant(stampsList.at(index.row()).getName());

                case country:
                    return QVariant(stampsList.at(index.row()).getCountry());

                case year:
                    return QVariant(stampsList.at(index.row()).getYear());

                case numberIssued:
                    return QVariant(stampsList.at(index.row()).getNumberIssued());

                default:
                    return QVariant();
        }
    }

    enum ResentRoles {
        name = Qt::DisplayRole,
        country = Qt::UserRole + 1,
        year = Qt::UserRole + 2,
        numberIssued = Qt::UserRole + 3
    };

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[name] = "stampName";
        roles[country] = "stampCountry";
        roles[year] = "stampYear";
        roles[numberIssued] = "stampNumberIssued";
        return roles;
    }

    Q_INVOKABLE void add(
        const QString& name,
        const QString& country,
        const int year,
        const int count
    ) {
        StampModel stampModel;
        stampModel.setName(name);
        stampModel.setCountry(country);
        stampModel.setYear(year);
        stampModel.setNumberIssued(count);

        beginInsertRows(QModelIndex(), stampsList.size(),stampsList.size());
        stampsList.append(stampModel);
        endInsertRows();
    }

    Q_INVOKABLE void del(const int index) {
        if (index >= 0 && index < stampsList.size())
        {
            beginRemoveRows(QModelIndex(), index, index);
            stampsList.removeAt(index);
            endRemoveRows();
        }
        else qDebug() << "Error index";
    }

    Q_INVOKABLE void edit(
            const int index,
            const QString& name,
            const QString& country,
            const int year,
            const int count
    ) {
        if(index >= 0 && index < stampsList.size() )
        {
           auto& currentStamp = stampsList[index];
           {
               currentStamp.setId(index);
               currentStamp.setName(name);
               currentStamp.setCountry(country);
               currentStamp.setYear(year);
               currentStamp.setNumberIssued(count);

               auto modelIndex = createIndex(index, 0);
               emit dataChanged(modelIndex, modelIndex);
               qDebug() << stampsList[index].getName();
           }

        }
         else qDebug() << "Error index";
    }
};

#endif // STUDENTLIST_H
