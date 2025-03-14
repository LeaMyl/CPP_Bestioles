// IAccessoire.h
#ifndef _IACCESSOIRE_H_
#define _IACCESSOIRE_H_

class IAccessoire
{
public:
    virtual ~IAccessoire() = default;
    virtual double modulerVitesse(double vitesse) const = 0;
    virtual double modulerResistance(double proba) const = 0;
    virtual double getCoeffCamoufflage() const = 0;
    virtual IAccessoire* clone() const = 0;
};

#endif // _IACCESSOIRE_H_