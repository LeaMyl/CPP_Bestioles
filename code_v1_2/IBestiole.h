// IBestiole.h
#ifndef _IBESTIOLE_H_
#define _IBESTIOLE_H_

#include "UImg.h"
#include <vector>  // Add this line
#include <memory>  // Add this line if not already present

class Milieu;
class IAccessoire;
class ICapteur;

class IBestiole
{
    public:

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
    virtual double getLimit() const = 0;
    virtual std::pair<int, int> getPosition() const = 0;
    virtual void vieillir() = 0;  // Pure virtual
    virtual double getSize() const = 0;
    virtual double getVitesse() const = 0;
    virtual double getOrientation() const = 0;
    virtual bool meurt() = 0;
    virtual void changeOrientation(double nouvelleOrientation) = 0;  // Pure virtual
    virtual IBestiole* clone() const = 0;  // Pure virtual
    virtual bool possedeYeux() const = 0;
    virtual bool possedeOreilles() const = 0;
    virtual double getResistanceCollision(double probaBase) const = 0;

    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual void setX(int x) = 0;
    virtual void setY(int y) = 0;
    virtual const std::vector<IAccessoire*>& getAccessoires() const = 0;
};

#endif