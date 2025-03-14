// Nageoires.h
#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_

#include "IAccessoire.h"

class Nageoires : public IAccessoire
{
private:
    double facteurVitesse;

public:
    Nageoires(double facteur = 1.5);
    virtual ~Nageoires() = default;

    double modulerVitesse(double vitesse) const override;
    double modulerResistance(double proba) const override;
    double getCoeffCamoufflage() const override;
    IAccessoire* clone() const override;
};

#endif // _NAGEOIRES_H_