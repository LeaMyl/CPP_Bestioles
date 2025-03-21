#ifndef _BESTIOLEFACTORY_H_
#define _BESTIOLEFACTORY_H_

#include "IBestiole.h"
#include "Configuration.h"
#include <memory>
#include <vector>
#include "Bestiole.h"

class BestioleFactory {
private:
    Configuration* config;

public:
    BestioleFactory();
    BestioleFactory(Configuration* config);
    int initialiserAttributsAgeLimite(Configuration* config);
    double initialiserAttributsVitesse(Configuration* config);

    double random_between(double a, double b);
    std::vector<std::unique_ptr<Bestiole>> creerPopulationBestioles(int nombreTotal);
    ~BestioleFactory() ;
};

#endif // _BESTIOLEFACTORY_H_