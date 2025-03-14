// IEvenementExterieur.h
#ifndef _IEVENEMENTEXTERIEUR_H_
#define _IEVENEMENTEXTERIEUR_H_

class Milieu;

class IEvenementExterieur
{
public:
    virtual ~IEvenementExterieur() = default;
    virtual void appliquer(Milieu& m) = 0;
};

#endif // _IEVENEMENTEXTERIEUR_H_