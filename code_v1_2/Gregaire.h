// Gregaire.h
#ifndef _GREGAIRE_H_
#define _GREGAIRE_H_

#include "IComportement.h"

class Gregaire : public IComportement
{
public:
    Gregaire() = default;
    virtual ~Gregaire() = default;

    double calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const override;
    IComportement* clone() const override;
    std::string getNom() const override { return "Gregaire"; }
};

#endif // _GREGAIRE_H_