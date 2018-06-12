#include "dataloader.h"
#include "cityitem.h"
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QTextStream>

QList <CityItem> DataLoader::readCityItemsList ()
{
    int unsuccesfullAttempts = 0;
    QList <CityItem> cityItemsList;
    QFile inputData(DATA_FILE_PATH);
    if (!inputData.open(QFile::ReadOnly))
    {
        qCritical() << "Cannot open the file!";
        return cityItemsList;
    }

    while (!inputData.atEnd()) {
        CityItem item;
        QString line = inputData.readLine();
        if (!getDataFromLine(line, item))
            unsuccesfullAttempts++;
        else
            cityItemsList.push_back(item);
    }

    inputData.close();
    qDebug("%d item(s) skipped during loading from file",unsuccesfullAttempts);
    return cityItemsList;
}

bool DataLoader::getDataFromLine(QString cityItemLine, CityItem &cityItem)
{
    if ((cityItemLine.count('\t') + 1) < COLUMS_COUNT)
        return false;
    QStringList lineData = cityItemLine.split('\t');
    if (!m_continetNames.contains(lineData.at(0)))
        return false;

    cityItem.continentName = lineData.at(0);
    cityItem.countryName = lineData.at(1);
    cityItem.cityName = lineData.at(2);

    bool wasConverted = false;
    cityItem.cityPopulation = lineData.at(3).toUInt(&wasConverted);
    if (!wasConverted)
        return false;

    cityItem.recordHighTempereture = lineData.at(4).toInt(&wasConverted);
    if (!wasConverted)
        return false;

    cityItem.recordLowTempereture = lineData.at(5).toInt(&wasConverted);
    if (!wasConverted)
        return false;

    return true;
}

QString DataLoader::cityItemToLine(CityItem cityItem)
{
    QString cityItemLine = "";
    cityItemLine = cityItem.continentName + '\t';
    cityItemLine += cityItem.countryName + '\t';
    cityItemLine += cityItem.cityName + '\t';
    cityItemLine += QString::number(cityItem.cityPopulation) + '\t';
    cityItemLine += QString::number(cityItem.recordHighTempereture) + '\t';
    cityItemLine += QString::number(cityItem.recordLowTempereture) + '\n';

    return cityItemLine;
}

bool DataLoader::writeCityItemsList(QList <CityItem> cityItemsList, unsigned int &savedItemsCounter)
{
    QFile outputData(DATA_FILE_PATH);
    if (!outputData.open(QFile::WriteOnly))
    {
        qCritical() << "Cannot write data to the file!";
        return false;
    }

    savedItemsCounter = 0;
    QTextStream stream( &outputData );

    for (int i = 0; i < cityItemsList.size(); i++)
    {
        stream << cityItemToLine(cityItemsList.at(i));
        savedItemsCounter++;
    }
    qInfo() << "Data successfully saved";

    return true;
}
