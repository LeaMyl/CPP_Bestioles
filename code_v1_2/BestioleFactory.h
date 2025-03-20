// BestioleFactory.h
#ifndef _BESTIOLEFACTORY_H_
#define _BESTIOLEFACTORY_H_

#include "Bestiole.h"
#include "FactoryMethod.h"

class BestioleFactory : public FactoryMethod {
    public:
        // Destructeur
        ~BestioleFactory() override = default;
        // Méthode pour créer une bestiole
        IBestiole* creerIBestiole() override {
            return new Bestiole();
        }
    };
#endif // BESTIOLEFACTORY_H