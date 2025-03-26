#ifndef _IBESTIOLE_H_
#define _IBESTIOLE_H_

#include "UImg.h"
#include <vector>
#include <memory>

// Déclarations anticipées des classes dépendantes
class Milieu;
class IAccessoire;
class ICapteur;

// Interface définissant les caractéristiques et comportements des bestioles
class IBestiole
{
public:
    // Attributs de base d'une bestiole
    static int next;  // Identifiant unique
    int identite;
    int x, y;
    double cumulX, cumulY;
    double orientation;
    double vitesse;
    T* couleur;
    int age;
    int ageLimite;

public:
    // Destructeur virtuel pour une destruction sécurisée
    virtual ~IBestiole() = default;

    // Méthodes virtuelles pures définissant le comportement de base
    virtual void bouge(int xLim, int yLim) = 0;
    virtual void action(Milieu & monMilieu) = 0;
    virtual void draw(UImg & support) = 0;
    virtual bool jeTeVois(const IBestiole & b) const = 0;
    virtual void initCoords(int xLim, int yLim) = 0;
    
    // Méthodes d'accès et de modification
    virtual double getLimit() const = 0;
    virtual std::pair<int, int> getPosition() const = 0;
    virtual void vieillir() = 0;
    virtual double getSize() const = 0;
    virtual double getVitesse() const = 0;
    virtual double getOrientation() const = 0;
    virtual bool meurt() = 0;
    virtual void changeOrientation(double nouvelleOrientation) = 0;
    virtual IBestiole* clone() const = 0;
    
    // Méthodes liées aux capteurs
    virtual bool possedeYeux() const = 0;
    virtual bool possedeOreilles() const = 0;
    
    // Méthodes liées aux collisions et accessoires
    virtual double getResistanceCollision(double probaBase) const = 0;
    virtual const std::vector<IAccessoire*>& getAccessoires() const = 0;

    // Accesseurs et mutateurs de position
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual void setX(int x) = 0;
    virtual void setY(int y) = 0;
};

#endif