// Configuration.cpp
#include "Configuration.h"
#include <fstream>
#include <iostream>

Configuration* Configuration::instance = nullptr;

Configuration::Configuration()
{
    setConfigDefault();
}

Configuration* Configuration::getInstance()
{
    if (instance == nullptr)
        instance = new Configuration();
    return instance;
}

void Configuration::setConfigDefault()
{
    // Comportements
    tauxGregaire = 0.2;
    tauxPeureuse = 0.2;
    tauxKamikaze = 0.2;
    tauxPrevoyante = 0.2;
    tauxMultiple = 0.2;
    
    // Événements
    tauxNaissanceSpontanee = 0.01;
    probaMortCollision = 0.3;
    probaClonage = 0.005;
    
    // Limites
    vMax = 10.0;
    rMax = 1.0;
    etaMax = 1.0;
    dMin = 0.0;
    dMax = 30.0;
    angleMin = 0.0;
    angleMax = M_PI/2.0;
    capaMin = 0.5;
    capaMax = 1.0;
    psiMin = 0.0;
    psiMax = 1.0;
    
    // Caractéristiques
    ageLimiteMin = 500;
    ageLimiteMax = 2000;
    tauxAccessoires = 0.7;
    tauxCapteurs = 0.7;
}

bool Configuration::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier de configuration : " << filename << std::endl;
        return false;
    }
    
    std::string paramName;
    double paramValue;
    
    while (file >> paramName >> paramValue) {
        if (paramName == "tauxGregaire") tauxGregaire = paramValue;
        else if (paramName == "tauxPeureuse") tauxPeureuse = paramValue;
        else if (paramName == "tauxKamikaze") tauxKamikaze = paramValue;
        else if (paramName == "tauxPrevoyante") tauxPrevoyante = paramValue;
        else if (paramName == "tauxMultiple") tauxMultiple = paramValue;
        else if (paramName == "tauxNaissanceSpontanee") tauxNaissanceSpontanee = paramValue;
        else if (paramName == "probaMortCollision") probaMortCollision = paramValue;
        else if (paramName == "probaClonage") probaClonage = paramValue;
        else if (paramName == "vMax") vMax = paramValue;
        else if (paramName == "rMax") rMax = paramValue;
        else if (paramName == "etaMax") etaMax = paramValue;
        else if (paramName == "dMin") dMin = paramValue;
        else if (paramName == "dMax") dMax = paramValue;
        else if (paramName == "angleMin") angleMin = paramValue;
        else if (paramName == "angleMax") angleMax = paramValue;
        else if (paramName == "capaMin") capaMin = paramValue;
        else if (paramName == "capaMax") capaMax = paramValue;
        else if (paramName == "psiMin") psiMin = paramValue;
        else if (paramName == "psiMax") psiMax = paramValue;
        else if (paramName == "ageLimiteMin") ageLimiteMin = static_cast<int>(paramValue);
        else if (paramName == "ageLimiteMax") ageLimiteMax = static_cast<int>(paramValue);
        else if (paramName == "tauxAccessoires") tauxAccessoires = paramValue;
        else if (paramName == "tauxCapteurs") tauxCapteurs = paramValue;
    }
    
    file.close();
    return true;
}
