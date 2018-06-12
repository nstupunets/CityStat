#include "dataloader.h"
#include "cityitem.h"
#include <algorithm>
#include <fstream>

constexpr std::array <const char*,DataLoader::CONTINENTS_COUNT> DataLoader::CONTINENTS;
constexpr std::array <const char*,DataLoader::COLUMS_COUNT> DataLoader::ATTRIBUTES;

bool DataLoader::readCityItemsVector (std::vector <CityItem> &cityItemsVector, unsigned int &skippedItemsCount)
{
    skippedItemsCount = 0;
    cityItemsVector.clear();

    std::string line;
    std::ifstream inputData(DATA_FILE_PATH);
    if (!inputData.is_open())
        return false;

    while (std::getline(inputData,line))
    {
        CityItem item;
        if (!getDataFromLine(line, item))
            skippedItemsCount++;
        else
            cityItemsVector.push_back(item);
    }

    inputData.close();
//    qDebug("%d item(s) skipped during loading from file",unsuccesfullAttempts);
    return true;
}

bool DataLoader::getDataFromLine(const std::string &cityItemLine, CityItem &cityItem)
{
    if (cityItemLine.empty())
        return false;

    std::vector <std::string> cityItemData;
    int columnCount = 0;
    size_t startPos = 0, endPos = 0;

    while(startPos < cityItemLine.length())
    {
        endPos = cityItemLine.find('\t', startPos);
        if (endPos == std::string::npos)
            endPos = cityItemLine.length();

        std::string str = cityItemLine.substr(startPos,endPos-startPos);
        cityItemData.push_back(str);

        startPos = endPos + 1;
        columnCount++ ;
    }

    if (columnCount != COLUMS_COUNT)
        return false;

    //fill CityItem data with string info
    auto it = std::find(DataLoader::CONTINENTS.begin(), DataLoader::CONTINENTS.end(), cityItemData[0]);
    if (it == DataLoader::CONTINENTS.end())
        return false;

    cityItem.setContinent(cityItemData[0]);
    cityItem.setCountry(cityItemData[1]);
    cityItem.setCity(cityItemData[2]);
    try
    {
        cityItem.setPopulation(std::stoul(cityItemData[3],nullptr));
        cityItem.setHighestT(std::stod(cityItemData[4],nullptr));
        cityItem.setLowestT(std::stod(cityItemData[5],nullptr));
    }
    catch(const std::invalid_argument&)
    {
        return false;
    }

    return true;
}

std::string DataLoader::cityItemToLine(const CityItem &cityItem)
{
    auto cityItemLine = cityItem.getContinent() + '\t';
    cityItemLine += cityItem.getCountry() + '\t';
    cityItemLine += cityItem.getCity() + '\t';
    cityItemLine += std::to_string(cityItem.getPopulation()) + '\t';
    cityItemLine += std::to_string(cityItem.getHighestT()) + '\t';
    cityItemLine += std::to_string(cityItem.getLowestT()) + '\n';

    return cityItemLine;
}

bool DataLoader::writeCityItemsVector(const std::vector <CityItem> &cityItemsVector, unsigned int &savedItemsCounter)
{
    std::ofstream outputData(DATA_FILE_PATH);
    savedItemsCounter = 0;

    if (!outputData.is_open())
        return false;

    for (auto &i : cityItemsVector)
    {
        outputData << cityItemToLine(i);
        savedItemsCounter++;
    }

    outputData.close();
    return true;
}
