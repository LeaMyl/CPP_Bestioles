#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <iostream>

// Classe de configuration globale pour la simulation
// Contient tous les paramètres ajustables de la simulation
class Configuration
{
public:
    // Taux de probabilité des différents comportements
    static double TAUX_GREGAIRE;
    static double TAUX_PEUREUSE;
    static double TAUX_KAMIKAZE;
    static double TAUX_PREVOYANTE;
    static double TAUX_MULTIPLE;

    // Taux des capteurs
    static double TAUX_CAPTEURS;
    static double TAUX_YEUX;
    static double TAUX_OREILLES; 

    // Taux des accessoires
    static double TAUX_ACCESSOIRES;

    // Paramètres de simulation
    static double AFF_SIZE;         // Taille d'affichage
    static double MAX_VITESSE;      // Vitesse maximale
    static double NOMBRE_BESTIOLES; // Nombre de bestioles

    // Paramètres des capteurs (oreilles et yeux)
    static double MAX_DELTA_O, MIN_DELTA_O;     // Distance d'écoute
    static double MAX_GAMMA_O, MIN_GAMMA_O;     // Capacité de détection auditive
    static double MAX_DELTA_Y, MIN_DELTA_Y;     // Distance de vue
    static double MAX_GAMMA_Y, MIN_GAMMA_Y;     // Capacité de détection visuelle
    static double MAX_ALPHA, MIN_ALPHA;         // Champ angulaire de vision

    // Paramètres des équipements
    static double MAX_NU;     // Multiplicateur des nageoires
    static double MAX_OMEGA;  // Capacité de résistance
    static double MAX_ETA;    // Réducteur de vitesse
    static double MAX_PSI, MIN_PSI;  // Facteurs de camouflage

    // Paramètres avancés de simulation
    static double GENERATION_RATE;    // Taux de génération de bestioles
    static double CLONE_RATE;         // Probabilité de clonage
    static double SURVIVE_COLLISION;  // Probabilité de survie lors des collisions
    static double PROPORTION_CHANGE;  // Probabilité de mutation de comportement
    static int VIE;                   // Espérance de vie moyenne

public:
    // Constructeur et destructeur par défaut
    Configuration();
    ~Configuration();
};

#endif