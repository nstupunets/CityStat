#ifndef CITYSTATMODEL_H
#define CITYSTATMODEL_H

#include "cityitem.h"

#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <memory>
#include <limits>

class DataLoader;

class CityStatModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CityStatModel(QObject *parent = nullptr);
    ~CityStatModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    //bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    //fill population info
    void fillPopulationInfo();
public slots:
    void saveDataInitiated();

signals:
    void isSaveDataSuccessfull(bool isSavingSuccessfull, unsigned int savedItemsCounter);
    void populationChanged(unsigned int maxPopulation,unsigned int minPopulation,unsigned int totalPopulation);

private:
    QList <CityItem> m_cityItemsList;
    std::unique_ptr<DataLoader> m_dataLoader;

    unsigned int m_minPopulationElement = std::numeric_limits<unsigned int>::max();
    unsigned int m_maxPopulationElement = 0;
    unsigned int m_totalPopulationElement = 0;

};

#endif // CITYSTATMODEL_H
