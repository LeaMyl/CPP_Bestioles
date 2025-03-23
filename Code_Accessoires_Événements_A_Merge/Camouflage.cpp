#include "Camouflage.h"
#include <algorithm> // For std::clamp

// Type identifiers for visual representation
enum AccessoireType { NAGEOIRES = 1, CARAPACE = 2, CAMOUFLAGE = 3 };

Camouflage::Camouflage(double indice) 
    : indiceCamoufflage(indice) {
    // Ensure the camouflage index is between 0 and 1
    if (indiceCamoufflage < 0.0) indiceCamoufflage = 0.0;
    if (indiceCamoufflage > 1.0) indiceCamoufflage = 1.0;
}

Camouflage::~Camouflage() {
}

double Camouflage::modulerVitesse(double vitesse) const {
    // No effect on speed
    return vitesse;
}

double Camouflage::modulerResistance(double proba) const {
    // No effect on collision resistance
    return proba;
}

double Camouflage::getCoeffCamoufflage() const {
    // Return the camouflage coefficient
    return indiceCamoufflage;
}

IAccessoire* Camouflage::clone() const {
    return new Camouflage(*this);
}

int Camouflage::getType() const {
    return CAMOUFLAGE;
}

double Camouflage::getIndiceCamoufflage() const {
    return indiceCamoufflage;
}

void Camouflage::setIndiceCamoufflage(double indice) {
    // Ensure the camouflage index is between 0 and 1
    if (indice < 0.0) indice = 0.0;
    if (indice > 1.0) indice = 1.0;
    indiceCamoufflage = indice;
}