#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_

#include "IAccessoire.h"

class Nageoires : public IAccessoire {
private:
    double coeffVitesse; // Speed multiplier coefficient ν ∈ [1; νmax]

public:
    Nageoires(double coeff = 1.5);
    virtual ~Nageoires();
    
    // Speed modifier (increase speed)
    virtual double modulerVitesse(double vitesse) const override;
    
    // No effect on resistance
    virtual double modulerResistance(double proba) const override;
    
    // No camouflage effect
    virtual double getCoeffCamoufflage() const override;
    
    // Clone for prototype pattern
    virtual IAccessoire* clone() const override;
    
    // Type identifier for visual representation
    virtual int getType() const override;
    
    // Specific getters/setters
    double getCoeffVitesse() const;
    void setCoeffVitesse(double coeff);
};

#endif