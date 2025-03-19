#include "ComportementPeureux.h"
#include "BestioleTestComp.h"
#include "MilieuTestComp.h"
#include <cmath>
#include <vector>

// Constructeur par défaut
ComportementPeureux::ComportementPeureux() : enTrainDeFuir(false), dureeFuite(0) {
    // Initialisation des attributs si nécessaire
    std::cout << "Constructeur ComportementPeureux" << std::endl;
}

// Destructeur
ComportementPeureux::~ComportementPeureux() {
    // Libération des ressources si nécessaire
    std::cout << "Destructeur ComportementPeureux" << std::endl;
}

// Implémentation de calculerNouvelleDirection
double ComportementPeureux::calculerNouvelleDirection(const BestioleTestComp& bestiole, const MilieuTestComp& milieu) {
    if (enTrainDeFuir) {
        dureeFuite--;
        if (dureeFuite <= 0) {
            enTrainDeFuir = false;
            bestiole.setVitesse(bestiole.getVitesse() / 2);
        }
        return bestiole.getOrientation();
    }

    if (doitFuir(bestiole, milieu)) {
        enTrainDeFuir = true;
        dureeFuite = 50;
        bestiole.setVitesse(bestiole.getVitesse() * 2);
        return calculerDirectionFuite(bestiole, milieu);
    }

    return bestiole.getOrientation();
}

// Implémentation de getCouleur
std::array<int, 3> ComportementPeureux::getCouleur() const {
    return {255, 0, 0}; // Couleur rouge pour le comportement peureux
}

// Implémentation de clone
IComportement* ComportementPeureux::clone() const {
    return new ComportementPeureux(*this);
}

// Méthode pour vérifier si la bestiole doit fuir
bool ComportementPeureux::doitFuir(const BestioleTestComp& bestiole, const MilieuTestComp& milieu) const {
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    return voisines.size() > 5;
}

// Méthode pour calculer la direction de fuite
double ComportementPeureux::calculerDirectionFuite(const BestioleTestComp& bestiole, const MilieuTestComp& milieu) const {
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    double directionMoyenne = 0.0;
    for (const auto& voisine : voisines) {
        directionMoyenne += voisine->getOrientation();
    }
    directionMoyenne /= voisines.size();
    return directionMoyenne + M_PI;
}