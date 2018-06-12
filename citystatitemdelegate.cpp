#include "citystatitemdelegate.h"

#include <iostream>

#include <QComboBox>
#include <QWidget>
#include <QModelIndex>
#include <QApplication>
#include <QString>


CityStatItemDelegate::CityStatItemDelegate(QObject *parent):QItemDelegate(parent)
{
  Items.push_back("Africa");
  Items.push_back("Asia");
  Items.push_back("Europe");
  Items.push_back("North America");
  Items.push_back("South America");
  Items.push_back("Australia/Oceania");
}


QWidget *CityStatItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
  QComboBox* editor = new QComboBox(parent);
  for(unsigned int i = 0; i < Items.size(); ++i)
  {
      editor->addItem(Items[i].c_str());
  }
  return editor;
}

void CityStatItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  QString value = (index.model()->data(index,Qt::EditRole)).toString();
  comboBox->setItemText(index.row(),value);
}

void CityStatItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void CityStatItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

void CityStatItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItem myOption = option;
  const QAbstractItemModel *model = index.model();

  QString text = model->data(index).toString();

  myOption.text = text;

  QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
}
