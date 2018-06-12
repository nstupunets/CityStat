#ifndef DATALOADER_H
#define DATALOADER_H

#include <QList>
#include <QVector>
#include <QString>
#include <QByteArray>

class CityItem;

class DataLoader
{
public:
    QList <CityItem> readCityItemsList() ;
    bool writeCityItemsList (QList <CityItem> cityItemsList, unsigned int &savedItemsCounter) ;
    //static const int getColumsCount () const { return COLUMS_COUNT; }

    QVector <QString> m_continetNames = {"Africa" ,"Asia", "Europe", "North America", "South America", "Australia/Oceania"};
private:
    bool getDataFromLine(QString cityItemLine, CityItem &cityItem);
    QString cityItemToLine(CityItem cityItem);

    static constexpr char* DATA_FILE_PATH = "C:\\Users\\nstupynets\\Documents\\CityStat\\data\\CityInfoStatistics.txt";
    static const int COLUMS_COUNT = 6;
};

#endif // DATALOADER_H
