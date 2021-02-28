#ifndef STAMPMODEL_HPP
#define STAMPMODEL_HPP

#include <QObject>


class StampModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString country READ getCountry WRITE setCountry)
    Q_PROPERTY(QString imageUrl READ getImageUrl WRITE setImageUrl)
    Q_PROPERTY(int id READ getId WRITE setId)
    Q_PROPERTY(int year READ getYear WRITE setYear)
    Q_PROPERTY(int numberIssued READ getNumberIssued WRITE setNumberIssued)
private:
    QString name;
    QString country;
    QString imageUrl;
    int id;
    int year;
    int numberIssued;
public:
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

    QString getName() {
        return this->name;
    }
    QString getCountry() {
        return this->country;
    }
    QString getImageUrl() {
        return this->imageUrl;
    }
    int getId() {
        return this->id;
    }
    int getYear() {
        return this->year;
    }
    int getNumberIssued() {
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
