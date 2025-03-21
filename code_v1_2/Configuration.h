#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <iostream>

using namespace std;

// Cette classe va permettre de configurer la simulation

class Configuration
{
public :
   //___________Définition des taux de chaque comportement___________
   static double    TAUX_GREGAIRE;
   static double    TAUX_PEUREUSE;
   static double    TAUX_KAMIKAZE;
   static double    TAUX_PREVOYANTE;
   static double    TAUX_MULTIPLE;
   static double    TAUX_NORMALE;

   // Définition des tailles des bestioles
   static double     AFF_SIZE;
   // Définition des vitesses maximales des bestioles
   static double     MAX_VITESSE;

   //___________Oreilles et YEUX___________
   // Distance d'écoute
   static double     MAX_DELTA_O;
   static double     MIN_DELTA_O;
   // Capacité de détection oreille
   static double     MAX_GAMMA_O;
   static double     MIN_GAMMA_O;
   // Distance de vue
   static double     MAX_DELTA_Y;
   static double     MIN_DELTA_Y;
   // Capacité de détection vue
   static double     MAX_GAMMA_Y;
   static double     MIN_GAMMA_Y;
   // Champ angulaire de vision
   static double     MAX_ALPHA;
   static double     MIN_ALPHA; 

   //___________Équipements___________
   // Multiplicateur des nageoires
   static double     MAX_NU;
   // Capacité de résistance
   static double     MAX_OMEGA;
   // Reducteur de vitesse
   static double     MAX_ETA;
   // Facteurs de camouflage
   static double     MAX_PSI;
   static double     MIN_PSI;

   //___________Paramètres de la simulation___________
   // Nombre de bestioles générées naturellement
   static double     GENERATION_RATE;
   // Probabilité de clonage
   static double     CLONE_RATE;
   // Probabilité de survie lors d'une collision
   static double     SURVIVE_COLLISION;
   // Probabilité de mutation d'un comportement à un autre
   static double     PROPORTION_CHANGE;
   // Esperence de vie moyenne
   static int        VIE;

public :
   // Constructeur par défaut
   Configuration();

   // Destructeur par défaut
   ~Configuration();

};

#endif // _CONFIGURATION_H_