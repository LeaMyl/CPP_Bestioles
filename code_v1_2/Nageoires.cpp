// Nageoires.cpp
#include "Nageoires.h"

Nageoires::Nageoires(double facteur) : facteurVitesse(facteur)
{
}

double Nageoires::modulerVitesse(double vitesse) const
{
    return vitesse * facteurVitesse;
}

double Nageoires::modulerResistance(double proba) const
{
    return proba; // Pas d'effet sur la résistance
}

double Nageoires::getCoeffCamoufflage() const
{
    return 1.0; // Pas d'effet sur le camouflage
}

IAccessoire* Nageoires::clone() const
{
    return new Nageoires(facteurVitesse);
}