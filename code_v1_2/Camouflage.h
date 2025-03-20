
// Camouflage.h
#ifndef _CAMOUFLAGE_H_
#define _CAMOUFLAGE_H_

#include "IAccessoire.h"

class Camouflage {
    public:
        double psi_min, psi_max;  // Capacité de camouflage
    
        Camouflage(double psiMin, double psiMax);
    
        double getCamouflageCapacity() const {
            return psi_max; // On considère le camouflage maximal
        }
};

#endif // _CAMOUFLAGE_H_