// Carapace.h
#ifndef _CARAPACE_H_
#define _CARAPACE_H_

#include "IAccessoire.h"

class Carapace : public IAccessoire
{
private:
    double facteurResistance;
    double facteurReduction;

public:
    Carapace(double resistance = 0.5, double reduction = 0.5);
    virtual ~Carapace() = default;

    double modulerVitesse(double vitesse) const override;
    double modulerResistance(double proba) const override;
    double getCoeffCamoufflage() const override;
    IAccessoire* clone() const override;
};

#endif // _CARAPACE_H_