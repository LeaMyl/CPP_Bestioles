#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

#include <vector>

class Bestiole;

class ICapteur {
public:
    virtual ~ICapteur() {}
    
    // Detect other bestioles in the environment
    virtual std::vector<const Bestiole*> detecter(const Bestiole& b, const std::vector<Bestiole>& autresBestioles) const = 0;
    
    // Clone method for the prototype pattern
    virtual ICapteur* clone() const = 0;
    
    // For visual representation
    virtual int getType() const = 0;
};

#endif // _ICAPTEUR_H_