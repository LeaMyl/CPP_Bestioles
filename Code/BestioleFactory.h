#ifndef _BESTIOLEFACTORY_H_
#define _BESTIOLEFACTORY_H_

#include "IBestiole.h"
#include "Configuration.h"
#include "FactoryMethod.h"
#include <memory>
#include <vector>
#include "Bestiole.h"
#include "AccessoireFactory.h"

class BestioleFactory : public FactoryMethod {
private:
    static BestioleFactory* instance;

public:
    BestioleFactory();

    // Implémentation de la méthode virtuelle de FactoryMethod
    IBestiole* creerIBestiole() override {
        return createBestioleWithRandomBestiole().release();
    }

    BestioleFactory* getInstance();
    int initialiserAttributsAgeLimite();
    double initialiserAttributsVitesse();

    double random_between(double a, double b);
    std::vector<std::unique_ptr<Bestiole>> creerPopulationBestioles(int nombreTotal);
    std::unique_ptr<Bestiole> createBestioleWithRandomBestiole();
    std::unique_ptr<IBestiole> cloneBestiole(const IBestiole& bestioleToClone);

    std::unique_ptr<Bestiole> ajusterComportementSelonRatios(
        std::unique_ptr<Bestiole> bestiole, 
        const std::vector<IBestiole*>& population);
    std::vector<std::unique_ptr<IBestiole>> ajouterBestiole(const std::vector<IBestiole*>& population, int nombre);

    ~BestioleFactory();
};

#endif // _BESTIOLEFACTORY_H_