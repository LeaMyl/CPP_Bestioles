#include "ComportementGregaire.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <cmath>
#include <vector>

// Constructeur par défaut
ComportementGregaire::ComportementGregaire() {
    std::cout << "Constructeur de comportement grégaire" << std::endl;
}

// Destructeur
ComportementGregaire::~ComportementGregaire() {
    std::cout << "Destructeur de comportement grégaire" << std::endl;
}

// Calculer la nouvelle direction basée sur le comportement grégaire
// Alignement de direction avec les bestioles voisines
double ComportementGregaire::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    // Détecter les bestioles voisines
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    
    // Si aucune bestiole voisine, conserver la direction actuelle
    if (voisines.empty()) {
        return bestiole.getOrientation();
    }
    
    // Calculer la direction moyenne des voisines
    double directionMoyenne = 0.0;
    for (const auto& voisine : voisines) {
        directionMoyenne += voisine->getOrientation();
    }
    directionMoyenne /= voisines.size();
    
    return directionMoyenne;
}

// Retourne la couleur associée au comportement grégaire (bleu)
std::array<int, 3> ComportementGregaire::getCouleur() const {
    return {0, 0, 255}; // Bleu
}

// Créer un clone du comportement
IComportement* ComportementGregaire::clone() const {
    return new ComportementGregaire(*this);
}