#ifndef COMPORTEMENTGREGAIRE_H
#define COMPORTEMENTGREGAIRE_H

#include "IComportement.h"

// Classe ComportementGregaire implémentant IComportement
class ComportementGregaire : public IComportement {
public:
    // Constructeur par défaut
    ComportementGregaire();

    // Destructeur
    ~ComportementGregaire() override;

    // Implémentation de la méthode calculerNouvelleDirection
    double calculerNouvelleDirection(const BestioleTestComp& bestiole, const MilieuTestComp& milieu) override;

    // Implémentation de la méthode getCouleur
    std::array<int, 3> getCouleur() const override;

    // Implémentation de la méthode clone
    IComportement* clone() const override;
};

#endif // COMPORTEMENTGREGAIRE_H