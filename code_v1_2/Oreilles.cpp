#include "Oreilles.h"
#include <cstdlib>


Oreilles::Oreilles(double d_min, double d_max, double g_min, double g_max): distance_min(d_min), distance_max(d_max), gamma_min(g_min), gamma_max(g_max) {}

bool Oreilles::detecterBestiole(double distance, double probabilite_detection) {
    if (distance >= distance_min && distance <= distance_max) {
        double gamma = gamma_min + (gamma_max - gamma_min) * (rand() / (double)RAND_MAX);
        return (probabilite_detection <= gamma);
    }
    return false;
}