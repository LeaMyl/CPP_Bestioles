// Oreilles.h
#ifndef _OREILLES_H_
#define _OREILLES_H_

#include "ICapteur.h"
#include "Configuration.h"
#include <cmath>

class Oreilles : public ICapteur {
private:
    double delta;  // Distance d'écoute
    double gamma;  // Capacité d'écoute (probabilité)
    
public:
    Oreilles(double d = 0.0, double g = 0.0);
    ~Oreilles();
    
    // Generate random Oreilles parameters based on configuration
    static Oreilles* generateRandomOreilles();
    
    // Detect other bestioles in hOreillesing range
    std::vector<const Bestiole*> detecter(const Bestiole& b, const std::vector<Bestiole>& autresBestioles) const override;
    
    // Clone method
    ICapteur* clone() const override;
    
    // Get type - 2 for Oreilles
    int getType() const override { return 2; }
    
    // Getters
    double getDelta() const { return delta; }
    double getGamma() const { return gamma; }

    // Modulate view and listening of the bestiole
    double modulerEcoute(double gamma, double delta) const { return gamma; }
};

#endif // _OREILLES_H_