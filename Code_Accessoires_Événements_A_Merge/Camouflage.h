#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "IAccessoire.h"

class Camouflage : public IAccessoire {
private:
    double indiceCamoufflage; // Camouflage coefficient ψ ∈ [ψmin; ψmax]

public:
    Camouflage(double indice = 0.5);
    virtual ~Camouflage();
    
    // No effect on speed
    virtual double modulerVitesse(double vitesse) const override;
    
    // No effect on resistance
    virtual double modulerResistance(double proba) const override;
    
    // Provide camouflage coefficient
    virtual double getCoeffCamoufflage() const override;
    
    // Clone for prototype pattern
    virtual IAccessoire* clone() const override;
    
    // Type identifier for visual representation
    virtual int getType() const override;
    
    // Specific getters/setters
    double getIndiceCamoufflage() const;
    void setIndiceCamoufflage(double indice);
};

#endif