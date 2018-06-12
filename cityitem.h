#ifndef CITYITEM_H
#define CITYITEM_H

#include <string>

class CityItem
{
public:
    CityItem() = default;
    ~CityItem() = default;
    CityItem(const CityItem& item) = default;
    CityItem(CityItem&& item) = default;

    CityItem(const std::string continent, const std::string country, const std::string city, unsigned int population, double highestT, double lowestT);

    void setContinent(const std::string &continent) { m_continentName = continent; }
    void setCountry(const std::string &country) { m_countryName = country; }
    void setCity(const std::string &city) { m_cityName = city; }
    void setPopulation(unsigned int population) { m_cityPopulation = population; }
    void setHighestT(double temperature) { m_recordHighTempereture = temperature; }
    void setLowestT(double temperature) { m_recordLowTempereture = temperature; }

    const std::string& getContinent() const { return m_continentName; }
    const std::string& getCountry() const { return m_countryName; }
    const std::string& getCity() const { return m_cityName; }
    int getPopulation() const { return m_cityPopulation; }
    double getHighestT() const { return m_recordHighTempereture; }
    double getLowestT() const { return m_recordLowTempereture; }

private:
    std::string m_continentName = "";
    std::string m_countryName = "";
    std::string m_cityName = "";
    unsigned int m_cityPopulation = 0;
    double m_recordHighTempereture = 0;
    double m_recordLowTempereture = 0;
};

#endif // CITYITEM_H
