#ifndef IAGGRAGATEDDATAPROVIDER_H
#define IAGGRAGATEDDATAPROVIDER_H

class IAggragatedDataProvider
{
public:
    virtual unsigned int getMaxPopulation() const = 0;
    virtual unsigned int getMinPopulation() const = 0;
    virtual unsigned int getTotalPopulation() const = 0;
};
#endif // IAGGRAGATEDDATAPROVIDER_H
