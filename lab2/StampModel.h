//
// Created by dmitrii on 3/29/2020.
//

#ifndef TESTCMAKE_STAMPMODEL_H
#define TESTCMAKE_STAMPMODEL_H


#include <QtCore/QString>

class StampModel {
public:
    int id;
    QString name;
    QString country;
    int year;
    int numberIssued;
    QString imageUrl;

    static QStringList getCountries() {
        QStringList list;
        list.append("Poland");
        list.append("United Kingdom");
        list.append("Yemen");
        list.append("USA");
        list.append("Ukraine");
        list.append("Russia");
        return list;
    }
};


#endif //TESTCMAKE_STAMPMODEL_H
