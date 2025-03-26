#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_

#include "IAccessoire.h"

class Nageoires : public IAccessoire {
private:
    double coeffVitesse; // Coefficient multiplicateur de vitesse

public:
    Nageoires(double coeff = 1.5);
    virtual ~Nageoires();
    
    // Modification de la vitesse (augmentation)
    virtual double modulerVitesse(double vitesse) const override;
    
    // Aucun effet sur la résistance
    virtual double modulerResistance(double proba) const override;
    
    // Aucun effet de camouflage
    virtual double getCoeffCamoufflage() const override;
    
    // Clonage pour le patron prototype
    virtual IAccessoire* clone() const override;
    
    // Identifiant de type pour représentation visuelle
    virtual int getType() const override;
    
    // Accesseurs spécifiques
    double getCoeffVitesse() const;
    void setCoeffVitesse(double coeff);
};

#endif