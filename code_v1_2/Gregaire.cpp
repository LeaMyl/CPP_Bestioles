// Gregaire.cpp
#include "Gregaire.h"
#include "IBestiole.h"
#include "Milieu.h"
#include <cmath>

double Gregaire::calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const
{
    // Obtenir les bestioles voisines
    std::vector<const IBestiole*> voisines = m.detecteBestiolesVoisines(b);
    
    if (voisines.empty()) {
        return b.getOrientation(); // Garder la même orientation s'il n'y a pas de voisins
    }
    
    // Calculer l'orientation moyenne des voisines
    double sommeX = 0.0;
    double sommeY = 0.0;
    
    for (const auto& voisine : voisines) {
        double orient = voisine->getOrientation();
        sommeX += cos(orient);
        sommeY += sin(orient);
    }
    
    // Calculer la nouvelle orientation
    if (sommeX == 0 && sommeY == 0) {
        return b.getOrientation();
    }
    
    return atan2(-sommeY, sommeX);
}

IComportement* Gregaire::clone() const
{
    return new Gregaire();
}
