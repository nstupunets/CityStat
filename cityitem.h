#ifndef CITYITEM_H
#define CITYITEM_H

#include <QString>

class CityItem
{
public:
//    CityItem();
//    ~CityItem(){}

    QString continentName;
    QString countryName;
    QString cityName;
    unsigned int cityPopulation;
    int recordHighTempereture;
    int recordLowTempereture;
};

#endif // CITYITEM_H
