// Kamikaze.cpp
#include "Kamikaze.h"
#include "IBestiole.h"
#include "Milieu.h"
#include <cmath>
#include <limits>

double Kamikaze::calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const
{
    // Obtenir les bestioles voisines
    std::vector<const IBestiole*> voisines = m.detecteBestiolesVoisines(b);
    
    if (voisines.empty()) {
        return b.getOrientation(); // Garder la même orientation s'il n'y a pas de voisins
    }
    
    // Trouver la bestiole la plus proche
    const IBestiole* cible = nullptr;
    double distanceMin = std::numeric_limits<double>::max();
    
    auto posB = b.getPosition();
    
    for (const auto& voisine : voisines) {
        auto posV = voisine->getPosition();
        double dx = posV.first - posB.first;
        double dy = posV.second - posB.second;
        double distance = std::sqrt(dx*dx + dy*dy);
        
        if (distance < distanceMin) {
            distanceMin = distance;
            cible = voisine;
        }
    }
    
    // Se diriger vers la cible
    auto posCible = cible->getPosition();
    double dx = posCible.first - posB.first;
    double dy = posCible.second - posB.second;
    
    return atan2(-dy, dx);
}

IComportement* Kamikaze::clone() const
{
    return new Kamikaze();
}

