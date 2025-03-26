#include "AccessoireFactory.h"
#include <cstdlib>
#include <ctime>

// Initialisation de l'instance statique du singleton
AccessoireFactory* AccessoireFactory::instance = nullptr;

// Constructeur privé : initialisation de la configuration et de la graine aléatoire
AccessoireFactory::AccessoireFactory() {
    // Charger la configuration par défaut de Configuration.h
    MAX_NU = Configuration::MAX_NU;
    MAX_OMEGA = Configuration::MAX_OMEGA;      
    MAX_ETA = Configuration::MAX_ETA;    
    MAX_PSI = Configuration::MAX_PSI;
    MIN_PSI = Configuration::MIN_PSI;  
    TAUX_ACCESSOIRES = Configuration::TAUX_ACCESSOIRES;
    
    // Générer une graine aléatoire pour une génération plus variée
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// Méthode d'accès au singleton
AccessoireFactory* AccessoireFactory::getInstance() {
    if (instance == nullptr) {
        instance = new AccessoireFactory();
    }
    return instance;
}

// Destructeur (vide car pas de mémoire dynamique à libérer)
AccessoireFactory::~AccessoireFactory() {
    // Pas de nettoyage explicite nécessaire
}

// Modificateur de configuration avec validation des entrées
void AccessoireFactory::setConfig(double _MAX_NU, double _MAX_OMEGA, 
                                  double _MAX_ETA, double _MIN_PSI, 
                                  double _MAX_PSI) {
    // Assurer que les valeurs sont dans des plages raisonnables
    MAX_NU = _MAX_NU > 1.0 ? _MAX_NU : 1.0;
    MAX_OMEGA = _MAX_OMEGA > 1.0 ? _MAX_OMEGA : 1.0;
    MAX_ETA = _MAX_ETA > 1.0 ? _MAX_ETA : 1.0;
    
    // Valider les valeurs de la plage psi
    MIN_PSI = _MIN_PSI < 0.0 ? 0.0 : (_MIN_PSI > 1.0 ? 1.0 : _MIN_PSI);  
    MAX_PSI = _MAX_PSI < MIN_PSI ? MIN_PSI : (_MAX_PSI > 1.0 ? 1.0 : _MAX_PSI); 
}

// Créer des nageoires avec un coefficient de vitesse aléatoire
IAccessoire* AccessoireFactory::createNageoires() {
    // Générer un coefficient aléatoire entre 1.0 et MAX_NU
    double coeff = 1.0 + static_cast<double>(rand()) / RAND_MAX * (MAX_NU - 1.0);
    return new Nageoires(coeff);
}

// Créer une carapace avec résistance et réduction aléatoires
IAccessoire* AccessoireFactory::createCarapace() {
    // Résistance aléatoire entre 1.0 et MAX_OMEGA
    double resistance = 1.0 + static_cast<double>(rand()) / RAND_MAX * (MAX_OMEGA - 1.0);
    
    // Réduction aléatoire entre 1.0 et MAX_ETA
    double reduction = 1.0 + static_cast<double>(rand()) / RAND_MAX * (MAX_ETA - 1.0);
    
    return new Carapace(resistance, reduction);
}

// Créer un camouflage avec coefficient aléatoire
IAccessoire* AccessoireFactory::createCamouflage() {
    // Coefficient de camouflage aléatoire entre MIN_PSI et MAX_PSI
    double coeff = MIN_PSI + static_cast<double>(rand()) / RAND_MAX * (MAX_PSI - MIN_PSI);
    return new Camouflage(coeff);
}

// Créer un accessoire complètement aléatoire
IAccessoire* AccessoireFactory::createRandomAccessoire() {
    // Choisir aléatoirement un type d'accessoire
    int type = rand() % 3;
    switch (type) {
        case 0: return createNageoires();
        case 1: return createCarapace();
        case 2: return createCamouflage();
        default: return createNageoires(); // Repli pour éviter des problèmes potentiels
    }
}