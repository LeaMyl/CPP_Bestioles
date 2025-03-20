// Nageoires.cpp
#include "Nageoires.h"

const double nu_max = 1.0;

double Nageoires::appliquerVitesse(double vitesse) {return vitesse * nu_max;}

Nageoires::Nageoires(double nu) : nu_max(nu) {}