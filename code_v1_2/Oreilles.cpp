#include "Oreilles.h"
#include "IBestiole.h"
#include <cmath>
#include <iostream>

Oreilles::Oreilles(double d , double c)
    : dist(d), capa(c) {}

bool Oreilles::detecte(const IBestiole& moi, const IBestiole& autre) const {
    // Calcul de la distance entre les deux bestioles
    auto posMoi = moi.getPosition();
    auto posAutre = autre.getPosition();
    double dx = posAutre.first - posMoi.first;
    double dy = posAutre.second - posMoi.second;
    double distance = std::sqrt(dx * dx + dy * dy);

    // Vérification si l'autre bestiole est dans la plage d'écoute
    if (distance <= dist) {
        // Calcul de la capacité de détection aléatoire dans [capaMin ; capaMax]
        
        double probabilite_detection_bestiole = 1.0; // Probabilité de détection fixée à 100% pour l'exemple
        return (probabilite_detection_bestiole <= capa);
    }
    else
    {
        return false;
    }
}

ICapteur* Oreilles::clone() const {
    return new Oreilles(*this);
}

Oreilles::~Oreilles() {
    // Pas d'allocation dynamique donc rien de spécial à libérer
    // Ajout d'un message pour vérifier quand il est appelé (optionnel)
    std::cout << "Destructeur de Oreilles appelé" << std::endl;
}
