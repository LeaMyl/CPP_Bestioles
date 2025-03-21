#ifndef _OREILLES_H_
#define _OREILLES_H_

#include "ICapteur.h"
#include <cmath>

class Oreilles : public ICapteur {
    public:
    double angle;  // Champ angulaire de vision [αmin ; αmax]
    double dist;  // Distance de détection [δymin ; δymax]
    double capa;  // Capacité de détection [γymin ; γymax]

    Oreilles(double d, double c);
    virtual ~Oreilles() = default;

    // Implémentation des méthodes de ICapteur
    bool detecte(const IBestiole& moi, const IBestiole& autre) const override;
    ICapteur* clone() const override;
};

#endif // _OREILLES_H_