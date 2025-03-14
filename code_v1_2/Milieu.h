// Milieu.h
#ifndef _MILIEU_H_
#define _MILIEU_H_

#include "UImg.h"
#include "IBestiole.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Milieu : public UImg
{
private:
    static const T white[];

    int width, height;
    std::vector<IBestiole*> listeBestioles;
    void gererCollisions();
    void gererNaissances();
    void gererMorts();

public:
    Milieu(int _width, int _height);
    ~Milieu();

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void step();

    void addMember(IBestiole* b);
    void removeMember(IBestiole* b);
    int nbVoisins(const IBestiole& b) const;

    std::vector<const IBestiole*> detecteBestiolesVoisines(const IBestiole& b) const;
    bool testCollision(const IBestiole& b1, const IBestiole& b2);
};

#endif // _MILIEU_H_