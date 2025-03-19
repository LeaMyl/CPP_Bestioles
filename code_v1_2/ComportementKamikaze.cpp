#include "ComportementKamikaze.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <cmath>
#include <limits> // Pour utiliser std::numeric_limits

// Constructeur par défaut
ComportementKamikaze::ComportementKamikaze() {
    std::cout << "Constructeur ComportementKamikaze" << std::endl;
}

// Destructeur
ComportementKamikaze::~ComportementKamikaze() {
    std::cout << "Destructeur ComportementKamikaze" << std::endl;
}

// Implémentation de calculerNouvelleDirection
double ComportementKamikaze::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    // Trouver la bestiole la plus proche
    const IBestiole* cible = trouverBestioleLaPlusProche(bestiole, milieu);

    if (cible == nullptr) {
        // Si aucune bestiole n'est trouvée, conserver la direction actuelle
        return bestiole.getOrientation();
    }

    // Calculer la direction vers la bestiole cible
    auto positionCible = cible->getPosition();
    double dx = positionCible.first - bestiole.getPosition().first;
    double dy = positionCible.second - bestiole.getPosition().second;

    // Retourner l'angle de la direction vers la cible
    return std::atan2(dy, dx);
}

// Implémentation de getCouleur
std::array<int, 3> ComportementKamikaze::getCouleur() const {
    return {255, 165, 0}; // Couleur orange pour le comportement kamikaze
}

// Implémentation de clone
IComportement* ComportementKamikaze::clone() const {
    return new ComportementKamikaze(*this);
}

// Méthode pour trouver la bestiole la plus proche
const IBestiole* ComportementKamikaze::trouverBestioleLaPlusProche(const Bestiole& bestiole, const Milieu& milieu) const {
    const IBestiole* cible = nullptr;
    double distanceMin = std::numeric_limits<double>::max(); // Initialiser avec une valeur très grande
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    for (const auto& autre : voisines) {
        if (&bestiole != autre) { // Ne pas se comparer à soi-même
            double dx = autre->getPosition().first - bestiole.getPosition().first;
            double dy = autre->getPosition().second - bestiole.getPosition().second;
            double distance = std::sqrt(dx * dx + dy * dy);

            if (distance < distanceMin) {
                distanceMin = distance;
                cible = autre;
            }
        }
    }

    return cible;
}