#include "Bestiole.h"

#include "Milieu.h"

#include <cstdlib>
#include <cmath>

int               Bestiole::next = 0;

ParametresBestioles::ParametresBestioles(){}
ParametresBestioles::~ParametresBestioles(){}
void ParametresBestioles::PushWith(string key, Dictionnaire_Parametres& pd){
    pd.emplace(make_pair(key,this));
}


Bestiole::Bestiole( void ) {
   identite = ++next;
   // cout << "const Bestiole (" << identite << ") par defaut" << endl;
   x = y = 0;
   cumulX = cumulY = 0.;

   GAMMA_O = Configuration::MIN_GAMMA_O;
   GAMMA_Y = Configuration::MIN_GAMMA_Y;
   ALPHA = Configuration::MIN_ALPHA;
   DELTA_O = Configuration::MIN_DELTA_O;
   DELTA_Y = Configuration::MIN_DELTA_Y;

   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   baseVitesse = static_cast<double>( rand() )/RAND_MAX*Configuration::MAX_VITESSE;
   vitesse = baseVitesse; // Initialement, aucun modificateur appliqué
   couleur = new T[ 3 ];
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   
   // Initialiser l'âge
   age = 0;
   ageLimite = rand() % 1000 + 500; // Limite d'âge aléatoire entre 500 et 1500 étapes
}
 
Bestiole::Bestiole(const Bestiole & b) {
   identite = ++next;
   // cout << "const Bestiole (" << identite << ") par copie" << endl;
   x = b.x;
   y = b.y;
   cumulX = cumulY = 0.;
   orientation = b.orientation;
   baseVitesse = b.baseVitesse;
   vitesse = b.vitesse;
   couleur = new T[3];
   memcpy(couleur, b.couleur, 3*sizeof(T));
   
   age = b.age;
   ageLimite = b.ageLimite;
   
   // Cloner tous les accessoires
   for (auto acc : b.accessoires) {
       accessoires.push_back(acc->clone());
   }
   
   // Cloner tous les capteurs
   for (auto capteur : b.capteurs) {
       capteurs.push_back(capteur->clone());
   }
}
 
Bestiole::~Bestiole(void) {
   delete[] couleur;
   
   // Supprimer tous les accessoires
   for (auto acc : accessoires) {
       delete acc;
   }
   accessoires.clear();
   
   // Supprimer tous les capteurs
   for (auto capteur : capteurs) {
       delete capteur;
   }
   capteurs.clear();
   
   // cout << "dest Bestiole" << endl;
}


void Bestiole::initCoords( int xLim, int yLim )
{
   x = rand() % xLim;
   y = rand() % yLim;
}


void Bestiole::bouge( int xLim, int yLim )
{
   double         nx, ny;
   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;
   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;
   nx = x + dx + cx;
   ny = y + dy + cy;
   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );
      cumulX += nx - x;
   }
   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );
      cumulY += ny - y;
   }
}


void Bestiole::action( Milieu & monMilieu )
{
   bouge( monMilieu.getWidth(), monMilieu.getHeight() );
}


bool operator==( const Bestiole & b1, const Bestiole & b2 )
{
   return ( b1.identite == b2.identite );
}


bool Bestiole::jeTeVois( const Bestiole & b ) const
{
   double         dist;
   dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( dist <= DELTA_Y );
}

paire_t Bestiole::getCoords() const
{
   paire_t res;
   res.x = x;
   res.y = y;
   res.ori = orientation;
   res.vite = vitesse;
   return res;
}

void Bestiole::setCoords(paire_t coords)
{
   x = coords.x;
   y = coords.y;
   orientation = coords.ori;
   vitesse = coords.vite;
}

// Ajouter ces méthodes à Bestiole.cpp

void Bestiole::ajouterAccessoire(IAccessoire* accessoire) {
   if (accessoire) {
       // Créer une copie de l'accessoire en utilisant la méthode clone
       accessoires.push_back(accessoire->clone());
       
       // Mettre à jour la vitesse en fonction de tous les accessoires
       vitesse = baseVitesse;
       for (auto acc : accessoires) {
           vitesse = acc->modulerVitesse(vitesse);
       }
   }
}

double Bestiole::getVitesse() const {
   return vitesse;
}

double Bestiole::getBaseVitesse() const {
   return baseVitesse;
}

void Bestiole::setVitesse(double v) {
   baseVitesse = v;
   
   // Appliquer tous les modificateurs d'accessoires
   vitesse = baseVitesse;
   for (auto acc : accessoires) {
       vitesse = acc->modulerVitesse(vitesse);
   }
}

double Bestiole::getOrientation() const {
   return orientation;
}

double Bestiole::getResistanceCollision(double probaBase) const {
   double proba = probaBase;
   
   // Appliquer tous les modificateurs d'accessoires
   for (auto acc : accessoires) {
       proba = acc->modulerResistance(proba);
   }
   return proba;
}

double Bestiole::getCoeffCamoufflage() const {
   double coeff = 0.0; // Pas de camouflage par défaut
   
   // Trouver le coefficient de camouflage maximum parmi tous les accessoires
   for (auto acc : accessoires) {
       double accCoeff = acc->getCoeffCamoufflage();
       if (accCoeff > coeff) {
           coeff = accCoeff;
       }
   }
   return coeff;
}

bool Bestiole::possedeAccessoire(int typeAccessoire) const {
   for (auto acc : accessoires) {
       if (acc->getType() == typeAccessoire) {
           return true;
       }
   }
   return false;
}

const std::vector<IAccessoire*>& Bestiole::getAccessoires() const {
   return accessoires;
}



// Méthodes d'âge et de mort
void Bestiole::vieillir() {
   age++;
}

bool Bestiole::meurt() const {
   return age >= ageLimite;
}

// Mettre à jour la méthode draw pour afficher les accessoires
void Bestiole::draw(UImg &support) {
   double xt = x + cos(orientation) * Configuration::AFF_SIZE / 2.1;
   double yt = y - sin(orientation) * Configuration::AFF_SIZE / 2.1;
   int couleur_vue[3] = {255, 0, 0}; // Rouge pour la vision
   int couleur_ecoute[3] = {0, 0, 255}; // Bleu pour l'écoute
   float alpha_vue = 0.5f; // Transparence 50% pour la vision
   float alpha_ecoute = 0.4f; // Transparence 40% pour l'écoute
   bool showFields = Milieu::showFieldOfView;
   double LIMITE_VUE = DELTA_Y;
   double LIMITE_OUIE = DELTA_O;
   std::cout<<"LIMITE_VUE : "<<LIMITE_VUE<<std::endl;
   std::cout<<"LIMITE_OUIE : "<<LIMITE_OUIE<<std::endl;

   if (showFields) {
      // Dessiner les capteurs
      double angle1 = orientation - ALPHA / 2;
      double angle2 = orientation + ALPHA / 2;
      double x1 = x + cos(angle1) * LIMITE_VUE;
      double y1 = y - sin(angle1) * LIMITE_VUE;
      double x2 = x + cos(angle2) * LIMITE_VUE;
      double y2 = y - sin(angle2) * LIMITE_VUE;
      CImg<int> points(3, 2); // Création d'un tableau pour les points du triangle
      points(0,0) = x; points(0,1) = y;
      points(1,0) = x1; points(1,1) = y1;
      points(2,0) = x2; points(2,1) = y2;
      support.draw_polygon(points, couleur_vue, alpha_vue);
      support.draw_circle(x, y, LIMITE_OUIE, couleur_ecoute, alpha_ecoute);
   }

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

   // Couleur noire pour la noiraude (Soot sprite)
   int noiraude_color[3] = {20, 20, 20}; // Presque noir
   
   // Dessiner le corps de base (forme ronde pour noiraude)
   double corps_taille = Configuration::AFF_SIZE; // Corps principal
   
   // Dessiner le corps principal de la noiraude (rond et noir)
   support.draw_circle(x, y, corps_taille / 2, noiraude_color);
   
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
   support.draw_circle(x, y, corps_taille / 2, noiraude_color);
   
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


Bestiole& Bestiole::operator=(const Bestiole& b) {
   if (this != &b) {
       // Free existing resources
       delete[] couleur;
       for (auto acc : accessoires) {
           delete acc;
       }
       accessoires.clear();
       
       for (auto capteur : capteurs) {
           delete capteur;
       }
       capteurs.clear();
       
       // Copy new resources
       x = b.x;
       y = b.y;
       cumulX = b.cumulX;
       cumulY = b.cumulY;
       orientation = b.orientation;
       baseVitesse = b.baseVitesse;
       vitesse = b.vitesse;
       
       couleur = new T[3];
       memcpy(couleur, b.couleur, 3*sizeof(T));
       
       age = b.age;
       ageLimite = b.ageLimite;
       
       // Clone accessories
       for (auto acc : b.accessoires) {
           if (acc) accessoires.push_back(acc->clone());
       }
       
       // Clone sensors
       for (auto capteur : b.capteurs) {
           if (capteur) capteurs.push_back(capteur->clone());
       }
   }
   return *this;
}

void Bestiole::ajouterCapteur(ICapteur* capteur) {
   if (capteur) {
       capteurs.push_back(capteur->clone());
   }
    
    for (auto capteur : capteurs) {
        // Mettre à jour les propriétés de vision
        if (capteur->getType() == 1) { // 1 for Eye
            Yeux* yeux = dynamic_cast<Yeux*>(capteur);
            std::cout<<"Test Yeux"<<std::endl;
            if (yeux) {
                // Mettre à jour les propriétés de vision
                DELTA_Y = yeux->getDelta();
                GAMMA_Y = yeux->getGamma();
                ALPHA = yeux->getAlpha();
                std::cout<<"DELTA_Y : "<<DELTA_Y<<std::endl;
                std::cout<<"GAMMA_Y : "<<GAMMA_Y<<std::endl;
                std::cout<<"ALPHA : "<<ALPHA<<std::endl;
            }
        }

        // Mettre à jour les propriétés d'écoute
        if (capteur->getType() == 2) { // 2 for Ear
            Oreilles* oreilles = dynamic_cast<Oreilles*>(capteur);
            if (oreilles) {
                // Mettre à jour les propriétés d'écoute
                DELTA_O = oreilles->getDelta();
                GAMMA_O = oreilles->getGamma();
            }
        }
    }
    std::cout<<"Capteurs ajoutés"<<std::endl;
    std::cout<<DELTA_Y<<std::endl;
    std::cout<<DELTA_O<<std::endl;
    
}

std::vector<const Bestiole*> Bestiole::detecterBestioles(const std::vector<Bestiole>& autresBestioles) const {
   std::vector<const Bestiole*> bestioleDetectees;
   
   // Use each sensor to detect bestioles
   for (const auto& capteur : capteurs) {
       std::vector<const Bestiole*> detecteesByCapteur = capteur->detecter(*this, autresBestioles);
       
       // Add unique bestioles to the result list
       for (const auto& b : detecteesByCapteur) {
           // Check if already detected
           bool alreadyDetected = false;
           for (const auto& existingB : bestioleDetectees) {
               if (existingB == b) {
                   alreadyDetected = true;
                   break;
               }
           }
           
           if (!alreadyDetected) {
               bestioleDetectees.push_back(b);
           }
       }
   }
   
   return bestioleDetectees;
}

const std::vector<ICapteur*>& Bestiole::getCapteurs() const {
   return capteurs;
}

bool Bestiole::possedeYeux() const {
   for (const auto& capteur : capteurs) {
       if (capteur->getType() == 1) { // 1 for Eye
           return true;
       }
   }
   return false;
}

bool Bestiole::possedeOreilles() const {
   for (const auto& capteur : capteurs) {
       if (capteur->getType() == 2) { // 2 for Ear
           return true;
       }
   }
   return false;
}
