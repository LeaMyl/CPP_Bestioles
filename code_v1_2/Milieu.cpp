#include "Milieu.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define NAGEOIRES 1
#define CARAPACE 2
#define CAMOUFLAGE 3

const T Milieu::white[] = { (T)255, (T)255, (T)255 };
bool Milieu::showFieldOfView = true;

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3), width(_width), height(_height) {
    cout << "const Milieu" << endl;
    std::srand(time(NULL));
}

Milieu::~Milieu() {
    cout << "dest Milieu" << endl;
    for (auto& bestiole : listeBestioles) {
        delete bestiole;
    }
}

void Milieu::step() {
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

    // Gérer les collisions
    gererCollisions();

    // Traiter les événements naturels
    processNaturalEvents();

    // Gérer le vieillissement et les morts naturelles
    for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ) {
        (*it)->vieillir();

        // Vérifier si la bestiole meurt de vieillesse
        if ((*it)->meurt()) {
            delete *it;
            it = listeBestioles.erase(it);
        } else {
            (*it)->action(*this);
            ++it;
        }
    }

    // Dessiner les bestioles
    for (auto& bestiole : listeBestioles) {
        bestiole->draw(*this);
    }
}

void Milieu::addMember(IBestiole* b) {
    listeBestioles.push_back(b);
    b->initCoords(width, height);
}

void Milieu::removeMember(IBestiole* b) {
    auto it = std::find(listeBestioles.begin(), listeBestioles.end(), b);
    if (it != listeBestioles.end()) {
        delete *it;
        listeBestioles.erase(it);
    }
}

int Milieu::nbVoisins(const IBestiole& b) const {
    int nb = 0;
    for (const auto& bestiole : listeBestioles) {
        if (&b != bestiole && b.jeTeVois(*bestiole)) {
            nb++;
        }
    }
    return nb;
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

void Milieu::printInfo() const {
    cout << "Nombre de bestioles : " << listeBestioles.size() << endl;
    int nNageoires = 0;
    int nCarapaces = 0;
    int nCamouflages = 0;
    int nYeux = 0;
    int nOreilles = 0;

    for (auto b : listeBestioles) {
        for (auto acc : b->getAccessoires()) {
            if (acc->getType() == NAGEOIRES) {
                nNageoires++;
            } else if (acc->getType() == CARAPACE) {
                nCarapaces++;
            } else if (acc->getType() == CAMOUFLAGE) {
                nCamouflages++;
            }
        }

        if (b->possedeYeux()) {
            nYeux++;
        }

        if (b->possedeOreilles()) {
            nOreilles++;
        }
    }

    cout << "Nombre de bestioles avec nageoires : " << nNageoires << endl;
    cout << "Nombre de bestioles avec carapaces : " << nCarapaces << endl;
    cout << "Nombre de bestioles avec camouflage : " << nCamouflages << endl;
    cout << "Nombre de bestioles avec yeux : " << nYeux << endl;
    cout << "Nombre de bestioles avec oreilles : " << nOreilles << endl;
}

void Milieu::toggleFieldOfView() {
    showFieldOfView = !showFieldOfView;
}

bool Milieu::getShowFieldOfView() const {
    return showFieldOfView;
}

void Milieu::gererCollisions() {
    for (auto it1 = listeBestioles.begin(); it1 != listeBestioles.end(); ) {
        bool it1Died = false;

        for (auto it2 = listeBestioles.begin(); it2 != listeBestioles.end(); ) {
            if (*it1 != *it2) {
                double dist = std::sqrt(
                    ((*it1)->getX() - (*it2)->getX()) * ((*it1)->getX() - (*it2)->getX()) +
                    ((*it1)->getY() - (*it2)->getY()) * ((*it1)->getY() - (*it2)->getY())
                );

                if (dist < Configuration::AFF_SIZE) {
                    double probaBase = Configuration::SURVIVE_COLLISION;
                    double proba1 = (*it1)->getResistanceCollision(probaBase);
                    double proba2 = (*it2)->getResistanceCollision(probaBase);

                    bool it1Survives = (std::rand() % 100) < proba1 * 100;
                    bool it2Survives = (std::rand() % 100) < proba2 * 100;

                    if (!it1Survives) {
                        it1Died = true;
                        break;
                    }

                    if (!it2Survives) {
                        delete *it2;
                        it2 = listeBestioles.erase(it2);
                        continue;
                    }

                    // Rebond des bestioles
                    double dx = (*it2)->getX() - (*it1)->getX();
                    double dy = (*it2)->getY() - (*it1)->getY();
                    double collisionAngle = std::atan2(-dy, dx);

                    double newOri1 = 2 * collisionAngle - (*it1)->getOrientation();
                    double newOri2 = 2 * collisionAngle - (*it2)->getOrientation();

                    (*it1)->changeOrientation(newOri1);
                    (*it2)->changeOrientation(newOri2);

                    double pushDistance = (Configuration::AFF_SIZE - dist) / 2 + 1;
                    double pushX = pushDistance * std::cos(collisionAngle);
                    double pushY = -pushDistance * std::sin(collisionAngle);

                    (*it1)->setX((*it1)->getX() - pushX);
                    (*it1)->setY((*it1)->getY() - pushY);
                    (*it2)->setX((*it2)->getX() + pushX);
                    (*it2)->setY((*it2)->getY() + pushY);
                }
            }
            ++it2;
        }

        if (it1Died) {
            delete *it1;
            it1 = listeBestioles.erase(it1);
        } else {
            ++it1;
        }
    }
}

void Milieu::processNaturalEvents() {
    // Naissances spontanées
    BestioleFactory* factory ;
    if ((std::rand() % 1000) < (Configuration::GENERATION_RATE * 10)) {
        
        std::unique_ptr<IBestiole> b = factory->createBestioleWithRandomBestiole();
        b->initCoords(width, height);
        std::cout << "Nouvelle bestiole née!" << std::endl;
        addMember(b.release());
    }

    for (IBestiole* bestiole : listeBestioles) {
        if ((std::rand() % 1000) < (Configuration::CLONE_RATE * 10)) {
            std::unique_ptr<IBestiole> clone = factory->cloneBestiole(*bestiole);
            clone->initCoords(width, height);
            listeBestioles.push_back(clone.release()); // Si vous devez garder des raw pointers
            std::cout << "Bestiole clonée!" << std::endl;
        }
    }

}


void Milieu::toggleFieldOfView() { 
   showFieldOfView = !showFieldOfView; 
}

bool Milieu::getShowFieldOfView() const { 
   return showFieldOfView; 
}
