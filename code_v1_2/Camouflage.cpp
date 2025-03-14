// Camouflage.cpp
#include "Camouflage.h"

Camouflage::Camouflage(double indice) : indiceCamoufflage(indice)
{
}

double Camouflage::modulerVitesse(double vitesse) const
{
    return vitesse; // Pas d'effet sur la vitesse
}

double Camouflage::modulerResistance(double proba) const
{
    return proba; // Pas d'effet sur la résistance
}

double Camouflage::getCoeffCamoufflage() const
{
    return indiceCamoufflage;
}

IAccessoire* Camouflage::clone() const
{
    return new Camouflage(indiceCamoufflage);
}