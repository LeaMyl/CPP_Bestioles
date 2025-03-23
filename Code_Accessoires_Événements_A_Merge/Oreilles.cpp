#include "Oreilles.h"
#include "Bestiole.h"

#include <cstdlib>

Oreilles::Oreilles(double d, double g) : delta(d), gamma(g) {}

Oreilles::~Oreilles() {}

Oreilles* Oreilles::generateRandomOreilles() {
    double d = Configuration::MIN_DELTA_O + (static_cast<double>(rand()) / RAND_MAX) * 
                (Configuration::MAX_DELTA_O - Configuration::MIN_DELTA_O);
    double g = Configuration::MIN_GAMMA_O + (static_cast<double>(rand()) / RAND_MAX) * 
                (Configuration::MAX_GAMMA_O - Configuration::MIN_GAMMA_O);
    
    return new Oreilles(d, g);
}

std::vector<const Bestiole*> Oreilles::detecter(const Bestiole& b, const std::vector<Bestiole>& autresBestioles) const {
    std::vector<const Bestiole*> bestioleDetectees;
    double bX = b.getX();
    double bY = b.getY();
    
    for (const auto& other : autresBestioles) {
        // Skip self
        if (&b == &other) continue;
        
        // Check if other bestiole is within detection range
        double dx = other.getX() - bX;
        double dy = other.getY() - bY;
        double distance = std::sqrt(dx*dx + dy*dy);
        
        // Check if within hOreillesing range
        if (distance <= delta) {
            // Apply detection probability based on gamma
            double detectionProba = gamma * (1.0 - (distance / delta));
            
            // HOreillesing is not affected by camouflage (only visual detection is)
            
            // Random detection based on probability
            if ((static_cast<double>(rand()) / RAND_MAX) < detectionProba) {
                bestioleDetectees.push_back(&other);
            }
        }
    }
    
    return bestioleDetectees;
}

ICapteur* Oreilles::clone() const {
    return new Oreilles(delta, gamma);
}