#ifndef CITYSTATITEMDELEGATE_H
#define CITYSTATITEMDELEGATE_H

#include <QItemDelegate>


class CityStatItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    CityStatItemDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    std::vector<std::string> Items;
};

#endif // CITYSTATITEMDELEGATE_H
