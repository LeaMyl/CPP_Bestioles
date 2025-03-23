#ifndef _YEUX_H_
#define _YEUX_H_

#include "ICapteur.h"
#include "Configuration.h"
#include <cmath>

class Yeux : public ICapteur {
private:
    double delta;  // Distance de perception
    double gamma;  // Capacité de détection (probabilité)
    double alpha;  // Champ de vision angulaire (en radians)
    
public:
    Yeux(double d = 0.0, double g = 0.0, double a = 0.0);
    ~Yeux();
    
    // Generate random Yeux parameters based on configuration
    static Yeux* generateRandomYeux();
    
    // Detect other bestioles in the field of vision
    std::vector<const Bestiole*> detecter(const Bestiole& b, const std::vector<Bestiole>& autresBestioles) const override;
    
    // Clone method
    ICapteur* clone() const override;
    
    // Get type - 1 for Yeux
    int getType() const override { return 1; }
    
    // Getters
    double getDelta() const { return delta; }
    double getGamma() const { return gamma; }
    double getAlpha() const { return alpha; }

    // Modulate view and listening of the bestiole
    double modulerVue(double gamma, double delta, double alpha) const { return gamma; }
};

#endif // _YEUX_H_