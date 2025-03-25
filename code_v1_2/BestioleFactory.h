#ifndef _BESTIOLEFACTORY_H_
#define _BESTIOLEFACTORY_H_

#include "IBestiole.h"
#include "Configuration.h"
#include <memory>
#include <vector>
#include "Bestiole.h"
#include "AccessoireFactory.h"

class BestioleFactory {
private:
    static BestioleFactory* instance;
    //AccessoireFactory* factory;
public:
    BestioleFactory();
    //BestioleFactory(Configuration* config);

    BestioleFactory* getInstance();
    int initialiserAttributsAgeLimite();
    double initialiserAttributsVitesse();

    double random_between(double a, double b);
    std::vector<std::unique_ptr<Bestiole>> creerPopulationBestioles(int nombreTotal);
    std::unique_ptr<Bestiole> createBestioleWithRandomBestiole() ;
    std::unique_ptr<IBestiole> cloneBestiole(const IBestiole& bestioleToClone);

    std::unique_ptr<Bestiole> ajusterComportementSelonRatios(std::unique_ptr<Bestiole> bestiole);
    std::vector<std::unique_ptr<IBestiole>> ajouterBestiole(const std::vector<IBestiole*>& population, int nombre);

    ~BestioleFactory() ;
};

#endif // _BESTIOLEFACTORY_H_