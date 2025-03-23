#include "Yeux.h"
#include "Bestiole.h"

#include <cstdlib>

Yeux::Yeux(double d, double g, double a) : delta(d), gamma(g), alpha(a) {}

Yeux::~Yeux() {}

Yeux* Yeux::generateRandomYeux() {
    double d = Configuration::MIN_DELTA_Y + (static_cast<double>(rand()) / RAND_MAX) * 
                (Configuration::MAX_DELTA_Y - Configuration::MIN_DELTA_Y);
    double g = Configuration::MIN_GAMMA_Y + (static_cast<double>(rand()) / RAND_MAX) * 
                (Configuration::MAX_GAMMA_Y - Configuration::MIN_GAMMA_Y);
    double a = Configuration::MIN_ALPHA + (static_cast<double>(rand()) / RAND_MAX) * 
                (Configuration::MAX_ALPHA - Configuration::MIN_ALPHA);
    
    return new Yeux(d, g, a);
}

std::vector<const Bestiole*> Yeux::detecter(const Bestiole& b, const std::vector<Bestiole>& autresBestioles) const {
    std::vector<const Bestiole*> bestioleDetectees;
    double bOrientation = b.getOrientation();
    double bX = b.getX();
    double bY = b.getY();
    
    for (const auto& other : autresBestioles) {
        // Skip self
        if (&b == &other) continue;
        
        // Check if other bestiole is within detection range
        double dx = other.getX() - bX;
        double dy = other.getY() - bY;
        double distance = std::sqrt(dx*dx + dy*dy);
        
        // Check if within vision range
        if (distance <= delta) {
            // Calculate angle between current orientation and direction to other bestiole
            double angle = std::atan2(-dy, dx);
            double angleDiff = std::abs(angle - bOrientation);
            
            // Normalize angle difference to be between 0 and PI
            while (angleDiff > M_PI) angleDiff -= 2 * M_PI;
            angleDiff = std::abs(angleDiff);
            
            // Check if within the vision cone
            if (angleDiff <= alpha / 2) {
                // Apply detection probability based on gamma
                double detectionProba = gamma * (1.0 - (distance / delta));
                
                // Adjust detection probability based on camouflage
                double camouflage = other.getCoeffCamoufflage();
                detectionProba *= (1.0 - camouflage);
                
                // Random detection based on probability
                if ((static_cast<double>(rand()) / RAND_MAX) < detectionProba) {
                    bestioleDetectees.push_back(&other);
                }
            }
        }
    }
    
    return bestioleDetectees;
}

ICapteur* Yeux::clone() const {
    return new Yeux(delta, gamma, alpha);
}