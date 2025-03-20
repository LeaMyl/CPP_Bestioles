// ComportementPrevoyant.h
#ifndef COMPORTEMENTPREVOYANT_H
#define COMPORTEMENTPREVOYANT_H

#include "IComportement.h"
#include "IBestiole.h"

// Classe ComportementPrevoyant implémentant IComportement
class ComportementPrevoyant : public IComportement {
public:
    // Constructeur par défaut
    ComportementPrevoyant();

    // Destructeur
    ~ComportementPrevoyant() override;

    // Implémentation de la méthode calculerNouvelleDirection
    double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) override;

    // Implémentation de la méthode getCouleur
    std::array<int, 3> getCouleur() const override;

    // Implémentation de la méthode clone
    IComportement* clone() const override;

private:
    // Méthode pour prédire les collisions potentielles
    bool detecterCollisionPotentielle(const Bestiole& bestiole, const IBestiole& autre, 
                                     double& tempsCollision, double& angleEvitement) const;
};

#endif // COMPORTEMENTPREVOYANT_H