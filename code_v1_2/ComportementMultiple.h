// ComportementMultiple.h
#ifndef COMPORTEMENTMULTIPLE_H
#define COMPORTEMENTMULTIPLE_H

#include "IComportement.h"
#include <vector>
#include <memory>

// Classe ComportementMultiple implémentant IComportement
class ComportementMultiple : public IComportement {
public:
    // Constructeur par défaut
    ComportementMultiple();

    // Destructeur
    ~ComportementMultiple() override;

    // Implémentation de la méthode calculerNouvelleDirection
    double calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) override;

    // Implémentation de la méthode getCouleur
    std::array<int, 3> getCouleur() const override;

    // Implémentation de la méthode clone
    IComportement* clone() const override;

private:
    // Liste des comportements disponibles
    std::vector<std::unique_ptr<IComportement>> comportementsDisponibles;
    
    // Index du comportement actuel
    mutable int comportementActuel;
    
    // Compteur pour changer de comportement
    mutable int compteurChangement;
    
    // Durée maximale d'un comportement
    const int DUREE_MAX_COMPORTEMENT = 100;
    
    // Initialiser les comportements disponibles
    void initialiserComportements();
    
    // Changer de comportement aléatoirement
    void changerComportement() const;
};

#endif // COMPORTEMENTMULTIPLE_H