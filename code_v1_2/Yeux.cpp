#include "Yeux.h"
#include "IBestiole.h"
#include "IAccessoire.h"
#include <cmath>
#include <iostream>

Yeux::Yeux(double a, double d, double c)
    : angle(a), dist(d), capa(c) {
        std::cout<<"Constructeur Yeux"<<std::endl;
    }

bool Yeux::detecte(const IBestiole& moi, const IBestiole& autre) const {
    // Calcul de la distance entre les deux bestioles
    auto posMoi = moi.getPosition();
    auto posAutre = autre.getPosition();
    double dx = posAutre.first - posMoi.first;
    double dy = posAutre.second - posMoi.second;
    double distance = std::sqrt(dx * dx + dy * dy);

    // Calcul de l'angle entre les deux bestioles
    double angle_dif = std::atan2(dy, dx);
    if (angle_dif < 0){
        angle_dif+= 2* M_PI;
    }

    // Vérification si l'autre bestiole est dans le champ de vision
    if (angle >= angle_dif &&    dist >= distance) {
        double probabilite_Camoufflage_bestiole = 0; // Probabilité de Camouflage de autre
    
        for (const auto& accessoire : autre.getAccessoires()) {
            //Normalement, seule l'accessoire camoufflage à probabilite_Camoufflage_bestiole different de 0
            probabilite_Camoufflage_bestiole = accessoire->getCoeffCamoufflage();
        }
        return (probabilite_Camoufflage_bestiole <= capa);
    }
    return false;
}

ICapteur* Yeux::clone() const {
    return new Yeux(*this);
}

Yeux::~Yeux() {
    // Pas d'allocation dynamique donc rien de spécial à libérer
    // Ajout d'un message pour vérifier quand il est appelé (optionnel)
    std::cout << "Destructeur de Yeux appelé" << std::endl;
}
