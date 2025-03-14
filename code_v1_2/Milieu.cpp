// Milieu.cpp
#include "Milieu.h"
#include "Configuration.h"
#include "Bestiole.h"


const T Milieu::white[] = { (T)255, (T)255, (T)255 };

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3),
    width(_width), height(_height)
{
    cout << "const Milieu" << endl;
    std::srand(time(NULL));
}

Milieu::~Milieu()
{
    cout << "dest Milieu" << endl;
    
    for (auto& bestiole : listeBestioles) {
        delete bestiole;
    }
}

void Milieu::step()
{
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);
    
    // Copier la liste pour éviter les problèmes de modification pendant l'itération
    std::vector<IBestiole*> copieListeBestioles = listeBestioles;
    
    for (auto& bestiole : copieListeBestioles) {
        bestiole->action(*this);
    }
    
    // Gérer les collisions, naissances et morts
    gererCollisions();
    gererNaissances();
    gererMorts();
    
    // Dessiner les bestioles
    for (auto& bestiole : listeBestioles) {
        bestiole->draw(*this);
    }
}

void Milieu::addMember(IBestiole* b)
{
    listeBestioles.push_back(b);
    b->initCoords(width, height);
}

void Milieu::removeMember(IBestiole* b)
{
    auto it = std::find(listeBestioles.begin(), listeBestioles.end(), b);
    if (it != listeBestioles.end()) {
        delete *it;
        listeBestioles.erase(it);
    }
}

int Milieu::nbVoisins(const IBestiole& b) const
{
    int nb = 0;
    for (const auto& bestiole : listeBestioles) {
        if (&b != bestiole && b.jeTeVois(*bestiole)) {
            nb++;
        }
    }
    return nb; // Ajout du return
}


std::vector<const IBestiole*> Milieu::detecteBestiolesVoisines(const IBestiole& b) const
{
      std::vector<const IBestiole*> voisines;
      
      for (const auto& bestiole : listeBestioles) {
         if (&b != bestiole && b.jeTeVois(*bestiole)) {
               voisines.push_back(bestiole);
         }
      }
      
      return voisines;
}

bool testCollision(const IBestiole& b1, const IBestiole& b2)
{
    auto pos1 = b1.getPosition();
    auto pos2 = b2.getPosition();
    
    double dx = pos2.first - pos1.first;
    double dy = pos2.second - pos1.second;
    double distance = std::sqrt(dx*dx + dy*dy);
    
    return distance < (b1.getSize() + b2.getSize()) / 2;

}