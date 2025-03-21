// IBestiole.h
#ifndef _IBESTIOLE_H_
#define _IBESTIOLE_H_

#include "UImg.h"

class Milieu;

class IBestiole
{
    public:
    static const double AFF_SIZE;
    static const double MAX_VITESSE;
    static const double LIMITE_VUE;

    static int next;

    int identite;
    int x, y;
    double cumulX, cumulY;
    double orientation;
    double vitesse;
    T* couleur;
    int age;
    int ageLimite;
public:
    virtual ~IBestiole() = default;
    virtual void bouge(int xLim, int yLim) = 0;
    virtual void action(Milieu & monMilieu) = 0;
    virtual void draw(UImg & support) = 0;
    virtual bool jeTeVois(const IBestiole & b) const = 0;
    virtual void initCoords(int xLim, int yLim) = 0;
    virtual double getLimit() const { return ageLimite; };
    virtual std::pair<int, int> getPosition() const = 0;
    virtual double getSize() const = 0;
    virtual double getVitesse() const = 0;
    virtual double getOrientation() const = 0;
    virtual bool meurt() = 0;
    virtual IBestiole* clone() const = 0;
};

#endif