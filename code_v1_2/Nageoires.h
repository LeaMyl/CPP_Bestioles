// Nageoires.h
#ifndef _NAGEOIRES_H_
#define _NAGEOIRES_H_

#include "IAccessoire.h"

class Nageoires {
    public:
        double nu_max;  // Coefficient multiplicateur de vitesse
    
        Nageoires(double nu);
    
        double appliquerVitesse(double vitesse);
};

#endif // _NAGEOIRES_H_