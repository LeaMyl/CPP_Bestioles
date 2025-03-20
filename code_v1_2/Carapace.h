// Carapace.h
#ifndef _CARAPACE_H_
#define _CARAPACE_H_

#include "IAccessoire.h"

class Carapace {
    public:
        double omega_max;  // Coefficient de réduction de probabilité de mort
        double eta_max;  // Facteur de réduction de vitesse
    
        Carapace(double omega, double eta);
    
        double reduireProbabiliteMort(double probabilite);
    
        double reduireVitesse(double vitesse);
};

#endif // _CARAPACE_H_