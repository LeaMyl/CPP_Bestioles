// Peureuse.h
#ifndef _PEUREUSE_H_
#define _PEUREUSE_H_

#include "IComportement.h"

class Peureuse : public IComportement
{
private:
    int seuilPeur;
    double facteurAcceleration;

public:
    Peureuse(int seuil = 3, double facteur = 2.0);
    virtual ~Peureuse() = default;

    double calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const override;
    IComportement* clone() const override;
    std::string getNom() const override { return "Peureuse"; }
};

#endif // _PEUREUSE_H_