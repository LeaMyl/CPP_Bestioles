// Oreilles.h
#ifndef _OREILLES_H_
#define _OREILLES_H_

#include "ICapteur.h"
#include <cmath>

class Oreilles : public ICapteur
{
private:
    double distance; // δ
    double capaciteDetection; // γ

public:
    Oreilles(double dist = 15.0, double capacite = 0.7);
    virtual ~Oreilles() = default;

    bool detecte(const IBestiole & moi, const IBestiole & autre) const override;
    double getDistance() const override { return distance; }
    double getChampAngulaire() const override { return 2 * M_PI; } // Détection dans toutes les directions
    double getCapaciteDetection() const override { return capaciteDetection; }
    ICapteur* clone() const override;
};

#endif // _OREILLES_H_