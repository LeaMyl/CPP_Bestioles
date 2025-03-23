#ifndef _BESTIOLEFACTORY_H_
#define _BESTIOLEFACTORY_H_

#include <iostream>

#include "Bestiole.h"
#include "AccessoireFactory.h"
#include "IAccessoire.h"

#include "Yeux.h"
#include "Oreilles.h"

using namespace std;

class BestioleFactory
{
private:
   static BestioleFactory* instance;
   AccessoireFactory* factory;
public :

   // Constructeur de base
   BestioleFactory();
   
   // Destructeur de base
   ~BestioleFactory();

   // Création d'une bestiole basique
   Bestiole createBestiole();

   // Création d'une bestiole avec un accessoire
   Bestiole createBestiole(IAccessoire* accessoire);

   // Création d'une bestiole avec des capteurs aléatoires
   Bestiole createBestioleWithRandomSensors();

   // Get singleton instance
   static BestioleFactory* getInstance();
};

#endif // _BESTIOLEFACTORY_H_