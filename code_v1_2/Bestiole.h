// Bestiole.h
// Bestiole.h
#ifndef _BESTIOLE_H_
#define _BESTIOLE_H_

#include "IBestiole.h"
#include "ICapteur.h"
#include "IAccessoire.h"
#include "IComportement.h"
#include "UImg.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Milieu;

class Bestiole : public IBestiole
{
private:
    static const double AFF_SIZE;

    static int next;

    
    int x, y;
    double cumulX, cumulY;
    double orientation;
    double vitesse;
    T* couleur;
    int age;
    int ageLimite;

    
    std::vector<std::unique_ptr<ICapteur>> capteurs;
    vector<IAccessoire*> accessoires;
    IComportement* comportement;

    void bouge(int xLim, int yLim) override;

public:
    int identite;
    Bestiole( int ageLimite, double vitesse);
    Bestiole(const Bestiole& b);
    ~Bestiole();
    
    // Méthodes de IBestiole
    void action(Milieu& monMilieu) override;
    void draw(UImg& support) override;
    bool jeTeVois(const IBestiole& b) const override;
    void initCoords(int xLim, int yLim) override;
    std::pair<int, int> getPosition() const override { return std::pair<int, int>(x, y); }
    double getVitesse() const override { return vitesse; }
    double getOrientation() const override { return orientation; }
    bool meurt() override;
    IBestiole* clone() const override;
    
    // Méthodes supplémentaires
    int getIdentite() const { return identite; }
    void vieillir();
    void ajouterCapteur(std::unique_ptr<ICapteur> capteur);
    void ajouterAccessoire(IAccessoire* accessoire);
    void setComportement(IComportement* comp);
    IComportement* getComportement() const { return comportement; };
    
    // Pour la détection des collisions
    double getSize() const override { return AFF_SIZE; };

    double getLimit() const override { return ageLimite; };
    
    // Méthodes utiles pour les capteurs et accessoires
    double getCoeffCamouflage() const;
    bool detecte(const IBestiole& autre) const;
    bool estDetectee(const IBestiole& autre) const;
    void changeOrientation(double nouvelleOrientation);

    friend bool operator==(const Bestiole& b1, const Bestiole& b2);
    void setVitesse(double nouvelleVitesse);
};

#endif // _BESTIOLE_H_