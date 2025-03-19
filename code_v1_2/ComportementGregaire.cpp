#include "ComportementGregaire.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <cmath>
#include <vector>

// Constructeur par défaut
ComportementGregaire::ComportementGregaire() {
    // Initialisation des attributs si nécessaire
    std::cout << "Constructeur ComportementGregaire" << std::endl;
}

// Destructeur
ComportementGregaire::~ComportementGregaire() {
    // Libération des ressources si nécessaire
    std::cout << "Destructeur ComportementGregaire" << std::endl;
}

// Implémentation de calculerNouvelleDirection
double ComportementGregaire::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    if (voisines.empty()) {
        return bestiole.getOrientation();
    }
    double directionMoyenne = 0.0;
    for (const auto& voisine : voisines) {
        directionMoyenne += voisine->getOrientation();
    }
    directionMoyenne /= voisines.size();
    return directionMoyenne;
}

// Implémentation de getCouleur
std::array<int, 3> ComportementGregaire::getCouleur() const {
    return {0, 0, 255}; // Couleur bleue pour le comportement grégaire
}

// Implémentation de clone
IComportement* ComportementGregaire::clone() const {
    return new ComportementGregaire(*this);
}