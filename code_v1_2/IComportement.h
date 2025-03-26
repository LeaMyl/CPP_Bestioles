#ifndef ICOMPORTEMENT_H
#define ICOMPORTEMENT_H

#include <array>

// Déclarations anticipées pour éviter les inclusions circulaires
class Bestiole;
class Milieu;

// Interface définissant le comportement des bestioles
class IComportement {
public:
    // Calcule la nouvelle direction de déplacement de la bestiole
    // @param bestiole La bestiole dont on calcule la direction
    // @param milieu L'environnement dans lequel la bestiole évolue
    // @return L'angle de la nouvelle direction
    virtual double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) = 0;

    // Obtient la couleur associée au comportement
    // @return Un tableau RGB représentant la couleur
    virtual std::array<int, 3> getCouleur() const = 0;

    // Méthode de clonage pour le patron de conception Prototype
    virtual IComportement* clone() const = 0;

    // Destructeur virtuel pour une destruction sécurisée des dérivés
    virtual ~IComportement() = default;
};

#endif