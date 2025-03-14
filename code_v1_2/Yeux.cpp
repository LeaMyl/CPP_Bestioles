// Yeux.cpp
#include "Yeux.h"
#include "IBestiole.h"
#include <cmath>

Yeux::Yeux(double champAng, double dist, double capacite) : 
    champAngulaire(champAng), distance(dist), capaciteDetection(capacite)
{
}

bool Yeux::detecte(const IBestiole & moi, const IBestiole & autre) const
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
    
    // Calcul de l'angle
    double angleVers = std::atan2(-dy, dx); // Angle vers l'autre bestiole
    double orientationMoi = moi.getOrientation();
    
    // Normalisation de l'angle entre -π et π
    double diffAngle = angleVers - orientationMoi;
    while (diffAngle > M_PI) diffAngle -= 2 * M_PI;
    while (diffAngle < -M_PI) diffAngle += 2 * M_PI;
    diffAngle = std::abs(diffAngle);
    
    // Vérification de l'angle
    if (diffAngle > champAngulaire / 2) {
        return false;
    }
    
    // Prise en compte de la capacité de détection
    double proba = static_cast<double>(rand()) / RAND_MAX;
    return proba <= capaciteDetection;
}

ICapteur* Yeux::clone() const
{
    return new Yeux(champAngulaire, distance, capaciteDetection);
}
