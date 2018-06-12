#ifndef CITYSTATITEMDELEGATE_H
#define CITYSTATITEMDELEGATE_H

#include "dataloader.h"
#include <QItemDelegate>


class CityStatItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    CityStatItemDelegate(QObject *parent = 0);

private:
    //private methods
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CITYSTATITEMDELEGATE_H
