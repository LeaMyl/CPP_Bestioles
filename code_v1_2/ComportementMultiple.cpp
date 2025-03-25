// ComportementMultiple.cpp
#include "ComportementMultiple.h"
#include "Bestiole.h"
#include "Milieu.h"
#include "ComportementGregaire.h"
#include "ComportementPeureux.h"
#include "ComportementKamikaze.h"
#include "ComportementPrevoyant.h"
#include <cmath>
#include <random>
#include <ctime>

// Constructeur par défaut
ComportementMultiple::ComportementMultiple() : comportementActuel(0), compteurChangement(0) {
    std::cout << "Constructeur ComportementMultiple" << std::endl;
    initialiserComportements();
}

// Destructeur
ComportementMultiple::~ComportementMultiple() {
    std::cout << "Destructeur ComportementMultiple" << std::endl;
    // Les comportements sont nettoyés automatiquement par les unique_ptr
}

// Initialiser les comportements disponibles
void ComportementMultiple::initialiserComportements() {
    // Ajouter des comportements clonés pour éviter de partager les instances
    comportementsDisponibles.push_back(std::unique_ptr<IComportement>(ComportementGregaire().clone()));
    comportementsDisponibles.push_back(std::unique_ptr<IComportement>(ComportementPeureux().clone()));
    comportementsDisponibles.push_back(std::unique_ptr<IComportement>(ComportementKamikaze().clone()));
    comportementsDisponibles.push_back(std::unique_ptr<IComportement>(ComportementPrevoyant().clone()));

    // Initialiser le générateur aléatoire
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Choisir un comportement initial aléatoire
    comportementActuel = std::rand() % comportementsDisponibles.size();
}

// Changer de comportement aléatoirement
void ComportementMultiple::changerComportement() const {
    int nouveauComportement;
    do {
        nouveauComportement = std::rand() % comportementsDisponibles.size();
    } while (nouveauComportement == comportementActuel);
    
    comportementActuel = nouveauComportement;
    compteurChangement = 0;
}

// Implémentation de calculerNouvelleDirection
double ComportementMultiple::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    // Incrémenter le compteur
    compteurChangement++;
    
    // Changer de comportement quand le compteur atteint la durée maximale
    if (compteurChangement >= DUREE_MAX_COMPORTEMENT) {
        changerComportement();
    }
    
    // Déléguer le calcul au comportement actuel
    return comportementsDisponibles[comportementActuel]->calculerNouvelleDirection(bestiole, milieu);
}

// Implémentation de getCouleur
std::array<int, 3> ComportementMultiple::getCouleur() const {
    return {128, 0, 128}; // Couleur violette pour le comportement multiple
}

IComportement* ComportementMultiple::clone() const {
    ComportementMultiple* copie = new ComportementMultiple();

    // Copier les valeurs de l’objet actuel
    copie->comportementActuel = this->comportementActuel;
    copie->compteurChangement = this->compteurChangement;

    // Cloner chaque comportement indépendamment
    for (const auto& comportement : this->comportementsDisponibles) {
        copie->comportementsDisponibles.push_back(
            std::unique_ptr<IComportement>(comportement->clone()) // Cloner le comportement
        );
    }

    return copie;
}