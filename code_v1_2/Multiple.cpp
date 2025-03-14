// Multiple.cpp
#include "Multiple.h"
#include "IBestiole.h"
#include "Milieu.h"
#include <cmath>
#include <numeric>

Multiple::Multiple()
{
}

Multiple::~Multiple()
{
    for (auto comp : comportements) {
        delete comp;
    }
}

void Multiple::ajouterComportement(IComportement* comp, double p)
{
    comportements.push_back(comp);
    this->poids.push_back(p);
}

double Multiple::calculerNouvelleDirection(const IBestiole & b, const Milieu & m) const
{
    if (comportements.empty()) {
        return b.getOrientation();
    }
    
    double sommeX = 0.0;
    double sommeY = 0.0;
    double sommePoids = 0.0;
    
    for (size_t i = 0; i < comportements.size(); i++) {
        double direction = comportements[i]->calculerNouvelleDirection(b, m);
        sommeX += cos(direction) * poids[i];
        sommeY += sin(direction) * poids[i];
        sommePoids += poids[i];
    }
    
    if (sommePoids > 0) {
        sommeX /= sommePoids;
        sommeY /= sommePoids;
    }
    
    if (sommeX == 0 && sommeY == 0) {
        return b.getOrientation();
    }
    
    return atan2(sommeY, sommeX);
}

IComportement* Multiple::clone() const
{
    Multiple* clone = new Multiple();
    
    for (size_t i = 0; i < comportements.size(); i++) {
        clone->ajouterComportement(comportements[i]->clone(), poids[i]);
    }
    
    return clone;
}

