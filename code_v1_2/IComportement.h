// IComportement.h
#ifndef _ICOMPORTEMENT_H_
#define _ICOMPORTEMENT_H_

#include <string>

class IBestiole;
class Milieu;

class IComportement
{
public:
    virtual ~IComportement() = default;
    virtual double calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const = 0;
    virtual IComportement* clone() const = 0;
    virtual std::string getNom() const = 0;
};

#endif // _ICOMPORTEMENT_H_
