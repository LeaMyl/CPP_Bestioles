#include "Configuration.h"
#include <cmath>

// Définition des taux de comportement pour les différents types de bestioles
double Configuration::TAUX_GREGAIRE = 0.0/6.0;     // Taux de comportement grégaire (suivre le groupe)
double Configuration::TAUX_PEUREUSE = 0.0/6.0;     // Taux de comportement peureux
double Configuration::TAUX_KAMIKAZE = 0.0/6.0;     // Taux de comportement kamikaze
double Configuration::TAUX_PREVOYANTE = 0.0/6.0;   // Taux de comportement prévoyant
double Configuration::TAUX_MULTIPLE = 6.0/6.0;     // Taux de comportement multiple
double Configuration::TAUX_NORMALE = 0.0/6.0;      // Taux de comportement normal

// Taux de détection des capteurs
double Configuration::TAUX_CAPTEURS = 3.0/3.0;     // Taux global de détection des capteurs

// Taux de perception des yeux et oreilles
double Configuration::TAUX_YEUX = 2.0/3.0;         // Taux de perception visuelle
double Configuration::TAUX_OREILLES = 2.0/3.0;     // Taux de perception auditive

// Taux d'accessoires
double Configuration::TAUX_ACCESSOIRES = 3.0/3.0;  // Taux global d'accessoires

// Paramètres de simulation
double Configuration::AFF_SIZE = 10;               // Taille d'affichage des bestioles
double Configuration::MAX_VITESSE = 5;             // Vitesse maximale
int Configuration::VIE = 2000;                     // Durée de vie maximale
double Configuration::PROPORTION_CHANGE = 10;      // Proportion de changement

// Paramètres de configuration des capteurs
double Configuration::MAX_DELTA_O = 100;           // Distance maximale de détection des oreilles
double Configuration::MIN_DELTA_O = 50;            // Distance minimale de détection des oreilles
double Configuration::MAX_GAMMA_O = 10;            // Capacité maximale de détection des oreilles
double Configuration::MIN_GAMMA_O = 5;             // Capacité minimale de détection des oreilles
double Configuration::MAX_DELTA_Y = 100;           // Distance maximale de détection des yeux
double Configuration::MIN_DELTA_Y = 50;            // Distance minimale de détection des yeux
double Configuration::MAX_GAMMA_Y = 10;            // Capacité maximale de détection des yeux
double Configuration::MIN_GAMMA_Y = 5;             // Capacité minimale de détection des yeux

// Paramètres angulaires et de mouvement
double Configuration::MAX_ALPHA = M_PI +  M_PI/4;  // Angle maximal
double Configuration::MIN_ALPHA = M_PI/4;          // Angle minimal

// Paramètres additionnels de mouvement
double Configuration::MAX_NU = 5;                  // Vitesse maximale
double Configuration::MAX_OMEGA = 10;              // Vitesse angulaire maximale
double Configuration::MAX_ETA = 5;                 // Paramètre de déplacement maximal
double Configuration::MAX_PSI = 10;                // Angle maximal de déplacement
double Configuration::MIN_PSI = 5;                 // Angle minimal de déplacement

// Paramètres de reproduction et survie
double Configuration::GENERATION_RATE = 0.1;       // Taux de génération de nouvelles bestioles
double Configuration::CLONE_RATE = 0.1;            // Taux de clonage
double Configuration::SURVIVE_COLLISION = 0.1;     // Probabilité de survie aux collisions

// Constructeur (vide)
Configuration::Configuration() {}

// Destructeur (vide)
Configuration::~Configuration() {}