#ifndef _MILIEU_H_
#define _MILIEU_H_

#include "UImg.h"
#include "IBestiole.h"
#include "Bestiole.h"
#include "Configuration.h"
#include "BestioleFactory.h"
#include "AccessoireFactory.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

class Milieu : public UImg {
public:
    // Constructeur et destructeur
    Milieu(int _width, int _height);
    ~Milieu();

    // Propriétés statiques et accesseurs
    static bool showFieldOView;
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Méthodes principales de simulation
    void step();                         // Effectue une étape de simulation
    void addMember(IBestiole* b);        // Ajoute une bestiole au milieu
    void removeMember(IBestiole* b);     // Supprime une bestiole du milieu

    // Gestion des événements naturels
    void gererCollisions();               // Gère les collisions entre bestioles
    void processNaturalEvents();          // Gère les naissances et clonages

    // Utilitaires d'information
    void printInfo() const;               // Affiche des statistiques sur les bestioles
    void toggleFieldOfView();             // Active/désactive l'affichage du champ de vision
    bool getShowFieldOfView() const;      // Retourne l'état du champ de vision

    // Méthodes de détection
    int nbVoisins(const IBestiole& b) const;                       // Compte les voisins d'une bestiole
    std::vector<const IBestiole*> detecteBestiolesVoisines(const IBestiole& b) const; // Détecte les bestioles voisines

    // Couleur de fond
    static const T white[];
    static bool showFieldOfView;
    std::vector<IBestiole*> getListeBestioles() const { return listeBestioles; }

private:
    int width;                            // Largeur du milieu
    int height;                           // Hauteur du milieu
    std::vector<IBestiole*> listeBestioles; // Liste des bestioles dans le milieu

    // Méthode interne pour tester les collisions
    bool testCollision(const IBestiole& b1, const IBestiole& b2) const;
};

#endif