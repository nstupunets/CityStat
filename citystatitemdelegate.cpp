#include "citystatitemdelegate.h"

#include <iostream>

#include <QComboBox>
#include <QWidget>
#include <QModelIndex>
#include <QApplication>
#include <QString>
#include <QDebug>


CityStatItemDelegate::CityStatItemDelegate(QObject *parent):QItemDelegate(parent)
{}


QWidget *CityStatItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
  auto *editor = new QComboBox(parent);
  for(auto &i : DataLoader::CONTINENTS)
  {
      editor->addItem(i);
  }
  return editor;
}

void CityStatItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  auto *comboBox = static_cast<QComboBox*>(editor);
  auto value = index.model()->data(index,Qt::DisplayRole).toString();
  comboBox->setCurrentIndex(comboBox->findText(value));
}

void CityStatItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  auto *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void CityStatItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

void CityStatItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  auto myOption = option;
  const auto *model = index.model();

  auto text = model->data(index).toString();

  myOption.text = text;

  QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
}
