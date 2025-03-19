#ifndef ICOMPORTEMENT_H
#define ICOMPORTEMENT_H

#include <array>

// Déclaration anticipée de Bestiole
class Bestiole;
class Milieu;

// Interface IComportement
class IComportement {
public:
    // Méthode virtuelle pure pour calculer la nouvelle direction d'une bestiole
    virtual double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) = 0;

    // Méthode virtuelle pour obtenir la couleur associée au comportement
    virtual std::array<int, 3> getCouleur() const = 0;

    // Méthode virtuelle pour cloner le comportement (utile pour le polymorphisme)
    virtual IComportement* clone() const = 0;

    // Destructeur virtuel pour assurer une destruction propre des objets dérivés
    virtual ~IComportement() = default;
};

#endif // ICOMPORTEMENT_H