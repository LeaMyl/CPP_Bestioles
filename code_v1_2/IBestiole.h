// IBestiole.h
#ifndef _IBESTIOLE_H_
#define _IBESTIOLE_H_

#include "UImg.h"

class Milieu;

class IBestiole
{
public:
    virtual ~IBestiole() = default;
    virtual void bouge(int xLim, int yLim) = 0;
    virtual void action(Milieu & monMilieu) = 0;
    virtual void draw(UImg & support) = 0;
    virtual bool jeTeVois(const IBestiole & b) const = 0;
    virtual void initCoords(int xLim, int yLim) = 0;
    virtual std::pair<int, int> getPosition() const = 0;
    double getSize() const { return AFF_SIZE; }
    virtual double getVitesse() const = 0;
    virtual double getOrientation() const = 0;
    virtual bool meurt() = 0;
    virtual IBestiole* clone() const = 0;
};

#endif