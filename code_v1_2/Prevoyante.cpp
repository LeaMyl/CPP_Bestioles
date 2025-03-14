// Prevoyante.cpp
#include "Prevoyante.h"
#include "IBestiole.h"
#include "Milieu.h"
#include <cmath>
#include <limits>

double Prevoyante::calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const
{
    // Obtenir les bestioles voisines
    std::vector<const IBestiole*> voisines = m.detecteBestiolesVoisines(b);
    
    if (voisines.empty()) {
        return b.getOrientation(); // Garder la même orientation s'il n'y a pas de voisins
    }
    
    // Prédire la position future des voisines
    // et éviter les collisions potentielles
    auto posB = b.getPosition();
    double orientB = b.getOrientation();
    double vitesseB = b.getVitesse();
    
    // Calculer la future position de la bestiole
    double futurX = posB.first + cos(orientB) * vitesseB * 5; // Prédiction sur 5 pas de temps
    double futurY = posB.second - sin(orientB) * vitesseB * 5;
    
    // Vérifier les collisions potentielles
    bool collisionPotentielle = false;
    double directionEvitement = 0.0;
    
    for (const auto& voisine : voisines) {
        auto posV = voisine->getPosition();
        double orientV = voisine->getOrientation();
        double vitesseV = voisine->getVitesse();
        
        // Calculer la future position de la voisine
        double futurXV = posV.first + cos(orientV) * vitesseV * 5;
        double futurYV = posV.second - sin(orientV) * vitesseV * 5;
        
        // Calculer la distance future
        double dx = futurXV - futurX;
        double dy = futurYV - futurY;
        double distanceFuture = std::sqrt(dx*dx + dy*dy);
        
        // Si une collision est prévue
        if (distanceFuture < 15.0) { // Seuil de collision
            collisionPotentielle = true;
            directionEvitement = atan2(-dy, dx) + M_PI; // Direction opposée
            break;
        }
    }
    
    if (collisionPotentielle) {
        return directionEvitement;
    }
    
    return b.getOrientation();
}

IComportement* Prevoyante::clone() const
{
    return new Prevoyante();
}
