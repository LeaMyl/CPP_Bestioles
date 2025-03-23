#include "Carapace.h"

// Type identifiers for visual representation
enum AccessoireType { NAGEOIRES = 1, CARAPACE = 2, CAMOUFLAGE = 3 };

Carapace::Carapace(double resistance, double reduction) 
    : coeffResistance(resistance), coeffReduction(reduction) {
}

Carapace::~Carapace() {
}

double Carapace::modulerVitesse(double vitesse) const {
    // Reduce speed by applying the reduction coefficient
    return vitesse / coeffReduction;
}

double Carapace::modulerResistance(double proba) const {
    // Reduce death probability by dividing by the resistance coefficient
    return proba / coeffResistance;
}

double Carapace::getCoeffCamoufflage() const {
    // No camouflage effect (0 = not camouflaged)
    return 0.0;
}

IAccessoire* Carapace::clone() const {
    return new Carapace(*this);
}

int Carapace::getType() const {
    return CARAPACE;
}

double Carapace::getCoeffResistance() const {
    return coeffResistance;
}

void Carapace::setCoeffResistance(double coeff) {
    // Ensure coefficient is at least 1
    if (coeff < 1.0) coeff = 1.0;
    coeffResistance = coeff;
}

double Carapace::getCoeffReduction() const {
    return coeffReduction;
}

void Carapace::setCoeffReduction(double coeff) {
    // Ensure coefficient is at least 1
    if (coeff < 1.0) coeff = 1.0;
    coeffReduction = coeff;
}