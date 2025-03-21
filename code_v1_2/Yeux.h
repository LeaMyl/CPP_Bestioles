#ifndef _YEUX_H_
#define _YEUX_H_

#include "ICapteur.h"
#include <cstdlib>

class Yeux : public ICapteur {
public:
    double angle;  // Champ angulaire de vision [αmin ; αmax]
    double dist;  // Distance de détection [δymin ; δymax]
    double capa;  // Capacité de détection [γymin ; γymax]

    Yeux(double a ,double d, double c);
    ~Yeux();

    // Implémentation des méthodes de ICapteur
    bool detecte(const IBestiole& moi, const IBestiole& autre) const override;
    ICapteur* clone() const override;
};

#endif // _YEUX_H_