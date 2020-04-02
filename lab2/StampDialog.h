#ifndef TESTCMAKE_STAMPDIALOG_H
#define TESTCMAKE_STAMPDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include "StampModel.h"
#include <QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtCore/QStandardPaths>
#include <QUuid>

class StampDialog : public QDialog {
    Q_OBJECT
    Q_PROPERTY(StampModel Stamp READ getStamp WRITE setStamp)

private:
    QGridLayout *layout;

    QLabel *image;

    QLabel *nameLabel;
    QLabel *yearLabel;
    QLabel *numberIssuedLabel;
    QLabel *countryLabel;
    QLabel *imageLabel;

    QLineEdit *nameEdit;
    QLineEdit *yearEdit;
    QLineEdit *numberIssuedEdit;
    QComboBox *countryEdit;
    QFileDialog *fileDialog;

    QString imageUrl;
    QDialogButtonBox *buttonBox;

    QPushButton *saveButton;
    QPushButton *closeButton;
    QPushButton *imageButton;
public:
    explicit StampDialog(QWidget *parent = nullptr) {
        setWindowTitle("Аттрибуты марки");
        layout = new QGridLayout();
        image = new QLabel("Нет картинки");

        image->setMaximumWidth(200);
        image->setMaximumHeight(200);
        image->setScaledContents(true);

        nameEdit = new QLineEdit();
        numberIssuedEdit = new QLineEdit();

        nameLabel = new QLabel("Название");
        yearLabel = new QLabel("Год");
        countryLabel = new QLabel("Страна");
        numberIssuedLabel = new QLabel("Тираж");
        imageLabel = new QLabel("Изображение");

        nameEdit = new QLineEdit();
        yearEdit = new QLineEdit();
        countryEdit = new QComboBox();
        numberIssuedEdit = new QLineEdit();
        imageButton = new QPushButton("Загрузить изображение");

        fileDialog = new QFileDialog(this, "Выберете изображение", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "Images(*.jpg *.jpeg *.png *.jfif)");
        fileDialog->setFileMode(QFileDialog::FileMode::ExistingFile);
        fileDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);

        QStringList countries = StampModel::getCountries();
        foreach(QString country, countries)
        {
            countryEdit->addItem(country);
        }

        buttonBox = new QDialogButtonBox();
        saveButton = buttonBox->addButton(QDialogButtonBox::StandardButton::Save);
        closeButton = buttonBox->addButton(QDialogButtonBox::StandardButton::Cancel);

        layout->addWidget(image, 0, 0, 1, 2);
        layout->addWidget(nameLabel, 1, 0);
        layout->addWidget(yearLabel, 2, 0);
        layout->addWidget(countryLabel, 3, 0);
        layout->addWidget(numberIssuedLabel, 4, 0);
        layout->addWidget(imageLabel, 5, 0);

        layout->addWidget(nameEdit, 1, 1);
        layout->addWidget(yearEdit, 2, 1);
        layout->addWidget(countryEdit, 3, 1);
        layout->addWidget(numberIssuedEdit, 4, 1);
        layout->addWidget(imageButton, 5, 1);

        layout->addWidget(buttonBox, 6, 0, 1, 2);

        connect(closeButton, &QPushButton::clicked, this, &StampDialog::reject);
        connect(saveButton, &QPushButton::clicked, this, &StampDialog::accept);
        connect(imageButton, &QPushButton::clicked, this, &StampDialog::handleDialog);

        setLayout(layout);
    }

    void setStamp(const StampModel &newStamp) {
        nameEdit->setText(newStamp.name);
        countryEdit->setCurrentText(newStamp.country);
        yearEdit->setText(QString::number(newStamp.year));
        numberIssuedEdit->setText(QString::number(newStamp.numberIssued));
        imageUrl = newStamp.imageUrl;
        updateImage();
    }

    StampModel getStamp() {
        StampModel stamp;

        stamp.name = nameEdit->text();
        stamp.country = countryEdit->currentText();
        stamp.year = yearEdit->text().toInt();
        stamp.numberIssued = numberIssuedEdit->text().toInt();
        stamp.imageUrl = imageUrl;

        return stamp;
    }

    ~StampDialog() override {
        delete layout;
        delete image;
        delete nameLabel;
        delete yearLabel;
        delete numberIssuedLabel;
        delete countryLabel;
        delete imageLabel;
        delete nameEdit;
        delete yearEdit;
        delete numberIssuedEdit;
        delete countryEdit;
        delete fileDialog;
        delete buttonBox;
        delete imageButton;
    }

private:
    void updateImage() {
        QPixmap pm(imageUrl);
        image->setPixmap(pm.scaled(200,200,Qt::KeepAspectRatio));
    }

private slots:
    void handleDialog() {
        if (!imageUrl.isEmpty()) {
            if (QFile::exists(imageUrl))
            {
                QFile::remove(imageUrl);
            }
        }

        if (fileDialog->exec() == QDialog::Accepted)
        {
            foreach(QUrl url, fileDialog->selectedUrls()){
                qDebug() << url.fileName() << url.toString();
                imageUrl = url.toLocalFile();
            }
        }

        QDir picturesDir(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
        QString newFileName = picturesDir.absoluteFilePath(QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces));

        qDebug() << imageUrl << " was loaded" << "copy to" << newFileName;

        if (QFile::copy(imageUrl,  newFileName)) {
            qDebug() << "image was copied";
        }

        imageUrl = newFileName;

        updateImage();
    };
};

#endif //TESTCMAKE_STAMPDIALOG_H
