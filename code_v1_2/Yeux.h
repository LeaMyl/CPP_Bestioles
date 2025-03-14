// Yeux.h
#ifndef _YEUX_H_
#define _YEUX_H_

#include "ICapteur.h"

class Yeux : public ICapteur
{
private:
    double champAngulaire; // α
    double distance; // δ
    double capaciteDetection; // γ

public:
    Yeux(double champAng = M_PI/2, double dist = 20.0, double capacite = 0.8);
    virtual ~Yeux() = default;

    bool detecte(const IBestiole & moi, const IBestiole & autre) const override;
    double getDistance() const override { return distance; }
    double getChampAngulaire() const override { return champAngulaire; }
    double getCapaciteDetection() const override { return capaciteDetection; }
    ICapteur* clone() const override;
};

#endif // _YEUX_H_