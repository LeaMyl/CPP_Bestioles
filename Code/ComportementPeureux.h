#ifndef COMPORTEMENTPEUREUX_H
#define COMPORTEMENTPEUREUX_H

#include "IComportement.h"

// Comportement Peureux : la bestiole fuit les autres bestioles
class ComportementPeureux : public IComportement {
public:
    // Constructeur et destructeur
    ComportementPeureux();
    ~ComportementPeureux() override;

    // Calcule la direction de fuite si nécessaire
    double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) override;

    // Retourne la couleur associée à ce comportement
    std::array<int, 3> getCouleur() const override;

    // Clone le comportement courant
    IComportement* clone() const override;

private:
    // Méthodes internes de gestion du comportement
    bool doitFuir(const Bestiole& bestiole, const Milieu& milieu) const;
    double calculerDirectionFuite(const Bestiole& bestiole, const Milieu& milieu) const;
    
    // État de fuite
    mutable bool enTrainDeFuir;
    mutable int dureeFuite;
};

#endif