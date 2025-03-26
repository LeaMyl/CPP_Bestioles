#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

// Interface définissant les capacités de détection des capteurs
// Utilisée pour implémenter différents types de détection (yeux, oreilles)

class IBestiole;

class ICapteur 
{
public:
    // Destructeur virtuel pour permettre une destruction sécurisée des dérivés
    virtual ~ICapteur() = default;
    
    // Méthode abstraite pour détecter la présence d'une autre bestiole
    // @param moi La bestiole possédant le capteur
    // @param autre La bestiole à détecter
    // @return true si la bestiole est détectée, false sinon
    virtual bool detecte(const IBestiole & moi, const IBestiole & autre) const = 0;
    
    // Méthode de clonage pour le patron de conception Prototype
    virtual ICapteur* clone() const = 0;
};

#endif