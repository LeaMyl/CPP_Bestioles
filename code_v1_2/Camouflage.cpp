// Camouflage.cpp
#include "Camouflage.h"

double Camouflage::getCamouflageCapacity() const {
    return psi_max; // On considère le camouflage maximal
}

Camouflage::Camouflage(double psiMin, double psiMax) : psi_min(psiMin), psi_max(psiMax) {}