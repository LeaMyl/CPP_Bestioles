#include "AccessoireFactory.h"
#include <cstdlib>
#include <ctime>

// Initialize static instance
AccessoireFactory* AccessoireFactory::instance = nullptr;

AccessoireFactory::AccessoireFactory() {
    // Configuration des paramètres dans Configuration.h
    MAX_NU = Configuration::MAX_NU;
    MAX_OMEGA = Configuration::MAX_OMEGA;      
    MAX_ETA = Configuration::MAX_ETA;    
    MAX_PSI = Configuration::MAX_PSI;
    MIN_PSI = Configuration::MIN_PSI;  
    TAUX_ACCESSOIRES = Configuration::TAUX_ACCESSOIRES;
    
    // Génère une seed aléatoire
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

AccessoireFactory* AccessoireFactory::getInstance() {
    if (instance == nullptr) {
        instance = new AccessoireFactory();
    }
    return instance;
}

AccessoireFactory::~AccessoireFactory() {
    // Nothing to clean up
}

void AccessoireFactory::setConfig(double _MAX_NU, double _MAX_OMEGA, double _MAX_ETA, double _MIN_PSI, double _MAX_PSI) {
    MAX_NU = _MAX_NU > 1.0 ? _MAX_NU : 1.0;
    MAX_OMEGA = _MAX_OMEGA > 1.0 ? _MAX_OMEGA : 1.0;
    MAX_ETA = _MAX_ETA > 1.0 ? _MAX_ETA : 1.0;
    MIN_PSI = _MIN_PSI < 0.0 ? 0.0 : (_MIN_PSI > 1.0 ? 1.0 : _MIN_PSI);  
    MAX_PSI = _MAX_PSI < MIN_PSI ? MIN_PSI : (_MAX_PSI > 1.0 ? 1.0 : _MAX_PSI); 
}

IAccessoire* AccessoireFactory::createNageoires() {
    // Vitesses aléatoires entre 1.0 et MAX_NU
    double coeff = 1.0 + static_cast<double>(rand()) / RAND_MAX * (MAX_NU - 1.0);
    return new Nageoires(coeff);
}

IAccessoire* AccessoireFactory::createCarapace() {
    // Resistance aléatoire entre 1.0 et MAX_OMEGA
    double resistance = 1.0 + static_cast<double>(rand()) / RAND_MAX * (MAX_OMEGA - 1.0);
    // Réduction aléatoire entre 1.0 et MAX_ETA
    double reduction = 1.0 + static_cast<double>(rand()) / RAND_MAX * (MAX_ETA - 1.0);
    return new Carapace(resistance, reduction);
}

IAccessoire* AccessoireFactory::createCamouflage() {
    // Camouflage aléatoire entre MIN_PSI et MAX_PSI
    double coeff = MIN_PSI + static_cast<double>(rand()) / RAND_MAX * (MAX_PSI - MIN_PSI);
    return new Camouflage(coeff);
}

IAccessoire* AccessoireFactory::createRandomAccessoire() {
    // Choisie un type d'accessoire aléatoire
    int type = rand() % 3;
    switch (type) {
        case 0: return createNageoires();
        case 1: return createCarapace();
        case 2: return createCamouflage();
        default: return createNageoires();
    }
}