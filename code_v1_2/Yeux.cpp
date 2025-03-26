#include "Yeux.h"
#include "IBestiole.h"
#include "IAccessoire.h"
#include <cmath>
#include <iostream>

// Constructeur avec initialisation des paramètres de vision
Yeux::Yeux(double a, double d, double c)
    : angle(a), dist(d), capa(c) {
    // std::cout << "Constructeur Yeux" << std::endl;
}

// Méthode de détection d'une autre bestiole
bool Yeux::detecte(const IBestiole& moi, const IBestiole& autre) const {
    // Calcul de la distance entre les bestioles
    auto posMoi = moi.getPosition();
    auto posAutre = autre.getPosition();
    double dx = posAutre.first - posMoi.first;
    double dy = posAutre.second - posMoi.second;
    double distance = std::sqrt(dx * dx + dy * dy);

    // Calcul de l'angle entre les bestioles
    double angle_dif = std::atan2(dy, dx);
    if (angle_dif < 0) {
        angle_dif += 2 * M_PI;
    }

    // Vérification dans le champ de vision
    if (angle >= angle_dif && dist >= distance) {
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
ICapteur* Yeux::clone() const {
    return new Yeux(*this);
}

// Destructeur
Yeux::~Yeux() {
    // std::cout << "Destructeur de Yeux appelé" << std::endl;
}