// Multiple.h
#ifndef _MULTIPLE_H_
#define _MULTIPLE_H_

#include "IComportement.h"
#include <vector>
#include <memory>

class Multiple : public IComportement
{
private:
    std::vector<IComportement*> comportements;
    std::vector<double> poids;

public:
    Multiple();
    virtual ~Multiple();

    void ajouterComportement(IComportement* comp, double poids);
    double calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const override;
    IComportement* clone() const override;
    std::string getNom() const override { return "Multiple"; }
};

#endif // _MULTIPLE_H_