#include "Yeux.h"

bool Yeux::detecterBestiole(double angle, double distance, double probabilite_detection) {
    if (angle >= angle_min && angle <= angle_max &&
        distance >= distance_min && distance <= distance_max) {
        double gamma = gamma_min + (gamma_max - gamma_min) * (rand() / (double)RAND_MAX);
        return (probabilite_detection <= gamma);
    }
    return false;
}

Yeux::Yeux(double a_min, double a_max, double d_min, double d_max, double g_min, double g_max) : angle_min(a_min), angle_max(a_max), distance_min(d_min), distance_max(d_max), gamma_min(g_min), gamma_max(g_max) {}