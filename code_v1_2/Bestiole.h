// Bestiole.h
#ifndef _BESTIOLE_H_
#define _BESTIOLE_H_

#include "IBestiole.h"
#include "ICapteur.h"
#include "IAccessoire.h"
#include "IComportement.h"
#include "UImg.h"
#include "Configuration.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Milieu;

class Bestiole : public IBestiole
{
private:
    // Attributs statiques
    static int next;  // Générateur d'identifiants uniques
    
    // Attributs de position et de mouvement
    int x, y;              // Coordonnées actuelles
    double cumulX, cumulY; // Cumul des déplacements fractionnaires
    double orientation;    // Direction de déplacement
    double vitesse;        // Vitesse de déplacement
    
    // Attributs d'état
    T* couleur;            // Couleur de la bestiole
    int age;               // Âge actuel
    int ageLimite;         // Âge maximum
    int identite;          // Identifiant unique

    // Conteneurs de composants
    std::vector<std::unique_ptr<ICapteur>> capteurs;  // Capteurs de la bestiole
    vector<IAccessoire*> accessoires;                 // Accessoires de la bestiole
    IComportement* comportement = nullptr;            // Comportement de la bestiole

    // Méthode privée de mouvement
    void bouge(int xLim, int yLim) override;

public:
    // Constructeurs et destructeur
    Bestiole(int ageLimite, double vitesse);     // Constructeur standard
    Bestiole(const Bestiole& b);                 // Constructeur par copie
    ~Bestiole();                                 // Destructeur

    // ===== MÉTHODES DE BASE =====
    // Méthodes principales de simulation
    void action(Milieu& monMilieu) override;     // Action à chaque tour
    void draw(UImg& support) override;           // Dessin de la bestiole
    void initCoords(int xLim, int yLim) override;// Initialisation des coordonnées

    // ===== MÉTHODES DE CAPTEURS =====
    // Gestion des capteurs
    void ajouterCapteur(std::unique_ptr<ICapteur> capteur);  // Ajouter un capteur
    bool possedeYeux() const override;           // Vérifier la présence d'yeux
    bool possedeOreilles() const override;       // Vérifier la présence d'oreilles
    
    // Méthodes de détection
    bool jeTeVois(const IBestiole& b) const override;  // Détection mutuelle
    bool detecte(const IBestiole& autre) const;        // Détection unilatérale
    bool estDetectee(const IBestiole& autre) const;    // Probabilité d'être détecté

    // ===== MÉTHODES D'ACCESSOIRES =====
    // Gestion des accessoires
    void ajouterAccessoire(IAccessoire* accessoire);   // Ajouter un accessoire
    double getCoeffCamouflage() const;                 // Coefficient de camouflage
    double getResistanceCollision(double probaBase) const override; // Résistance aux collisions

    // ===== MÉTHODES DE COMPORTEMENT =====
    void setComportement(IComportement* comp);         // Définir un comportement
    IComportement* getComportement() const { return comportement; }; // Obtenir le comportement

    // ===== MÉTHODES DE CYCLE DE VIE =====
    void vieillir() override;                   // Faire vieillir la bestiole
    bool meurt() override;                      // Vérifier si la bestiole meurt

    // ===== GETTERS ET SETTERS =====
    // Position
    std::pair<int, int> getPosition() const override;
    int getX() const override;
    int getY() const override;
    void setX(int x) override;
    void setY(int y) override;
    double getSize() const override;

    // Mouvement
    double getVitesse() const override;
    void setVitesse(double nouvelleVitesse);
    double getOrientation() const override;
    void changeOrientation(double nouvelleOrientation) override;

    // Autres
    int getIdentite() const { return identite; }
    double getLimit() const override { return ageLimite; }
    const std::vector<IAccessoire*>& getAccessoires() const override;

    // ===== OPÉRATEURS =====
    friend bool operator==(const Bestiole& b1, const Bestiole& b2);

    // ===== MÉTHODES DE CLONAGE =====
    IBestiole* clone() const override;
};

#endif // _BESTIOLE_H_