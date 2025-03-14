// Peureuse.cpp
#include "Peureuse.h"
#include "IBestiole.h"
#include "Milieu.h"
#include <cmath>

Peureuse::Peureuse(int seuil, double facteur) : 
    seuilPeur(seuil), facteurAcceleration(facteur)
{
}

double Peureuse::calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const
{
    // Obtenir les bestioles voisines
    std::vector<const IBestiole*> voisines = m.detecteBestiolesVoisines(b);
    
    // Si le nombre de voisines dépasse le seuil, fuir
    if (voisines.size() >= seuilPeur) {
        // Calculer la direction opposée au centre de masse des voisines
        double sommeX = 0.0;
        double sommeY = 0.0;
        
        for (const auto& voisine : voisines) {
            auto pos = voisine->getPosition();
            sommeX += pos.first;
            sommeY += pos.second;
        }
        
        double centreX = sommeX / voisines.size();
        double centreY = sommeY / voisines.size();
        
        // Position de la bestiole
        auto pos = b.getPosition();
        double dx = pos.first - centreX;
        double dy = pos.second - centreY;
        
        // Calculer la nouvelle orientation (direction opposée)
        return atan2(-dy, dx);
    }
    
    // Sinon, garder la même orientation
    return b.getOrientation();
}

IComportement* Peureuse::clone() const
{
    return new Peureuse(seuilPeur, facteurAcceleration);
}

