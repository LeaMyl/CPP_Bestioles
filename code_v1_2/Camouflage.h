
// Camouflage.h
#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "IAccessoire.h"

class Camouflage : public IAccessoire
{
private:
    double indiceCamoufflage;

public:
    Camouflage(double indice = 0.5);
    virtual ~Camouflage() = default;

    double modulerVitesse(double vitesse) const override;
    double modulerResistance(double proba) const override;
    double getCoeffCamoufflage() const override;
    IAccessoire* clone() const override;
};

#endif // _CAMOUFLAGE_H_