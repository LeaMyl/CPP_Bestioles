// ComportementPrevoyant.cpp
#include "ComportementPrevoyant.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <cmath>
#include <vector>
#include <limits>

// Constructeur par défaut
ComportementPrevoyant::ComportementPrevoyant() {
    std::cout << "Constructeur ComportementPrevoyant" << std::endl;
}

// Destructeur
ComportementPrevoyant::~ComportementPrevoyant() {
    std::cout << "Destructeur ComportementPrevoyant" << std::endl;
}

// Implémentation de calculerNouvelleDirection
double ComportementPrevoyant::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    if (voisines.empty()) {
        return bestiole.getOrientation();
    }

    // Vérifier les collisions potentielles avec les bestioles voisines
    double tempsCollisionMin = std::numeric_limits<double>::max();
    double angleEvitement = bestiole.getOrientation();
    bool collisionDetectee = false;

    for (const auto& voisine : voisines) {
        double tempsCollision;
        double angleEvitementLocal;
        
        if (detecterCollisionPotentielle(bestiole, *voisine, tempsCollision, angleEvitementLocal)) {
            if (tempsCollision < tempsCollisionMin) {
                tempsCollisionMin = tempsCollision;
                angleEvitement = angleEvitementLocal;
                collisionDetectee = true;
            }
        }
    }

    if (collisionDetectee) {
        return angleEvitement;
    }
    
    return bestiole.getOrientation();
}

// Implémentation de getCouleur
std::array<int, 3> ComportementPrevoyant::getCouleur() const {
    return {0, 128, 0}; // Couleur verte pour le comportement prévoyant
}

// Implémentation de clone
IComportement* ComportementPrevoyant::clone() const {
    return new ComportementPrevoyant(*this);
}

// Méthode pour prédire les collisions potentielles
bool ComportementPrevoyant::detecterCollisionPotentielle(const Bestiole& bestiole, const IBestiole& autre, 
                                                        double& tempsCollision, double& angleEvitement) const {
    // Position et vélocité de la bestiole actuelle
    auto pos1 = bestiole.getPosition();
    double x1 = pos1.first;
    double y1 = pos1.second;
    double vx1 = bestiole.getVitesse() * cos(bestiole.getOrientation());
    double vy1 = bestiole.getVitesse() * sin(bestiole.getOrientation());
    
    // Position et vélocité de l'autre bestiole
    auto pos2 = autre.getPosition();
    double x2 = pos2.first;
    double y2 = pos2.second;
    double vx2 = autre.getVitesse() * cos(autre.getOrientation());
    double vy2 = autre.getVitesse() * sin(autre.getOrientation());
    
    // Calculer les vitesses relatives
    double dvx = vx2 - vx1;
    double dvy = vy2 - vy1;
    double dx = x2 - x1;
    double dy = y2 - y1;
    
    // Somme des rayons (utiliser getSize depuis IBestiole)
    double sumRadius = bestiole.getSize() / 2.0 + autre.getSize() / 2.0;
    
    // Calculer les coefficients de l'équation quadratique
    double a = dvx * dvx + dvy * dvy;
    if (a < 0.0001) return false; // Les bestioles se déplacent parallèlement
    
    double b = 2 * (dx * dvx + dy * dvy);
    double c = dx * dx + dy * dy - sumRadius * sumRadius;
    
    // Calculer le discriminant
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false; // Pas d'intersection
    
    // Calculer les temps de collision potentiels
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    
    // Vérifier si la collision se produira dans le futur
    if (t1 <= 0 && t2 <= 0) return false;
    
    // Prendre le premier temps de collision positif
    tempsCollision = (t1 > 0) ? t1 : t2;
    
    // Si la collision est trop lointaine, l'ignorer
    if (tempsCollision > 20) return false;
    
    // Calculer l'angle pour éviter la collision
    // Calculer le vecteur normal à la collision
    double xCollision = x1 + vx1 * tempsCollision;
    double yCollision = y1 + vy1 * tempsCollision;
    double xOther = x2 + vx2 * tempsCollision;
    double yOther = y2 + vy2 * tempsCollision;
    
    // Vecteur allant de la position de collision à la position de l'autre
    double nx = xOther - xCollision;
    double ny = yOther - yCollision;
    
    // Normaliser le vecteur
    double norm = sqrt(nx * nx + ny * ny);
    if (norm > 0) {
        nx /= norm;
        ny /= norm;
    }
    
    // Calculer l'angle d'évitement (perpendiculaire au vecteur normal)
    // Choisir aléatoirement l'une des deux directions perpendiculaires possibles
    bool direction = (rand() % 2 == 0);
    if (direction) {
        angleEvitement = atan2(-nx, ny);  // Tourner à 90 degrés dans un sens
    } else {
        angleEvitement = atan2(nx, -ny);  // Tourner à 90 degrés dans l'autre sens
    }
    
    return true;
}