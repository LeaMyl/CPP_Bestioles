#include "ComportementKamikaze.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <cmath>
#include <limits>

// Constructeur par défaut
ComportementKamikaze::ComportementKamikaze() {
    // std::cout << "Constructeur de comportement kamikaze" << std::endl;
}

// Destructeur
ComportementKamikaze::~ComportementKamikaze() {
    // std::cout << "Destructeur de comportement kamikaze" << std::endl;
}

// Calculer la nouvelle direction basée sur le comportement kamikaze
double ComportementKamikaze::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    // Trouver la bestiole la plus proche
    const IBestiole* cible = trouverBestioleLaPlusProche(bestiole, milieu);

    // Si aucune cible n'est trouvée, conserver la direction actuelle
    if (cible == nullptr) {
        return bestiole.getOrientation();
    }

    // Calculer la direction vers la bestiole cible
    auto positionCible = cible->getPosition();
    double dx = positionCible.first - bestiole.getPosition().first;
    double dy = positionCible.second - bestiole.getPosition().second;

    // Calculer l'angle de direction vers la cible
    double angle = std::atan2(dy, dx);
    if (angle < 0) {
        angle += 2.0 * M_PI; // Convertir les angles négatifs en [0, 2π]
    }
    return -angle;
}

// Retourne la couleur associée au comportement kamikaze (orange)
std::array<int, 3> ComportementKamikaze::getCouleur() const {
    return {255, 165, 0}; // Orange
}

// Créer un clone du comportement
IComportement* ComportementKamikaze::clone() const {
    return new ComportementKamikaze(*this);
}

// Trouver la bestiole la plus proche
const IBestiole* ComportementKamikaze::trouverBestioleLaPlusProche(const Bestiole& bestiole, const Milieu& milieu) const {
    const IBestiole* cible = nullptr;
    double distanceMin = std::numeric_limits<double>::max();
    
    // Détecter les bestioles voisines
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    
    // Parcourir les voisines pour trouver la plus proche
    for (const auto& autre : voisines) {
        if (&bestiole != autre) { // Éviter de se comparer à soi-même
            double dx = autre->getPosition().first - bestiole.getPosition().first;
            double dy = autre->getPosition().second - bestiole.getPosition().second;
            double distance = std::sqrt(dx * dx + dy * dy);

            // Mettre à jour la cible si une distance plus courte est trouvée
            if (distance < distanceMin) {
                distanceMin = distance;
                cible = autre;
            }
        }
    }

    return cible;
}