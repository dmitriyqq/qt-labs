//
// Created by dmitrii on 3/29/2020.
//

#ifndef TESTCMAKE_IMAGEDELEGATE_H
#define TESTCMAKE_IMAGEDELEGATE_H

#include <QPixmap>
#include <QLabel>
#include <QPainter>

class ImageDelegate : public QAbstractItemDelegate {
Q_OBJECT
public:
    explicit ImageDelegate(QObject *parent = nullptr):  QAbstractItemDelegate(parent) {}

    ~ImageDelegate() override = default;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QString imageUrl = index.data().toString();

        if (imageUrl.isEmpty()) {
            return;
        }

        QPixmap pm(imageUrl);
        pm = pm.scaled(option.rect.width(), option.rect.height(), Qt::AspectRatioMode::KeepAspectRatio);

        int paddingTop = (option.rect.height() - pm.height()) / 2;
        int paddingLeft = (option.rect.width() - pm.width()) / 2;

        QRect rect = {option.rect.left() + paddingLeft, option.rect.top() + paddingTop, pm.width(), pm.height()};
        painter->drawPixmap(rect, pm);
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        return {100,100};
    }
};
#endif //TESTCMAKE_IMAGEDELEGATE_H
