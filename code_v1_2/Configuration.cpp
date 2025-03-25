#include "Configuration.h"
#include <cmath>

double Configuration::TAUX_GREGAIRE = 2.0/6.0;
double Configuration::TAUX_PEUREUSE = 2.0/6.0;
double Configuration::TAUX_KAMIKAZE = 1.0/6.0;
double Configuration::TAUX_PREVOYANTE = 1.0/6.0;
double Configuration::TAUX_MULTIPLE = 0.0/6.0;
double Configuration::TAUX_NORMALE = 0.0/6.0;


double Configuration::TAUX_CAPTEURS = 3.0/3.0;

double Configuration::TAUX_YEUX = 2.0/3.0;
double Configuration::TAUX_OREILLES = 2.0/3.0; //TAUX_OREILLES + TAUX_YEUX peut etre <1 car on peut avoir des yeux et des oreilles en même temps


double Configuration::TAUX_ACCESSOIRES = 3.0/3.0;


double Configuration::AFF_SIZE = 10;
double Configuration::MAX_VITESSE = 5;
int Configuration::VIE = 2000;
double Configuration::PROPORTION_CHANGE = 10;


double Configuration::MAX_DELTA_O = 100;
double Configuration::MIN_DELTA_O = 50;
double Configuration::MAX_GAMMA_O = 10;
double Configuration::MIN_GAMMA_O = 5;
double Configuration::MAX_DELTA_Y = 100;
double Configuration::MIN_DELTA_Y = 50;
double Configuration::MAX_GAMMA_Y = 10;
double Configuration::MIN_GAMMA_Y = 5;
double Configuration::MAX_ALPHA = M_PI +  M_PI/4;
double Configuration::MIN_ALPHA = M_PI/4;

double Configuration::MAX_NU = 5;
double Configuration::MAX_OMEGA = 10;
double Configuration::MAX_ETA = 5;
double Configuration::MAX_PSI = 10;
double Configuration::MIN_PSI = 5;




double Configuration::GENERATION_RATE = 0.1;
double Configuration::CLONE_RATE = 0.1;
double Configuration::SURVIVE_COLLISION = 0.1;

// Constructeur
Configuration::Configuration() {}

// Destructeur
Configuration::~Configuration() {}

