// Carapace.cpp
#include "Carapace.h"

Carapace::Carapace(double resistance, double reduction) : 
    facteurResistance(resistance), facteurReduction(reduction)
{
}

double Carapace::modulerVitesse(double vitesse) const
{
    return vitesse * facteurReduction;
}

double Carapace::modulerResistance(double proba) const
{
    return proba * facteurResistance;
}

double Carapace::getCoeffCamoufflage() const
{
    return 1.0; // Pas d'effet sur le camouflage
}

IAccessoire* Carapace::clone() const
{
    return new Carapace(facteurResistance, facteurReduction);
}