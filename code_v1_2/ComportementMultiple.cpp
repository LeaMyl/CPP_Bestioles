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
ComportementMultiple::ComportementMultiple() 
    : comportementActuel(0), compteurChangement(0) {
    // std::cout << "Constructeur de comportement multiple" << std::endl;
    initialiserComportements();
}

// Destructeur
ComportementMultiple::~ComportementMultiple() {
    // std::cout << "Destructeur de comportement multiple" << std::endl;
    // Les comportements sont nettoyés automatiquement par les unique_ptr
}

// Initialiser les comportements disponibles
void ComportementMultiple::initialiserComportements() {
    // Ajouter des clones des différents comportements
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
        // Choisir un comportement différent du comportement actuel
        nouveauComportement = std::rand() % comportementsDisponibles.size();
    } while (nouveauComportement == comportementActuel);
    
    comportementActuel = nouveauComportement;
    compteurChangement = 0;
}

// Calculer la nouvelle direction avec changement de comportement
double ComportementMultiple::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    // Incrémenter le compteur de comportement
    compteurChangement++;
    
    // Changer de comportement si la durée maximale est atteinte
    if (compteurChangement >= DUREE_MAX_COMPORTEMENT) {
        changerComportement();
    }
    
    // Déléguer le calcul de direction au comportement actuel
    return comportementsDisponibles[comportementActuel]->calculerNouvelleDirection(bestiole, milieu);
}

// Retourne la couleur associée au comportement multiple (violet)
std::array<int, 3> ComportementMultiple::getCouleur() const {
    return {128, 0, 128}; // Violet
}

// Créer un clone du comportement multiple
IComportement* ComportementMultiple::clone() const {
    ComportementMultiple* copie = new ComportementMultiple();

    // Copier les valeurs de l'objet actuel
    copie->comportementActuel = this->comportementActuel;
    copie->compteurChangement = this->compteurChangement;

    // Cloner chaque comportement indépendamment
    for (const auto& comportement : this->comportementsDisponibles) {
        copie->comportementsDisponibles.push_back(
            std::unique_ptr<IComportement>(comportement->clone())
        );
    }

    return copie;
}