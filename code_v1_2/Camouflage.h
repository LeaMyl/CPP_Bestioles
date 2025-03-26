#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "IAccessoire.h"

/**
 * @class Camouflage
 * @brief Représente un accessoire de camouflage pour une créature
 * 
 * Le Camouflage fournit un coefficient de dissimulation visuelle
 * sans affecter directement la vitesse ou la résistance.
 */
class Camouflage : public IAccessoire {
private:
    double indiceCamoufflage; // Coefficient de camouflage ψ ∈ [ψmin; ψmax]

public:
    // Constructeur avec indice de camouflage par défaut
    Camouflage(double indice = 0.5);
    
    // Destructeur
    virtual ~Camouflage();
    
    // Aucune modification de vitesse
    virtual double modulerVitesse(double vitesse) const override;
    
    // Aucune modification de résistance
    virtual double modulerResistance(double proba) const override;
    
    // Retourne le coefficient de camouflage
    virtual double getCoeffCamoufflage() const override;
    
    // Créer une copie profonde du camouflage
    virtual IAccessoire* clone() const override;
    
    // Identifier le type d'accessoire pour la visualisation
    virtual int getType() const override;
    
    // Accesseurs spécifiques
    double getIndiceCamoufflage() const;
    void setIndiceCamoufflage(double indice);
};

#endif // _CAMOUFLAGE_H_