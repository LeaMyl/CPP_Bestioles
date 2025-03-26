#include "Milieu.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

// Définition des constantes pour les types d'accessoires
#define NAGEOIRES 1
#define CARAPACE 2
#define CAMOUFLAGE 3

// Couleur blanche pour le fond
const T Milieu::white[] = { (T)255, (T)255, (T)255 };

// Indicateur pour afficher le champ de vision des bestioles
bool Milieu::showFieldOfView = true;

// Constructeur du milieu
// Initialise la taille de l'écosystème et initialise le générateur de nombres aléatoires
Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3), width(_width), height(_height) {
    cout << "Constructeur de Milieu" << endl;
    std::srand(time(NULL));
}

// Destructeur du milieu
// Libère la mémoire de toutes les bestioles
Milieu::~Milieu() {
    cout << "Destructeur de Milieu" << endl;
    for (auto& bestiole : listeBestioles) {
        delete bestiole;
    }
}

// Méthode principale d'une étape de simulation
void Milieu::step() {
    // Réinitialise le fond en blanc
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

    // Gestion des collisions entre bestioles
    gererCollisions();

    // Traitement des événements naturels (naissances, clonages)
    processNaturalEvents();

    // Gestion du vieillissement et de la mort des bestioles
    for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ) {
        (*it)->vieillir();

        // Suppression des bestioles qui meurent de vieillesse
        if ((*it)->meurt()) {
            delete *it;
            it = listeBestioles.erase(it);
        } else {
            // Exécution de l'action de la bestiole si elle survit
            (*it)->action(*this);
            ++it;
        }
    }

    // Dessin de toutes les bestioles survivantes
    for (auto& bestiole : listeBestioles) {
        bestiole->draw(*this);
    }
}

// Ajout d'une nouvelle bestiole au milieu
void Milieu::addMember(IBestiole* b) {
    listeBestioles.push_back(b);
    b->initCoords(width, height);
}

// Suppression d'une bestiole du milieu
void Milieu::removeMember(IBestiole* b) {
    auto it = std::find(listeBestioles.begin(), listeBestioles.end(), b);
    if (it != listeBestioles.end()) {
        delete *it;
        listeBestioles.erase(it);
    }
}

// Compte le nombre de voisins visibles pour une bestiole donnée
int Milieu::nbVoisins(const IBestiole& b) const {
    int nb = 0;
    for (const auto& bestiole : listeBestioles) {
        // Vérifie si la bestiole est différente et visible
        if (&b != bestiole && b.jeTeVois(*bestiole)) {
            nb++;
        }
    }
    return nb;
}

// Détecte et retourne la liste des bestioles voisines visibles
std::vector<const IBestiole*> Milieu::detecteBestiolesVoisines(const IBestiole& b) const {
    std::vector<const IBestiole*> voisines;
    for (const auto& bestiole : listeBestioles) {
        // Ajoute les bestioles visibles différentes de la bestiole courante
        if (&b != bestiole && b.jeTeVois(*bestiole)) {
            voisines.push_back(bestiole);
        }
    }
    return voisines;
}

// Teste la collision entre deux bestioles
bool testCollision(const IBestiole& b1, const IBestiole& b2) {
    auto pos1 = b1.getPosition();
    auto pos2 = b2.getPosition();
    
    // Calcul de la distance entre les bestioles
    double dx = pos2.first - pos1.first;
    double dy = pos2.second - pos1.second;
    double distance = std::sqrt(dx*dx + dy*dy);
    
    // Collision si la distance est inférieure à la somme de leurs rayons
    return distance < (b1.getSize() + b2.getSize()) / 2;
}

// Affiche des informations statistiques sur les bestioles
void Milieu::printInfo() const {
    cout << "Nombre de bestioles : " << listeBestioles.size() << endl;
    
    // Compteurs pour différents types d'accessoires et de capteurs
    int nNageoires = 0, nCarapaces = 0, nCamouflages = 0;
    int nYeux = 0, nOreilles = 0;

    // Parcours de toutes les bestioles pour compter leurs accessoires
    for (auto b : listeBestioles) {
        for (auto acc : b->getAccessoires()) {
            switch (acc->getType()) {
                case NAGEOIRES:   nNageoires++;   break;
                case CARAPACE:    nCarapaces++;   break;
                case CAMOUFLAGE:  nCamouflages++; break;
            }
        }

        // Compte les bestioles avec yeux et oreilles
        if (b->possedeYeux()) {
            nYeux++;
        }

        if (b->possedeOreilles()) {
            nOreilles++;
        }
    }

    // Affichage des statistiques
    cout << "Nombre de bestioles avec nageoires : " << nNageoires << endl;
    cout << "Nombre de bestioles avec carapaces : " << nCarapaces << endl;
    cout << "Nombre de bestioles avec camouflage : " << nCamouflages << endl;
    cout << "Nombre de bestioles avec yeux : " << nYeux << endl;
    cout << "Nombre de bestioles avec oreilles : " << nOreilles << endl;
}

// Bascule l'affichage du champ de vision
void Milieu::toggleFieldOfView() {
    showFieldOfView = !showFieldOfView;
}

// Retourne l'état actuel de l'affichage du champ de vision
bool Milieu::getShowFieldOfView() const {
    return showFieldOfView;
}

// Gestion des collisions entre bestioles
void Milieu::gererCollisions() {
    for (auto it1 = listeBestioles.begin(); it1 != listeBestioles.end(); ) {
        bool it1Died = false;

        for (auto it2 = listeBestioles.begin(); it2 != listeBestioles.end(); ) {
            // Évite de comparer une bestiole à elle-même
            if (*it1 != *it2) {
                // Calcul de la distance entre les bestioles
                double dist = std::sqrt(
                    ((*it1)->getX() - (*it2)->getX()) * ((*it1)->getX() - (*it2)->getX()) +
                    ((*it1)->getY() - (*it2)->getY()) * ((*it1)->getY() - (*it2)->getY())
                );

                // Collision si la distance est inférieure à la taille d'affichage
                if (dist < Configuration::AFF_SIZE) {
                    // Probabilité de survie de base
                    double probaBase = Configuration::SURVIVE_COLLISION;
                    double proba1 = (*it1)->getResistanceCollision(probaBase);
                    double proba2 = (*it2)->getResistanceCollision(probaBase);

                    // Détermination de la survie par un tirage aléatoire
                    bool it1Survives = (std::rand() % 100) < proba1 * 100;
                    bool it2Survives = (std::rand() % 100) < proba2 * 100;

                    // Gestion de la mort de la première bestiole
                    if (!it1Survives) {
                        it1Died = true;
                        break;
                    }

                    // Gestion de la mort de la deuxième bestiole
                    if (!it2Survives) {
                        delete *it2;
                        it2 = listeBestioles.erase(it2);
                        continue;
                    }

                    // Calcul du rebond lors de la collision
                    double dx = (*it2)->getX() - (*it1)->getX();
                    double dy = (*it2)->getY() - (*it1)->getY();
                    double collisionAngle = std::atan2(-dy, dx);

                    // Changement de l'orientation des bestioles
                    double newOri1 = 2 * collisionAngle - (*it1)->getOrientation();
                    double newOri2 = 2 * collisionAngle - (*it2)->getOrientation();

                    (*it1)->changeOrientation(newOri1);
                    (*it2)->changeOrientation(newOri2);

                    // Séparation des bestioles après collision
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

        // Suppression de la bestiole si elle meurt
        if (it1Died) {
            delete *it1;
            it1 = listeBestioles.erase(it1);
        } else {
            ++it1;
        }
    }
}

// Gestion des événements naturels (naissances, clonages)
void Milieu::processNaturalEvents() {
    // Création d'une fabrique de bestioles
    BestioleFactory* factory = new BestioleFactory();

    // Génération spontanée de nouvelles bestioles
    if ((std::rand() % 1000) < (Configuration::GENERATION_RATE * 10)) {
        std::unique_ptr<IBestiole> b = factory->createBestioleWithRandomBestiole();
        b->initCoords(width, height);
        std::cout << "Nouvelle bestiole née!" << std::endl;
        addMember(b.release());
    }

    // Clonage des bestioles existantes
    for (IBestiole* bestiole : listeBestioles) {
        if ((std::rand() % 1000) < (Configuration::CLONE_RATE * 10)) {
            std::unique_ptr<IBestiole> clone = factory->cloneBestiole(*bestiole);
            clone->initCoords(width, height);
            listeBestioles.push_back(clone.release());
            std::cout << "Bestiole clonée!" << std::endl;
        }
    }

    // Libération de la fabrique
    delete factory;
}