#ifndef COMPORTEMENTPEUREUX_H
#define COMPORTEMENTPEUREUX_H

#include "IComportement.h"

// Classe ComportementPeureux implémentant IComportement
class ComportementPeureux : public IComportement {
public:
    // Constructeur par défaut
    ComportementPeureux();

    // Destructeur
    ~ComportementPeureux() override;

    // Implémentation de la méthode calculerNouvelleDirection
    double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) override;

    // Implémentation de la méthode getCouleur
    std::array<int, 3> getCouleur() const override;

    // Implémentation de la méthode clone
    IComportement* clone() const override;

private:
    // Méthode pour vérifier si la bestiole doit fuir
    bool doitFuir(const Bestiole& bestiole, const Milieu& milieu) const;

    // Méthode pour calculer la direction de fuite
    double calculerDirectionFuite(const Bestiole& bestiole, const Milieu& milieu) const;

    // Attribut pour suivre si la bestiole est en train de fuir
    mutable bool enTrainDeFuir;
    mutable int dureeFuite; // Durée de la fuite (en pas de simulation)
};

#endif // COMPORTEMENTPEUREUX_H