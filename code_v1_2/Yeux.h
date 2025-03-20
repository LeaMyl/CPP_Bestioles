// Yeux.h
#ifndef _YEUX_H_
#define _YEUX_H_

#include "ICapteur.h"
#include <cstdlib>

class Yeux : public ICapteur {
    public:
        double angle_min, angle_max;  // Champ angulaire de vision
        double distance_min, distance_max;  // Distance de détection
        double gamma_min, gamma_max;  // Capacité de détection
    
        Yeux(double a_min, double a_max, double d_min, double d_max, double g_min, double g_max);
        virtual ~Yeux() = default;
    
        bool detecterBestiole(double angle, double distance, double probabilite_detection);
    };
#endif // _YEUX_H_