#include "Nageoires.h"

// Type identifiers for visual representation
enum AccessoireType { NAGEOIRES = 1, CARAPACE = 2, CAMOUFLAGE = 3 };

Nageoires::Nageoires(double coeff) : coeffVitesse(coeff) {
}

Nageoires::~Nageoires() {
}

double Nageoires::modulerVitesse(double vitesse) const {
    // Increase speed by applying the multiplier
    return vitesse * coeffVitesse;
}

double Nageoires::modulerResistance(double proba) const {
    // No effect on collision resistance
    return proba;
}

double Nageoires::getCoeffCamoufflage() const {
    // No camouflage effect (0 = not camouflaged)
    return 0.0;
}

IAccessoire* Nageoires::clone() const {
    return new Nageoires(*this);
}

int Nageoires::getType() const {
    return NAGEOIRES;
}

double Nageoires::getCoeffVitesse() const {
    return coeffVitesse;
}

void Nageoires::setCoeffVitesse(double coeff) {
    // Ensure coefficient is at least 1
    if (coeff < 1.0) coeff = 1.0;
    coeffVitesse = coeff;
}