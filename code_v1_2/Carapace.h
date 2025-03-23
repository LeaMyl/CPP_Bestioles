#ifndef _CARAPACE_H_
#define _CARAPACE_H_

#include "IAccessoire.h"

class Carapace : public IAccessoire {
private:
    double coeffResistance; // Resistance coefficient ω ∈ [1; ωmax]
    double coeffReduction;  // Speed reduction coefficient η ∈ [1; ηmax]

public:
    Carapace(double resistance = 1.5, double reduction = 1.3);
    virtual ~Carapace();
    
    // Speed modifier (reduce speed)
    virtual double modulerVitesse(double vitesse) const override;
    
    // Resistance modifier (reduce death probability)
    virtual double modulerResistance(double proba) const override;
    
    // No camouflage effect
    virtual double getCoeffCamoufflage() const override;
    
    // Clone for prototype pattern
    virtual IAccessoire* clone() const override;
    
    // Type identifier for visual representation
    virtual int getType() const override;
    
    // Specific getters/setters
    double getCoeffResistance() const;
    void setCoeffResistance(double coeff);
    
    double getCoeffReduction() const;
    void setCoeffReduction(double coeff);
};

#endif