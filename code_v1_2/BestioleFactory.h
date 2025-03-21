#ifndef _BESTIOLEFACTORY_H_
#define _BESTIOLEFACTORY_H_

#include "IBestiole.h"
#include "Configuration.h"
#include <memory>
#include <vector>

class BestioleFactory {
private:
    Configuration* config;

public:
    BestioleFactory();
    double random_between(double a, double b);
    std::vector<std::unique_ptr<Bestiole>> creerPopulationBestioles(int nombreTotal);
    ~BestioleFactory() ;
};

#endif // _BESTIOLEFACTORY_H_