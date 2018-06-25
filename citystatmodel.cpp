#include "citystatmodel.h"
#include "cityitem.h"

#include <string>
#include <algorithm>

CityStatModel::CityStatModel(QObject *parent): QAbstractTableModel(parent){}

CityStatModel::~CityStatModel(){}

bool CityStatModel::readData(unsigned int &skippedItemsCount)
{
    auto successfull = m_dataLoader.readCityItemsVector(m_cityItemsVector,skippedItemsCount);

    if (successfull)
    {
        m_totalPopulation = 0;
        for(auto &cityItem : m_cityItemsVector)
            m_totalPopulation += cityItem.getPopulation();

        updatePopulationInfo();
    }

    return successfull;
}

QVariant CityStatModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    QString header = "";

    if (orientation == Qt::Horizontal)
    {
        if ((section < 0) || (section > DataLoader::ATTRIBUTES.size() - 1))
            header = "Unknown";
        else
            header = DataLoader::ATTRIBUTES[section];

        return QVariant(header);
    }

    if (orientation == Qt::Vertical)
    {
        header = QString::number(section+1);
        return QVariant(header);
    }

    return QVariant();
}

int CityStatModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_cityItemsVector.size();
}

int CityStatModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return DataLoader::ATTRIBUTES.size();
}

QVariant CityStatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_cityItemsVector.size() || index.row() < 0)
         return QVariant();

    QVariant returnValue;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        CityItem item = m_cityItemsVector.at(index.row());
        if (index.column() == 0)
            returnValue = QString(item.getContinent().c_str());
        else if (index.column() == 1)
            returnValue = QString(item.getCountry().c_str());
        else if (index.column() == 2)
            returnValue = QString(item.getCity().c_str());
        else if (index.column() == 3)
            returnValue = item.getPopulation();
        else if (index.column() == 4)
            returnValue = item.getHighestT();
        else if (index.column() == 5)
            returnValue = item.getLowestT();
     }
     return returnValue;
}

bool CityStatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        CityItem &item = m_cityItemsVector[index.row()];
        switch (index.column())
        {
        case 0:
        {
            item.setContinent(value.toString().toStdString());
            break;
        }
        case 1:
        {
            item.setCountry(value.toString().toStdString());
            break;
        }
        case 2:
        {
            item.setCity(value.toString().toStdString());
            break;
        }
        case 3:
        {
            auto currentValue = value.toUInt();
            if ( currentValue > item.getPopulation())
            {
                auto diff = value.toUInt() - item.getPopulation();
                m_totalPopulation += diff;
            }
            else
            {
                auto diff = item.getPopulation() - value.toUInt();
                m_totalPopulation -= diff;
            }

            auto prevValue = item.getPopulation();
            item.setPopulation(currentValue);

            if (m_minPopulation > currentValue)
                m_minPopulation = currentValue;

            if (m_maxPopulation < currentValue)
                m_maxPopulation = currentValue;

            if ((m_minPopulation == prevValue)||(m_maxPopulation == prevValue))
                updatePopulationInfo();

            emit populationStatisticsChanged();
            break;
        }
        case 4:
        {
            item.setHighestT(value.toDouble());
            break;
        }
        case 5:
        {
            item.setLowestT(value.toDouble());
            break;
        }
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CityStatModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void CityStatModel::saveData()
{
    unsigned int savedItemsCounter = 0;

    bool isSavingSuccessfull = m_dataLoader.writeCityItemsVector(m_cityItemsVector, savedItemsCounter);
    emit dataSaved(isSavingSuccessfull, savedItemsCounter);
}

void CityStatModel::updatePopulationInfo()
{
    auto result = std::minmax_element(m_cityItemsVector.begin(), m_cityItemsVector.end(),
        [](const auto &first, const auto &second) {return first.getPopulation() < second.getPopulation();});

    m_minPopulation = (*result.first).getPopulation();
    m_maxPopulation = (*result.second).getPopulation();
}

void CityStatModel::insertCityItem(const CityItem& item)
{
     beginInsertRows(QModelIndex(), rowCount(), rowCount());
     m_cityItemsVector.push_back(item);
     endInsertRows();
}
