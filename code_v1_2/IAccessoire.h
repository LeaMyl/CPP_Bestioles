#ifndef _IACCESSOIRE_H_
#define _IACCESSOIRE_H_

// Interface définissant les caractéristiques des accessoires pour les bestioles
class IAccessoire {
public:
    // Destructeur virtuel pour permettre une destruction sécurisée des dérivés
    virtual ~IAccessoire() {}
    
    // Modifie la vitesse de la bestiole
    // @param vitesse Vitesse initiale
    // @return Vitesse modifiée
    virtual double modulerVitesse(double vitesse) const = 0;
    
    // Modifie la probabilité de mort lors des collisions
    // @param proba Probabilité initiale
    // @return Probabilité modifiée
    virtual double modulerResistance(double proba) const = 0;
    
    // Obtient le coefficient de camouflage
    // @return Coefficient entre 0 (pas camouflé) et 1 (parfaitement camouflé)
    virtual double getCoeffCamoufflage() const = 0;
    
    // Méthode de clonage pour le patron de conception Prototype
    virtual IAccessoire* clone() const = 0;
    
    // Obtient le type d'accessoire pour représentation visuelle
    virtual int getType() const = 0;
};

#endif