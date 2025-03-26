#include "Nageoires.h"

// Types d'accessoires pour représentation visuelle
enum AccessoireType { NAGEOIRES = 1, CARAPACE = 2, CAMOUFLAGE = 3 };

Nageoires::Nageoires(double coeff) : coeffVitesse(coeff) {
}

// Destructeur de classes
Nageoires::~Nageoires() {
}

// Augmentation de la vitesse en appliquant le multiplicateur
double Nageoires::modulerVitesse(double vitesse) const {
    return vitesse * coeffVitesse;
}

// Aucun effet sur la résistance aux collisions
double Nageoires::modulerResistance(double proba) const {
    return proba;
}

// Aucun effet de camouflage
double Nageoires::getCoeffCamoufflage() const {
    return 0.0;
}

// Clonage de l'accessoire
IAccessoire* Nageoires::clone() const {
    return new Nageoires(*this);
}

// Type de l'accessoire
int Nageoires::getType() const {
    return NAGEOIRES;
}

// Récupération du coefficient de vitesse
double Nageoires::getCoeffVitesse() const {
    return coeffVitesse;
}

// Définition du coefficient de vitesse (minimum 1.0)
void Nageoires::setCoeffVitesse(double coeff) {
    coeffVitesse = (coeff < 1.0) ? 1.0 : coeff;
}