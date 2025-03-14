// Oreilles.cpp
#include "Oreilles.h"
#include "IBestiole.h"
#include <cmath>

Oreilles::Oreilles(double dist, double capacite) : 
    distance(dist), capaciteDetection(capacite)
{
}

bool Oreilles::detecte(const IBestiole & moi, const IBestiole & autre) const
{
    // Récupération des positions
    auto positionMoi = moi.getPosition();
    auto positionAutre = autre.getPosition();
    
    // Calcul de la distance
    double dx = positionAutre.first - positionMoi.first;
    double dy = positionAutre.second - positionMoi.second;
    double distanceCalc = std::sqrt(dx*dx + dy*dy);
    
    // Vérification de la distance
    if (distanceCalc > distance) {
        return false;
    }
    
    // Prise en compte de la capacité de détection
    double proba = static_cast<double>(rand()) / RAND_MAX;
    return proba <= capaciteDetection;
}

ICapteur* Oreilles::clone() const
{
    return new Oreilles(distance, capaciteDetection);
}