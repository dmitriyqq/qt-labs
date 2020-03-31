//
// Created by dmitrii on 3/29/2020.
//

#ifndef TESTCMAKE_DIALOGDELEGATE_H
#define TESTCMAKE_DIALOGDELEGATE_H


#include <QtWidgets/QStyledItemDelegate>
#include <QEvent>
#include <QDebug>
#include "StampDialog.h"
#include "PhilatelyModel.h"

class DialogDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit DialogDelegate(QWidget *parent = nullptr, QWidget* parentWidget = nullptr) :
        QStyledItemDelegate(parent), parentWidget(parentWidget) {}

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
              StampDialog editDialog(parentWidget);

              int id = model->data(model->index(index.row(),0)).toInt();
              QString name = model->data(model->index(index.row(),1)).toString();
              QString country = model->data(model->index(index.row(),2)).toString();
              int year = model->data(model->index(index.row(),3)).toInt();
              int numberIssued = model->data(model->index(index.row(),4)).toInt();
              QString imageUrl = model->data(model->index(index.row(), 5)).toString();

              StampModel stamp = { id, name, country, year, numberIssued, imageUrl};
              editDialog.setStamp(stamp);
              if (editDialog.exec() == QDialog::Accepted)
              {
                  auto updatedStamp = editDialog.getStamp();

                  model->setData(model->index(index.row(),1), updatedStamp.name);
                  model->setData(model->index(index.row(),2), updatedStamp.country);
                  model->setData(model->index(index.row(),3), updatedStamp.year);
                  model->setData(model->index(index.row(),4), updatedStamp.numberIssued);
                  model->setData(model->index(index.row(),5), updatedStamp.imageUrl);

                  if (((PhilatelyModel*) model)->submitAll()) {
                      qDebug() << "updated";
                  } else {
                      qDebug() << "update rejected";
                  }
              }
        }
        return false;
    }

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        return nullptr;
    }

private:
    QWidget* parentWidget;
};


#endif //TESTCMAKE_DIALOGDELEGATE_H
