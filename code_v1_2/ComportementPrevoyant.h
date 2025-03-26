#ifndef COMPORTEMENTPREVOYANT_H
#define COMPORTEMENTPREVOYANT_H

#include "IComportement.h"
#include "IBestiole.h"

// Comportement Prévoyant : la bestiole anticipe les collisions
class ComportementPrevoyant : public IComportement {
public:
    // Constructeur et destructeur
    ComportementPrevoyant();
    ~ComportementPrevoyant() override;

    // Calcule la nouvelle direction en évitant les collisions potentielles
    double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) override;

    // Retourne la couleur associée à ce comportement
    std::array<int, 3> getCouleur() const override;

    // Clone le comportement courant
    IComportement* clone() const override;

private:
    // Méthode interne de détection des collisions
    bool detecterCollisionPotentielle(const Bestiole& bestiole, const IBestiole& autre, 
                                     double& tempsCollision, double& angleEvitement) const;
};

#endif