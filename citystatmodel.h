#ifndef CITYSTATMODEL_H
#define CITYSTATMODEL_H

#include "iaggragateddataprovider.h"
#include "cityitem.h"
#include "dataloader.h"

#include <memory>
#include <limits>
#include <vector>

#include <QAbstractTableModel>
#include <QString>

class DataLoader;

class CityStatModel : public QAbstractTableModel, public IAggragatedDataProvider
{
    Q_OBJECT

public:
    explicit CityStatModel(QObject *parent = nullptr);
    virtual ~CityStatModel();
    //fill population info
    void updatePopulationInfo();
    void saveData();
    bool readData(unsigned int &skippedItemsCount);
    void insertCityItem(const CityItem &item);

signals:
    void dataSaved(bool successfull, unsigned int savedItemsCounter);
    void populationStatisticsChanged();

private:
    // Header:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // Basic functionality:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // Editable:
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    //overloaded methods of IAggragatedDataProvider
    virtual unsigned int getMaxPopulation() const override {return m_maxPopulation;}
    virtual unsigned int getMinPopulation() const override {return m_minPopulation;}
    virtual unsigned int getTotalPopulation() const override {return m_totalPopulation;}

    //private fields
    std::vector <CityItem> m_cityItemsVector;
    DataLoader m_dataLoader;

    unsigned int m_maxPopulation = 0;
    unsigned int m_minPopulation = std::numeric_limits<unsigned int>::max();
    unsigned int m_totalPopulation = 0;
};

#endif // CITYSTATMODEL_H
