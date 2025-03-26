#include "ComportementPeureux.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <cmath>
#include <vector>

// Constructeur par défaut
ComportementPeureux::ComportementPeureux() 
    : enTrainDeFuir(false), dureeFuite(0) {
    std::cout << "Constructeur de comportement peureux" << std::endl;
}

// Destructeur
ComportementPeureux::~ComportementPeureux() {
    std::cout << "Destructeur de comportement peureux" << std::endl;
}

// Calculer la nouvelle direction basée sur le comportement peureux
double ComportementPeureux::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    // Si déjà en train de fuir
    if (enTrainDeFuir) {
        dureeFuite--;
        if (dureeFuite <= 0) {
            // Fin de la phase de fuite
            enTrainDeFuir = false;
            bestiole.setVitesse(3.);
        }
        return bestiole.getOrientation();
    }

    // Vérifier s'il faut fuir
    if (doitFuir(bestiole, milieu)) {
        enTrainDeFuir = true;
        dureeFuite = 10;

        // Augmenter progressivement la vitesse
        if (bestiole.getVitesse() < 4) {
            bestiole.setVitesse(bestiole.getVitesse() + 1);
        } else {
            bestiole.setVitesse(4);
        }

        // Calculer la direction de fuite
        return calculerDirectionFuite(bestiole, milieu);
    }

    // Conserver la direction actuelle si pas de menace
    return bestiole.getOrientation();
}

// Retourne la couleur associée au comportement peureux (rouge)
std::array<int, 3> ComportementPeureux::getCouleur() const {
    return {255, 0, 0}; // Rouge
}

// Créer un clone du comportement
IComportement* ComportementPeureux::clone() const {
    return new ComportementPeureux(*this);
}

// Déterminer si la bestiole doit fuir
bool ComportementPeureux::doitFuir(const Bestiole& bestiole, const Milieu& milieu) const {
    // Détecter les bestioles voisines
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);

    // Fuir si au moins une bestiole voisine est détectée
    return !voisines.empty();
}

// Calculer la direction de fuite
double ComportementPeureux::calculerDirectionFuite(const Bestiole& bestiole, const Milieu& milieu) const {
    // Détecter les bestioles voisines
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    
    // Calculer la direction moyenne des voisines
    double directionMoyenne = 0.0;
    for (const auto& voisine : voisines) {
        directionMoyenne += voisine->getOrientation();
    }
    directionMoyenne /= voisines.size();
    
    // Fuir dans la direction opposée
    return directionMoyenne + M_PI;
}