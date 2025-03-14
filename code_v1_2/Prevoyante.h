// Prevoyante.h
#ifndef _PREVOYANTE_H_
#define _PREVOYANTE_H_

#include "IComportement.h"

class Prevoyante : public IComportement
{
public:
    Prevoyante() = default;
    virtual ~Prevoyante() = default;

    double calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const override;
    IComportement* clone() const override;
    std::string getNom() const override { return "Prevoyante"; }
};

#endif // _PREVOYANTE_H_