#ifndef COMPORTEMENTMULTIPLE_H
#define COMPORTEMENTMULTIPLE_H

#include "IComportement.h"
#include <vector>
#include <memory>

// Comportement Multiple : change dynamiquement de comportement
class ComportementMultiple : public IComportement {
public:
    // Constructeur et destructeur
    ComportementMultiple();
    ~ComportementMultiple() override;

    // Calcule la nouvelle direction selon le comportement courant
    double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) override;

    // Retourne la couleur associée au comportement courant
    std::array<int, 3> getCouleur() const override;

    // Clone le comportement courant
    IComportement* clone() const override;

private:
    // Liste des comportements disponibles
    std::vector<std::unique_ptr<IComportement>> comportementsDisponibles;
    
    // Gestion dynamique du changement de comportement
    mutable int comportementActuel;
    mutable int compteurChangement;
    const int DUREE_MAX_COMPORTEMENT = 100;
    
    // Méthodes internes
    void initialiserComportements();
    void changerComportement() const;
};

#endif