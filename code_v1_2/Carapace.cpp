// Carapace.cpp
#include "Carapace.h"

double Carapace::reduireVitesse(double vitesse) {
    return vitesse / eta_max;
}

double Carapace::reduireProbabiliteMort(double probabilite) {
    return probabilite / omega_max;
}

Carapace::Carapace(double omega, double eta) : omega_max(omega), eta_max(eta) {}
