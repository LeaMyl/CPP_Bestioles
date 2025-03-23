#ifndef _ACCESSOIRE_FACTORY_H_
#define _ACCESSOIRE_FACTORY_H_

#include "IAccessoire.h"
#include "Nageoires.h"
#include "Carapace.h"
#include "Camouflage.h"

#include "Configuration.h" // Pour définir les paramètres de configuration

class AccessoireFactory {
private:   
    static AccessoireFactory* instance;
    
    // Configuration
    double MAX_NU = Configuration::MAX_NU;
    double MAX_OMEGA = Configuration::MAX_OMEGA;      
    double MAX_ETA = Configuration::MAX_ETA;    
    double MAX_PSI = Configuration::MAX_PSI;
    double MIN_PSI = Configuration::MIN_PSI; 
    double TAUX_ACCESSOIRES = Configuration::TAUX_ACCESSOIRES;
    
    // Private constructor for singleton
    AccessoireFactory();
    
public:
    // Get singleton instance
    static AccessoireFactory* getInstance();
    
    // Destructor
    ~AccessoireFactory();
    
    // Set configuration parameters
    void setConfig(double MAX_NU, double MAX_OMEGA, double MAX_ETA, double MIN_PSI, double MAX_PSI);
    
    // Create accessories with random attributes within configured ranges
    IAccessoire* createNageoires();
    IAccessoire* createCarapace();
    IAccessoire* createCamouflage();
    
    // Create a random accessory
    IAccessoire* createRandomAccessoire();
};

#endif