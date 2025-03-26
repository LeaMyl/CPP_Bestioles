#ifndef COMPORTEMENTGREGAIRE_H
#define COMPORTEMENTGREGAIRE_H

#include "IComportement.h"

// Comportement Grégaire : la bestiole suit le groupe
class ComportementGregaire : public IComportement {
public:
    // Constructeur et destructeur
    ComportementGregaire();
    ~ComportementGregaire() override;

    // Calcule la direction en fonction du groupe
    double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) override;

    // Retourne la couleur associée à ce comportement
    std::array<int, 3> getCouleur() const override;

    // Clone le comportement courant
    IComportement* clone() const override;
};

#endif