// Kamikaze.h
#ifndef _KAMIKAZE_H_
#define _KAMIKAZE_H_

#include "IComportement.h"

class Kamikaze : public IComportement
{
public:
    Kamikaze() = default;
    virtual ~Kamikaze() = default;

    double calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const override;
    IComportement* clone() const override;
    std::string getNom() const override { return "Kamikaze"; }
};

#endif // _KAMIKAZE_H_