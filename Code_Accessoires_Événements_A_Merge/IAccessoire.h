#ifndef _IACCESSOIRE_H_
#define _IACCESSOIRE_H_

class IAccessoire {
public:
    virtual ~IAccessoire() {}
    
    // Modify speed of the bestiole (returns modified speed)
    virtual double modulerVitesse(double vitesse) const = 0;
    
    // Modify death probability in collisions (returns modified probability)
    virtual double modulerResistance(double proba) const = 0;
    
    // Get camouflage coefficient (0 = not camouflaged, 1 = perfectly camouflaged)
    virtual double getCoeffCamoufflage() const = 0;
    
    // Clone method for the prototype pattern
    virtual IAccessoire* clone() const = 0;
    
    // For visual representation
    virtual int getType() const = 0;
};

#endif