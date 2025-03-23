#include "Configuration.h"
#include <cmath>

double Configuration::TAUX_GREGAIRE = 0.15;
double Configuration::TAUX_PEUREUSE = 0.15;
double Configuration::TAUX_KAMIKAZE = 0.15;
double Configuration::TAUX_PREVOYANTE = 0.15;
double Configuration::TAUX_MULTIPLE = 0.15;
double Configuration::TAUX_NORMALE = 0.15;
double Configuration::TAUX_CAPTEURS = 0.6;
double Configuration::TAUX_ACCESSOIRES = 0.3;

double Configuration::AFF_SIZE = 10;
double Configuration::MAX_VITESSE = 5;

double Configuration::MAX_DELTA_O = 75;
double Configuration::MIN_DELTA_O = 15;
double Configuration::MAX_GAMMA_O = 10;
double Configuration::MIN_GAMMA_O = 5;
double Configuration::MAX_DELTA_Y = 75;
double Configuration::MIN_DELTA_Y = 15;
double Configuration::MAX_GAMMA_Y = 10;
double Configuration::MIN_GAMMA_Y = 5;
double Configuration::MAX_ALPHA = 2 * M_PI;
double Configuration::MIN_ALPHA = 0;

double Configuration::MAX_NU = 10;
double Configuration::MAX_OMEGA = 10;
double Configuration::MAX_ETA = 10;
double Configuration::MAX_PSI = 10;
double Configuration::MIN_PSI = 5;

double Configuration::GENERATION_RATE = 0.3;
double Configuration::CLONE_RATE = 0.2;
double Configuration::SURVIVE_COLLISION = 0.5;
double Configuration::PROPORTION_CHANGE = 0.1;
int Configuration::VIE = 100;

// Constructeur
Configuration::Configuration() {}

// Destructeur
Configuration::~Configuration() {}

