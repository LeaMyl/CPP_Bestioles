// ICapteur.h
#ifndef _ICAPTEUR_H_
#define _ICAPTEUR_H_

class IBestiole;

class ICapteur 
{
public:
    virtual ~ICapteur() = default;
    virtual bool detecte(const IBestiole & moi, const IBestiole & autre) const = 0;
    virtual double getDistance() const = 0;
    virtual double getChampAngulaire() const = 0;
    virtual double getCapaciteDetection() const = 0;
    virtual ICapteur* clone() const = 0;
};

#endif // _ICAPTEUR_H_