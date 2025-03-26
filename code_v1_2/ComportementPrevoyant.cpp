#include "ComportementPrevoyant.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <cmath>
#include <vector>
#include <limits>

// Constructeur par défaut
ComportementPrevoyant::ComportementPrevoyant() {
    std::cout << "Constructeur de comportement prévoyant" << std::endl;
}

// Destructeur
ComportementPrevoyant::~ComportementPrevoyant() {
    std::cout << "Destructeur de comportement prévoyant" << std::endl;
}

// Calculer la nouvelle direction basée sur le comportement prévoyant
double ComportementPrevoyant::calculerNouvelleDirection(Bestiole& bestiole, const Milieu& milieu) {
    // Détecter les bestioles voisines
    std::vector<const IBestiole*> voisines = milieu.detecteBestiolesVoisines(bestiole);
    
    // Si aucune bestiole voisine, conserver la direction actuelle
    if (voisines.empty()) {
        return bestiole.getOrientation();
    }

    // Variables pour stocker les informations de collision
    double tempsCollisionMin = std::numeric_limits<double>::max();
    double angleEvitement = bestiole.getOrientation();
    bool collisionDetectee = false;

    // Vérifier les collisions potentielles avec chaque bestiole voisine
    for (const auto& voisine : voisines) {
        double tempsCollision;
        double angleEvitementLocal;
        
        if (detecterCollisionPotentielle(bestiole, *voisine, tempsCollision, angleEvitementLocal)) {
            // Mettre à jour l'angle d'évitement si une collision plus proche est détectée
            if (tempsCollision < tempsCollisionMin) {
                tempsCollisionMin = tempsCollision;
                angleEvitement = angleEvitementLocal;
                collisionDetectee = true;
            }
        }
    }

    // Retourner l'angle d'évitement si une collision est détectée
    if (collisionDetectee) {
        return angleEvitement;
    }
    
    // Sinon, conserver la direction actuelle
    return bestiole.getOrientation();
}

// Retourne la couleur associée au comportement prévoyant (vert)
std::array<int, 3> ComportementPrevoyant::getCouleur() const {
    return {0, 128, 0}; // Vert
}

// Créer un clone du comportement
IComportement* ComportementPrevoyant::clone() const {
    return new ComportementPrevoyant(*this);
}

// Détecter les collisions potentielles
bool ComportementPrevoyant::detecterCollisionPotentielle(const Bestiole& bestiole, const IBestiole& autre, 
                                                        double& tempsCollision, double& angleEvitement) const {
    // Récupérer les positions et vélocités des bestioles
    auto pos1 = bestiole.getPosition();
    double x1 = pos1.first, y1 = pos1.second;
    double vx1 = bestiole.getVitesse() * cos(bestiole.getOrientation());
    double vy1 = bestiole.getVitesse() * sin(bestiole.getOrientation());
    
    auto pos2 = autre.getPosition();
    double x2 = pos2.first, y2 = pos2.second;
    double vx2 = autre.getVitesse() * cos(autre.getOrientation());
    double vy2 = autre.getVitesse() * sin(autre.getOrientation());
    
    // Calculer les vitesses et positions relatives
    double dvx = vx2 - vx1;
    double dvy = vy2 - vy1;
    double dx = x2 - x1;
    double dy = y2 - y1;
    
    // Calculer la somme des rayons des bestioles
    double sumRadius = bestiole.getSize() / 2.0 + autre.getSize() / 2.0;
    
    // Résoudre l'équation quadratique pour détecter la collision
    double a = dvx * dvx + dvy * dvy;
    if (a < 0.0001) return false; // Mouvement parallèle
    
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
    
    // Ignorer les collisions trop lointaines
    if (tempsCollision > 20) return false;
    
    // Calculer le point de collision
    double xCollision = x1 + vx1 * tempsCollision;
    double yCollision = y1 + vy1 * tempsCollision;
    double xOther = x2 + vx2 * tempsCollision;
    double yOther = y2 + vy2 * tempsCollision;
    
    // Calculer le vecteur normal à la collision
    double nx = xOther - xCollision;
    double ny = yOther - yCollision;
    
    // Normaliser le vecteur
    double norm = sqrt(nx * nx + ny * ny);
    if (norm > 0) {
        nx /= norm;
        ny /= norm;
    }
    
    // Calculer l'angle d'évitement (perpendiculaire au vecteur normal)
    // Choix aléatoire de la direction perpendiculaire
    bool direction = (rand() % 2 == 0);
    if (direction) {
        angleEvitement = atan2(-nx, ny);  // Tourner à 90 degrés
    } else {
        angleEvitement = atan2(nx, -ny);  // Tourner à 90 degrés dans l'autre sens
    }
    
    return true;
}