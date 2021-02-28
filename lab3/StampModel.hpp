#ifndef STAMPMODEL_HPP
#define STAMPMODEL_HPP

#include <QString>
#include <QStringList>
#include <QStringListModel>

class StampModel {
private:
    int id;
    QString name;
    QString country;
    int year;
    int numberIssued;
    QString imageUrl;
public:
    const QString getName() const {
        return this->name;
    }
    const QString getCountry() const {
        return this->country;
    }
    const QString getImageUrl() const {
        return this->imageUrl;
    }

    int getId() const {
        return this->id;
    }
    int getYear() const {
        return this->year;
    }
    int getNumberIssued() const {
        return this->numberIssued;
    }

    void setName(QString name) {
        this->name = name;
    }
    void setCountry(QString country) {
        this->country = country;
    }
    void setImageUrl(QString imageUrl) {
        this->imageUrl = imageUrl;
    }

    void setId(int id) {
        this->id = id;
    }
    void setYear(int year) {
        this->year = year;
    }
    void setNumberIssued(int numberIssued) {
        this->numberIssued = numberIssued;
    }
};

#endif // STAMPMODEL_HPP
