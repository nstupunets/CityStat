#ifndef DATALOADER_H
#define DATALOADER_H

#include <array>
#include <vector>
#include <string>
#include <QStringList>
class CityItem;

class DataLoader
{
public:
    bool readCityItemsVector(std::vector <CityItem> &cityItemsVector, unsigned int &skippedItemsCount) ;
    bool writeCityItemsVector (const std::vector <CityItem> &cityItemsVector, unsigned int &savedItemsCounter) ;
    //static const int getColumsCount () const { return COLUMS_COUNT; }

    static const int COLUMS_COUNT = 6;
    static const int CONTINENTS_COUNT = 6;
    static constexpr std::array <const char*,CONTINENTS_COUNT> CONTINENTS = {"Africa", "Asia", "Europe", "North America", "South America", "Australia/Oceania"};
    static constexpr std::array <const char*,COLUMS_COUNT> ATTRIBUTES = {"Continent", "Country", "City", "Population", "Highest T", "Lowest T"};
private:
    bool getDataFromLine(const std::string &cityItemLine, CityItem &cityItem);
    std::string cityItemToLine(const CityItem &cityItem);

    static constexpr const char* DATA_FILE_PATH = "..\\CityStat\\data\\CityInfoStatistics.txt";
};

#endif // DATALOADER_H
