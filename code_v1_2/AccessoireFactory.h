#ifndef _ACCESSOIRE_FACTORY_H_
#define _ACCESSOIRE_FACTORY_H_

#include "Configuration.h"  // Paramètres de configuration
#include "IAccessoire.h"    // Interface des accessoires
#include "Nageoires.h"      // Accessoire de nageoires
#include "Carapace.h"       // Accessoire de carapace
#include "Camouflage.h"     // Accessoire de camouflage

/**
 * @class AccessoireFactory
 * @brief Fabrique de singleton pour la création d'accessoires de créatures
 * 
 * Cette fabrique implémente le patron Singleton pour gérer la création 
 * de différents types d'accessoires avec des paramètres aléatoires configurables.
 */
class AccessoireFactory {
private:   
    // Instance unique du singleton
    static AccessoireFactory* instance;
    
    // Paramètres de configuration avec valeurs par défaut
    double MAX_NU = Configuration::MAX_NU;      // Coefficient max de vitesse des nageoires
    double MAX_OMEGA = Configuration::MAX_OMEGA;// Coefficient max de résistance de la carapace
    double MAX_ETA = Configuration::MAX_ETA;    // Coefficient max de réduction de vitesse
    double MAX_PSI = Configuration::MAX_PSI;    // Coefficient max de camouflage
    double MIN_PSI = Configuration::MIN_PSI;    // Coefficient min de camouflage
    double TAUX_ACCESSOIRES = Configuration::TAUX_ACCESSOIRES; // Taux d'accessoires
    
    // Constructeur privé pour empêcher l'instanciation externe
    AccessoireFactory();
    
public:
    // Obtenir l'instance unique du singleton
    static AccessoireFactory* getInstance();
    
    // Destructeur
    ~AccessoireFactory();
    
    // Modifier les paramètres de configuration avec validation
    void setConfig(double MAX_NU, double MAX_OMEGA, double MAX_ETA, 
                   double MIN_PSI, double MAX_PSI);
    
    // Créer des types spécifiques d'accessoires avec attributs aléatoires
    IAccessoire* createNageoires();    // Créer des nageoires
    IAccessoire* createCarapace();     // Créer une carapace
    IAccessoire* createCamouflage();   // Créer un camouflage
    
    // Créer un accessoire complètement aléatoire
    IAccessoire* createRandomAccessoire();
};

#endif // _ACCESSOIRE_FACTORY_H_