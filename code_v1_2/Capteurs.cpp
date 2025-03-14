#include <stdlib.h>

    class CapteurYeux {
    public:
        double angle_min, angle_max;  // Champ angulaire de vision
        double distance_min, distance_max;  // Distance de détection
        double gamma_min, gamma_max;  // Capacité de détection
    
        CapteurYeux(double a_min, double a_max, double d_min, double d_max, double g_min, double g_max)
            : angle_min(a_min), angle_max(a_max), distance_min(d_min), distance_max(d_max), gamma_min(g_min), gamma_max(g_max) {}
    
        bool detecterBestiole(double angle, double distance, double probabilite_detection) {
            if (angle >= angle_min && angle <= angle_max &&
                distance >= distance_min && distance <= distance_max) {
                double gamma = gamma_min + (gamma_max - gamma_min) * (rand() / (double)RAND_MAX);
                return (probabilite_detection <= gamma);
            }
            return false;
        }
    };
    
    class CapteurOreilles {
    public:
        double distance_min, distance_max;  // Plage de distance d'écoute
        double gamma_min, gamma_max;  // Capacité de détection auditive
    
        CapteurOreilles(double d_min, double d_max, double g_min, double g_max)
            : distance_min(d_min), distance_max(d_max), gamma_min(g_min), gamma_max(g_max) {}
    
        bool detecterBestiole(double distance, double probabilite_detection) {
            if (distance >= distance_min && distance <= distance_max) {
                double gamma = gamma_min + (gamma_max - gamma_min) * (rand() / (double)RAND_MAX);
                return (probabilite_detection <= gamma);
            }
            return false;
        }
    };