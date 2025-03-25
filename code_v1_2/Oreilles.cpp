#include "Oreilles.h"
#include "IBestiole.h"
#include "IAccessoire.h"
#include <cmath>
#include <iostream>

Oreilles::Oreilles(double d , double c)
    : dist(d), capa(c) {
        std::cout<< "Constructeur Oreilles"<<std::endl;
    }

bool Oreilles::detecte(const IBestiole& moi, const IBestiole& autre) const {
    // Calcul de la distance entre les deux bestioles
    auto posMoi = moi.getPosition();
    auto posAutre = autre.getPosition();
    double dx = posAutre.first - posMoi.first;
    double dy = posAutre.second - posMoi.second;
    double distance = std::sqrt(dx * dx + dy * dy);

    // Vérification si l'autre bestiole est dans la plage d'écoute
    if (distance <= dist) {
        
        double probabilite_Camoufflage_bestiole = 0; // Probabilité de Camouflage de autre
    
        for (const auto& accessoire : autre.getAccessoires()) {
            //Normalement, seule l'accessoire camoufflage à probabilite_Camoufflage_bestiole different de 0
            probabilite_Camoufflage_bestiole = accessoire->getCoeffCamoufflage();
        }
        return (probabilite_Camoufflage_bestiole <= capa);
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
