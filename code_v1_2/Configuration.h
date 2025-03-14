// Configuration.h
#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <string>

class Configuration
{
private:
    static Configuration* instance;
    
    Configuration();
    
public:
    static Configuration* getInstance();
    
    // Comportements
    double tauxGregaire;
    double tauxPeureuse;
    double tauxKamikaze;
    double tauxPrevoyante;
    double tauxMultiple;
    
    // Événements
    double tauxNaissanceSpontanee;
    double probaMortCollision;
    double probaClonage;
    
    // Limites
    double vMax, rMax, etaMax;
    double dMin, dMax;
    double angleMin, angleMax;
    double capaMin, capaMax;
    double psiMin, psiMax;
    
    // Caractéristiques
    int ageLimiteMin, ageLimiteMax;
    double tauxAccessoires;
    double tauxCapteurs;
    
    void setConfigDefault();
    bool loadFromFile(const std::string& filename);
};

#endif // _CONFIGURATION_H_