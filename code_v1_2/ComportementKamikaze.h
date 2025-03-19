#ifndef COMPORTEMENTKAMIKAZE_H
#define COMPORTEMENTKAMIKAZE_H

#include "IComportement.h"

// Classe ComportementKamikaze implémentant IComportement
class ComportementKamikaze : public IComportement {
public:
    // Constructeur par défaut
    ComportementKamikaze();

    // Destructeur
    ~ComportementKamikaze() override;

    // Implémentation de la méthode calculerNouvelleDirection
    double calculerNouvelleDirection(const BestioleTestComp& bestiole, const MilieuTestComp& milieu) override;

    // Implémentation de la méthode getCouleur
    std::array<int, 3> getCouleur() const override;

    // Implémentation de la méthode clone
    IComportement* clone() const override;

private:
    // Méthode pour trouver la bestiole la plus proche
    const IBestiole* trouverBestioleLaPlusProche(const BestioleTestComp& bestiole, const MilieuTestComp& milieu) const;
};

#endif // COMPORTEMENTKAMIKAZE_H