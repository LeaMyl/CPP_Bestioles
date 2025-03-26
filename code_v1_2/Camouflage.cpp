#include "Camouflage.h"
#include <algorithm> // Pour une utilisation potentielle de std::clamp

// Énumération des types d'accessoires (cohérente entre les implémentations)
enum AccessoireType { NAGEOIRES = 1, CARAPACE = 2, CAMOUFLAGE = 3 };

// Constructeur avec validation de l'indice de camouflage
Camouflage::Camouflage(double indice) 
    : indiceCamoufflage(indice) {
    // Garantir que l'indice de camouflage est entre 0 et 1
    indiceCamoufflage = std::max(0.0, std::min(indice, 1.0));
}

// Destructeur (vide car pas de gestion de mémoire dynamique)
Camouflage::~Camouflage() {
}

// Aucune modification de vitesse
double Camouflage::modulerVitesse(double vitesse) const {
    return vitesse;
}

// Aucune modification de résistance
double Camouflage::modulerResistance(double proba) const {
    return proba;
}

// Retourne le coefficient de camouflage
double Camouflage::getCoeffCamoufflage() const {
    return indiceCamoufflage;
}

// Créer une copie profonde du camouflage
IAccessoire* Camouflage::clone() const {
    return new Camouflage(*this);
}

// Identifier le type d'accessoire pour la visualisation
int Camouflage::getType() const {
    return CAMOUFLAGE;
}

// Accesseur de l'indice de camouflage
double Camouflage::getIndiceCamoufflage() const {
    return indiceCamoufflage;
}

// Modificateur de l'indice de camouflage avec validation
void Camouflage::setIndiceCamoufflage(double indice) {
    // Garantir que l'indice de camouflage est entre 0 et 1
    indiceCamoufflage = std::max(0.0, std::min(indice, 1.0));
}