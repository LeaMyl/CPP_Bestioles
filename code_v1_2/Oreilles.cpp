#include "Oreilles.h"
#include "IBestiole.h"
#include "IAccessoire.h"
#include <cmath>
#include <iostream>

// Constructeur avec initialisation des paramètres auditifs
Oreilles::Oreilles(double d, double c)
    : dist(d), capa(c) {
    std::cout << "Constructeur Oreilles" << std::endl;
}

// Méthode de détection auditive
bool Oreilles::detecte(const IBestiole& moi, const IBestiole& autre) const {
    // Calcul de la distance entre les bestioles
    auto posMoi = moi.getPosition();
    auto posAutre = autre.getPosition();
    double dx = posAutre.first - posMoi.first;
    double dy = posAutre.second - posMoi.second;
    double distance = std::sqrt(dx * dx + dy * dy);

    // Vérification dans la plage de détection
    if (distance <= dist) {
        double probabilite_Camoufflage_bestiole = 0;
    
        // Récupération du coefficient de camouflage
        for (const auto& accessoire : autre.getAccessoires()) {
            probabilite_Camoufflage_bestiole = accessoire->getCoeffCamoufflage();
        }
        return (probabilite_Camoufflage_bestiole <= capa);
    }
    return false;
}

// Clonage du capteur
ICapteur* Oreilles::clone() const {
    return new Oreilles(*this);
}

// Destructeur
Oreilles::~Oreilles() {
    std::cout << "Destructeur de Oreilles appelé" << std::endl;
}