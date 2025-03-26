#ifndef _CARAPACE_H_
#define _CARAPACE_H_

#include "IAccessoire.h"

/**
 * @class Carapace
 * @brief Représente un accessoire de protection pour une créature
 * 
 * La Carapace modifie la vitesse et la résistance aux collisions d'une créature.
 * Elle réduit la vitesse et augmente la probabilité de survie.
 */
class Carapace : public IAccessoire {
private:
    double coeffResistance; // Coefficient de résistance ω ∈ [1; ωmax]
    double coeffReduction;  // Coefficient de réduction de vitesse η ∈ [1; ηmax]

public:
    // Constructeur avec valeurs par défaut de résistance et réduction
    Carapace(double resistance = 1.5, double reduction = 1.3);
    
    // Destructeur
    virtual ~Carapace();
    
    // Modifier la vitesse en fonction des caractéristiques de la carapace
    virtual double modulerVitesse(double vitesse) const override;
    
    // Modifier la probabilité de collision
    virtual double modulerResistance(double proba) const override;
    
    // Aucun effet de camouflage
    virtual double getCoeffCamoufflage() const override;
    
    // Créer une copie profonde de la carapace
    virtual IAccessoire* clone() const override;
    
    // Identifier le type d'accessoire pour la visualisation
    virtual int getType() const override;
    
    // Accesseurs et modificateurs des coefficients de carapace
    double getCoeffResistance() const;
    void setCoeffResistance(double coeff);
    
    double getCoeffReduction() const;
    void setCoeffReduction(double coeff);
};

#endif // _CARAPACE_H_