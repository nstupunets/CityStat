#include "citystatmodel.h"
#include "cityitem.h"
#include "dataloader.h"

CityStatModel::CityStatModel(QObject *parent): QAbstractTableModel(parent)
{
    m_dataLoader = std::make_unique<DataLoader>();
    m_cityItemsList = m_dataLoader->readCityItemsList();
}

CityStatModel::~CityStatModel(){}

QVariant CityStatModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    QString header = "";

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            header = "Continent";
            break;
        case 1:
            header = "Country";
            break;
        case 2:
            header = "City";
            break;
        case 3:
            header = "Population";
            break;
        case 4:
            header = "Highest T";
            break;
        case 5:
            header = "Lowest T";
            break;
        default:
            header = "Unknown";
            break;
        }
        return QVariant(header);
    }

    if (orientation == Qt::Vertical)
    {
        header = QString::number(section+1);
        return QVariant(header);
    }

    return QVariant();
}

//bool CityStatModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}


int CityStatModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_cityItemsList.size();
}

int CityStatModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

QVariant CityStatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_cityItemsList.size() || index.row() < 0)
         return QVariant();

    QVariant returnValue;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        CityItem item = m_cityItemsList.at(index.row());
        if (index.column() == 0)
            returnValue = item.continentName;
        else if (index.column() == 1)
            returnValue = item.countryName;
        else if (index.column() == 2)
            returnValue = item.cityName;
        else if (index.column() == 3)
            returnValue = item.cityPopulation;
        else if (index.column() == 4)
            returnValue = item.recordHighTempereture;
        else if (index.column() == 5)
            returnValue = item.recordLowTempereture;
     }
     return returnValue;
}

bool CityStatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {
        switch (index.column())
        {
        case 0:
        {
            m_cityItemsList[index.row()].continentName=value.toString();
            break;
        }
        case 1:
        {
            m_cityItemsList[index.row()].countryName=value.toString();
            break;
        }
        case 2:
        {
            m_cityItemsList[index.row()].cityName=value.toString();
            break;
        }
        case 3:
        {
            m_cityItemsList[index.row()].cityPopulation=value.toUInt();
            fillPopulationInfo();
            break;
        }
        case 4:
        {
            m_cityItemsList[index.row()].recordHighTempereture=value.toInt();
            break;
        }
        case 5:
        {
            m_cityItemsList[index.row()].recordLowTempereture=value.toInt();
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

bool CityStatModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i<count;i++)
    {
        CityItem item;
        item.continentName="";
        item.countryName="";
        item.cityName="";
        item.cityPopulation = 0;
        item.recordHighTempereture = 0;
        item.recordLowTempereture = 0;
        m_cityItemsList.push_back(item);
    }
    endInsertRows();
    return true;
}

bool CityStatModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

void CityStatModel::saveDataInitiated()
{
    unsigned int savedItemsCounter = 0;
    bool isSavingSuccessfull = m_dataLoader->writeCityItemsList(m_cityItemsList, savedItemsCounter);
    emit isSaveDataSuccessfull(isSavingSuccessfull, savedItemsCounter);
}

void CityStatModel::fillPopulationInfo()
{
    m_minPopulationElement = std::numeric_limits<unsigned int>::max();
    m_maxPopulationElement = 0;
    m_totalPopulationElement = 0;

    for(int i = 0; i < m_cityItemsList.size(); i++)
    {
        if ( m_cityItemsList[i].cityPopulation > m_maxPopulationElement)
            m_maxPopulationElement =  m_cityItemsList[i].cityPopulation;

        if (m_cityItemsList[i].cityPopulation < m_minPopulationElement)
            m_minPopulationElement =  m_cityItemsList[i].cityPopulation;

        m_totalPopulationElement += m_cityItemsList[i].cityPopulation;
    }
    emit populationChanged(m_maxPopulationElement,m_minPopulationElement,m_totalPopulationElement);
}
