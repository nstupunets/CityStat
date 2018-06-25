#include "cityitem.h"

CityItem::CityItem(const std::string continent, const std::string country, const std::string city, unsigned int population, double highestT, double lowestT)
    : m_continentName(continent)
    , m_countryName(country)
    , m_cityName(city)
    , m_cityPopulation(population)
    , m_recordHighTempereture(highestT)
    , m_recordLowTempereture(lowestT)
{}
