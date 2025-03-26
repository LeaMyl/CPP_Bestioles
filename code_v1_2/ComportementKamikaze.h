#ifndef COMPORTEMENTKAMIKAZE_H
#define COMPORTEMENTKAMIKAZE_H

#include "IComportement.h"
#include "IBestiole.h"

// Comportement Kamikaze : la bestiole cherche à se diriger vers une autre bestiole
class ComportementKamikaze : public IComportement {
public:
    // Constructeur et destructeur
    ComportementKamikaze();
    ~ComportementKamikaze() override;

    // Calcule la direction vers la bestiole la plus proche
    double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) override;

    // Retourne la couleur associée à ce comportement
    std::array<int, 3> getCouleur() const override;

    // Clone le comportement courant
    IComportement* clone() const override;

private:
    // Méthode interne pour trouver la bestiole la plus proche
    const IBestiole* trouverBestioleLaPlusProche(const Bestiole& bestiole, const Milieu& milieu) const;
};

#endif