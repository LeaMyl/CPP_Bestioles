// Bestiole.cpp
#include "Bestiole.h"
#include "Milieu.h"
#include "Configuration.h"
#include "Yeux.h"
#include "Oreilles.h"
#include <cstdlib>
#include <cmath>


#include "IBestiole.h"
#include "IAccessoire.h"
#include "ICapteur.h"
#include <vector>
#include <memory>

int Bestiole::next = 0;

Bestiole::Bestiole( int ageLimi, double vitess_init)
{
    identite = ++next;
    age = 0;
    
     

    ageLimite = ageLimi;
     cout << "const Bestiole (" << identite << ") par defaut" << endl;
 
     x = y = 0;
     cumulX = cumulY = 0.;
     orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
     vitesse = vitess_init;
 

    couleur = new T[3];
    couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    
    // Si un comportement est défini, utiliser sa couleur
    if (comportement != nullptr) {
        auto comportementCouleur = comportement->getCouleur();
        couleur[0] = comportementCouleur[0];
        couleur[1] = comportementCouleur[1];
        couleur[2] = comportementCouleur[2];
    }
}


Bestiole::Bestiole(const Bestiole& b)
{
    identite = ++next;
    age = 0;
    ageLimite = b.ageLimite;

    cout << "const Bestiole (" << identite << ") par copie" << endl;

    x = b.x;
    y = b.y;
    cumulX = cumulY = 0.;
    orientation = b.orientation;
    vitesse = b.vitesse;
    
    couleur = new T[3];
    memcpy(couleur, b.couleur, 3 * sizeof(T));
    
    // Copie des capteurs
    for (const auto& capteur : b.capteurs) {
        capteurs.push_back(std::unique_ptr<ICapteur>(capteur->clone()));
    }
    
    // Copie des accessoires
    for (const auto& accessoire : b.accessoires) {
        accessoires.push_back(accessoire->clone());
    }
    
    // Copie du comportement
    if (b.comportement != nullptr) {
        comportement = b.comportement->clone();
    } else {
        comportement = nullptr;
    }
}

Bestiole::~Bestiole()
{
    delete[] couleur;
    
    // Libération des capteurs : // Pas besoin de libérer manuellement les capteurs, unique_ptr s'en charge
    //for (auto& capteur : capteurs) {
        //delete capteur;
    //}
    
    // Libération des accessoires
    for (auto& accessoire : accessoires) {
        delete accessoire;
    }
    
    // Libération du comportement
    if (comportement != nullptr) {
        delete comportement;
    }

    cout << "dest Bestiole (" << identite << ") par defaut" << endl;;
}

void Bestiole::initCoords(int xLim, int yLim)
{
    x = rand() % xLim;
    y = rand() % yLim;
}

void Bestiole::bouge(int xLim, int yLim)
{
    double nx, ny;
    double dx = cos(orientation) * vitesse;
    double dy = -sin(orientation) * vitesse;
    int cx, cy;

    cx = static_cast<int>(cumulX); cumulX -= cx;
    cy = static_cast<int>(cumulY); cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;

    if ((nx < 0) || (nx > xLim - 1)) {
        orientation = M_PI - orientation;
        cumulX = 0.;
    }
    else {
        x = static_cast<int>(nx);
        cx = static_cast<int>(nx);
        cumulX += nx - x;
    }

    if ((ny < 0) || (ny > yLim - 1)) {
        orientation = -orientation;
        cumulY = 0.;
    }
    else {
        y = static_cast<int>(ny);
        cumulY += ny - y;
    }
}

void Bestiole::action(Milieu& monMilieu)
{
    // Appliquer le comportement si présent
    if (comportement != nullptr) {
        double nouvelleOrientation = comportement->calculerNouvelleDirection(*this, monMilieu);
        changeOrientation(nouvelleOrientation);
    }
    
    // Appliquer les accessoires sur la vitesse
    double vitesseModifiee = vitesse;
    for (const auto& accessoire : accessoires) {
        vitesseModifiee = accessoire->modulerVitesse(vitesseModifiee);
    }
    
    // Sauvegarder l'ancienne vitesse
    double ancienneVitesse = vitesse;
    vitesse = vitesseModifiee;
    
    // Déplacer la bestiole
    bouge(monMilieu.getWidth(), monMilieu.getHeight());
    
    // Restaurer la vitesse d'origine
    vitesse = ancienneVitesse;
    
    // Vieillir la bestiole
    vieillir();
}




void Bestiole::draw(UImg &support) {
    Configuration* config;
    double xt = x + cos(orientation) * config->AFF_SIZE / 2.1;
    double yt = y - sin(orientation) * config->AFF_SIZE / 2.1;
    
    int couleur_vue[3] = {255, 0, 0};  // Rouge pour la vision
    int couleur_ecoute[3] = {0, 0, 255}; // Bleu pour l'écoute
    float alpha_vue = 0.3f;   // Transparence 30% pour la vision
    float alpha_ecoute = 0.2f;// Transparence 20% pour l'écoute

    for (const auto& capteur : capteurs) {
        // Essayer de convertir le capteur en Yeux
        if (auto yeux = dynamic_cast<Yeux*>(capteur.get())) {
            // Le capteur est de type Yeux
            double angle = yeux->angle;  // Récupérer l'angle de vision
            double dist = yeux->dist;    // Récupérer la distance de détection
    

              // Dessin du cône de vision en utilisant un polygone triangulaire
            double angle1 = orientation - angle / 2;
            double angle2 = orientation + angle / 2;
            double x1 = x + cos(angle1) * dist;
            double y1 = y - sin(angle1) * dist;
            double x2 = x + cos(angle2) * dist;
            double y2 = y - sin(angle2) * dist;
        
            CImg<int> points(3, 2);  // Création d'un tableau pour les points du triangle
            points(0,0) = x; points(0,1) = y;
            points(1,0) = x1; points(1,1) = y1;
            points(2,0) = x2; points(2,1) = y2;
        
            support.draw_polygon(points, couleur_vue, alpha_vue);
        }
        // Essayer de convertir le capteur en Oreilles
        else if (auto oreilles = dynamic_cast<Oreilles*>(capteur.get())) {

            // Le capteur est de type Oreilles
            double dist = oreilles->dist;  // Récupérer la distance de détection

            // Dessin du cercle d'écoute avec transparence
            support.draw_circle(x, y, dist, couleur_ecoute, alpha_ecoute);
    
        }
        else {
            // Le capteur est d'un autre type (non géré)
            std::cout << "Capteur inconnu" << std::endl;
        }
    }


    // Dessiner le corps de base (forme ronde pour noiraude)
   double corps_taille = Configuration::AFF_SIZE; // Corps principal
   
   // Dessiner le corps principal de la noiraude (rond et noir)
   support.draw_circle(x, y, corps_taille / 2, couleur);

    // Variables pour déterminer si la bestiole a certains accessoires
    bool has_carapace = false;
    bool has_nageoires = false;
    bool has_camouflage = false;

    // Vérifier quels accessoires sont présents
    for (auto acc : accessoires) {
        switch(acc->getType()) {
            case 1: has_nageoires = true; break;
            case 2: has_carapace = true; break;
            case 3: has_camouflage = true; break;
        }
    }

    // Si la bestiole a un camouflage, ajouter une cape derrière elle
    if (has_camouflage) {
        // Couleur verte semi-transparente pour la cape
        int cape_color[3] = {20, 150, 50};
        
        // Points pour la cape (forme triangulaire derrière la bestiole)
        CImg<int> cape_points(3, 2);
        cape_points(0,0) = x;
        cape_points(0,1) = y;
        
        double cape_width = corps_taille * 1.5;
        double cape_length = corps_taille * 2;
        
        cape_points(1,0) = x - cape_length * cos(orientation) + cape_width/2 * cos(orientation + M_PI/2);
        cape_points(1,1) = y + cape_length * sin(orientation) - cape_width/2 * sin(orientation + M_PI/2);
        
        cape_points(2,0) = x - cape_length * cos(orientation) - cape_width/2 * cos(orientation + M_PI/2);
        cape_points(2,1) = y + cape_length * sin(orientation) + cape_width/2 * sin(orientation + M_PI/2);
        
        // Dessiner la cape avec transparence (0.6 = 60% d'opacité)
        support.draw_polygon(cape_points, cape_color, 0.6);
    }
    
    // Si la bestiole a une carapace, dessiner une carapace bleue de Mario Kart
    if (has_carapace) {
        // Couleur bleue pour la carapace de Mario Kart
        int carapace_color[3] = {255, 255, 0}; // jaune vif 
        
        // Taille légèrement plus petite que le corps pour être visible
        double carapace_size = corps_taille * 0.8;
        
        // Dessiner la carapace comme un ovale sur le dos
        support.draw_circle(x, y, corps_taille, carapace_color,0.5);
    }
 
    // Re-dessiner le corps après la cape pour que la cape et la carapace soient derrière
   support.draw_circle(x, y, corps_taille / 2, couleur);
    // Si la bestiole a des nageoires, dessiner 4 palmes transparentes
    if (has_nageoires) {
        // Couleur pour les palmes (bleu clair semi-transparent)
        int palme_color[3] = {100, 200, 255};
        
        // Dessiner 4 palmes à différents angles autour du corps
        for (int i = 0; i < 4; i++) {
            double palme_angle = orientation + i * (M_PI / 2);
            double palme_length = corps_taille * 0.7;
            double palme_width = corps_taille * 0.3;
            
            // Point d'attache de la palme
            double palme_base_x = x + (corps_taille/2 - palme_width*0.1) * cos(palme_angle);
            double palme_base_y = y - (corps_taille/2 - palme_width*0.1) * sin(palme_angle);
            
            // Extrémité de la palme
            double palme_tip_x = palme_base_x + palme_length * cos(palme_angle);
            double palme_tip_y = palme_base_y - palme_length * sin(palme_angle);
            
            // Points pour la palme (forme ovale/rectangulaire arrondie)
            double perp_angle = palme_angle + M_PI/2;
            
            // Dessiner une ligne pour la tige de la palme
            support.draw_line(
                palme_base_x, 
                palme_base_y,
                palme_tip_x,
                palme_tip_y,
                palme_color, 
                0.8 // Transparence
            );
            
            // Dessiner une forme ovale pour la partie large de la palme
            double ellipse_center_x = palme_base_x + (palme_length * 0.7) * cos(palme_angle);
            double ellipse_center_y = palme_base_y - (palme_length * 0.7) * sin(palme_angle);
            
            support.draw_ellipse(
                ellipse_center_x, 
                ellipse_center_y,
                palme_width, 
                palme_width / 2,
                -palme_angle / M_PI * 180.,
                palme_color, 
                0.5 // Transparence de 50%
            );
        }
    }
    // Dessin de la bestiole
    //support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5., -orientation / M_PI * 180., couleur);
    //support.draw_circle(xt, yt, AFF_SIZE / 2., couleur);

    // Ajouter les yeux à la noiraude
   double eye_distance = corps_taille * 0.25;
   double eye_size = corps_taille * 0.12;
   double eye_offset_angle = orientation + M_PI/4;
   
   int eye_color[3] = {255, 255, 255}; // Blanc pour les yeux
   int pupil_color[3] = {0, 0, 0}; // Noir pour les pupilles
   
   // Œil gauche
   double left_eye_x = x + eye_distance * cos(eye_offset_angle);
   double left_eye_y = y - eye_distance * sin(eye_offset_angle);
   support.draw_circle(left_eye_x, left_eye_y, eye_size, eye_color);
   support.draw_circle(left_eye_x, left_eye_y, eye_size*0.6, pupil_color);
   
   // Œil droit
   double right_eye_x = x + eye_distance * cos(eye_offset_angle + M_PI/2);
   double right_eye_y = y - eye_distance * sin(eye_offset_angle + M_PI/2);
   support.draw_circle(right_eye_x, right_eye_y, eye_size, eye_color);
   support.draw_circle(right_eye_x, right_eye_y, eye_size*0.6, pupil_color);

 }

bool Bestiole::jeTeVois(const IBestiole& b) const
{
    return detecte(b) && estDetectee(b);
    
}

bool Bestiole::detecte(const IBestiole& autre) const
{
    //std::cout << "detecte() appelé pour Bestiole " << identite << " avec " << capteurs.size() << " capteurs" << std::endl;
    
    if (capteurs.empty()) {
        std::cout << "Aucun capteur trouvé pour Bestiole " << identite << std::endl;
        // Your default detection logic here
        /*
        auto pos = autre.getPosition();
        double dist = std::sqrt((x - pos.first) * (x - pos.first) + (y - pos.second) * (y - pos.second));
        return (dist <= 100);
        */
    }
    
    // Otherwise, use capteurs
    for (const auto& capteur : capteurs) {
        if (capteur->detecte(*this, autre)) {
            //std::cout << "Bestiole " << identite << " détecte avec un capteur" << std::endl;
            return true;
        }
    }
    
    return false;
}

bool Bestiole::estDetectee(const IBestiole& autre) const
{
    // Calcul de la probabilité de détection en fonction du camouflage
    double coeff = getCoeffCamouflage();
    double proba = static_cast<double>(rand()) / RAND_MAX;
    
    return proba <= coeff;
}

double Bestiole::getCoeffCamouflage() const
{
    double coeff = 1.0; // Par défaut, pas de camouflage
    
    for (const auto& accessoire : accessoires) {
        double coeff_accessoire = accessoire->getCoeffCamoufflage();
        if (coeff_accessoire < coeff) {
            coeff = coeff_accessoire;
        }
    }
    
    return coeff;
}

double Bestiole::getResistanceCollision(double probaBase) const {
    double resistance = probaBase;
    for (const auto& accessoire : accessoires) {
        resistance = accessoire->modulerResistance(resistance);
    }
    return resistance;
}

void Bestiole::changeOrientation(double nouvelleOrientation)
{
    this->orientation = nouvelleOrientation;
    
    // Normaliser l'orientation entre 0 et 2π
    while (orientation < 0) orientation += 2 * M_PI;
    while (orientation >= 2 * M_PI) orientation -= 2 * M_PI;
}

void Bestiole::vieillir()
{
    age++;
}

bool Bestiole::meurt()
{
    return age >= ageLimite;
}

IBestiole* Bestiole::clone() const {
    return new Bestiole(*this);
}


void Bestiole::ajouterCapteur(std::unique_ptr<ICapteur> capteur) 
{
    
    //std::cout << "AVANT: Bestiole " << identite << " a " << capteurs.size() << " capteurs" << std::endl;
    capteurs.push_back(std::move(capteur));
    //std::cout << "APRES: Bestiole " << identite << " a " << capteurs.size() << " capteurs" << std::endl;

}

void Bestiole::ajouterAccessoire(IAccessoire* accessoire) {
    if (accessoire) {
        // Créer une copie de l'accessoire en utilisant la méthode clone
        accessoires.push_back(accessoire->clone());
        
        // Mettre à jour la vitesse en fonction de tous les accessoires
        for (auto acc : accessoires) {
            vitesse = acc->modulerVitesse(vitesse);
        }
    }
 }

void Bestiole::setComportement(IComportement* comp)
{
    if (comportement != nullptr) {
        delete comportement;
    }
    comportement = comp;
    // Assigner la couleur en fonction du comportement
    auto couleurComportement = comportement->getCouleur();
    couleur[0] = couleurComportement[0];
    couleur[1] = couleurComportement[1];
    couleur[2] = couleurComportement[2];
}

bool operator==(const Bestiole& b1, const Bestiole& b2)
{
    return (b1.identite == b2.identite);
}

void Bestiole::setVitesse(double nouvelleVitesse) {
    vitesse = nouvelleVitesse;
}

const std::vector<IAccessoire*>& Bestiole::getAccessoires() const {
    return accessoires;
 }

 bool Bestiole::possedeYeux() const {
    for (const auto& capteur : capteurs) {
        if (dynamic_cast<Yeux*>(capteur.get())) {
            return true;
        }
    }
    return false;
}

bool Bestiole::possedeOreilles() const{
    for (const auto& capteur : capteurs) {
        if (dynamic_cast<Oreilles*>(capteur.get())) {
            return true;
        }
    }
    return false;
}

int Bestiole::getX() const {
    return x;
}

int Bestiole::getY() const {
    return y;
}

void Bestiole::setX(int x) {
    this->x = x;
}

void Bestiole::setY(int y)  {
    this->y = y;
}

std::pair<int, int> Bestiole::getPosition() const {
    return std::make_pair(x, y);
}

double Bestiole::getSize() const {
    return Configuration::AFF_SIZE;  // Or whatever size you want to return
}

double Bestiole::getVitesse() const {
    return vitesse;
}

double Bestiole::getOrientation() const {
    return orientation;
}