#ifndef _OREILLES_H_
#define _OREILLES_H_

#include "ICapteur.h"
#include <cmath>

class Oreilles : public ICapteur {
public:
    double angle;  // Champ angulaire de perception
    double dist;   // Distance de détection
    double capa;   // Capacité de détection

    Oreilles(double d, double c);
    ~Oreilles();

    // Détection d'une autre bestiole
    bool detecte(const IBestiole& moi, const IBestiole& autre) const override;
    
    // Clonage du capteur
    ICapteur* clone() const override;
};

#endif