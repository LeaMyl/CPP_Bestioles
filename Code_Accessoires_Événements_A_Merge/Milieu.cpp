#include "Milieu.h"
#include <ctime>
#include <cstdlib>

#define NAGEOIRES 1
#define CARAPACE 2
#define CAMOUFLAGE 3


const T    Milieu::white[] = { (T)255, (T)255, (T)255 };
bool Milieu::showFieldOfView = true;

Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ), width(_width), height(_height)
{
   cout << "const Milieu" << endl;
   std::srand( time(NULL) );
}


Milieu::~Milieu( void )
{
   cout << "dest Milieu" << endl;
}


void Milieu::step( void )
{
   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );

   // Vérifier les collisions
   gererCollisions();
    
   // Traiter les événements naturels
   processNaturalEvents();

   // Gérer le vieillissement et les morts naturelles
   for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ) {
      // Faire vieillir la bestiole
      it->vieillir();
      
      // Vérifier si elle meurt de vieillesse
      if (it->meurt()) {
          it = listeBestioles.erase(it);
      } else {
          it->action(*this);
          ++it;
      }
   }

   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {
      it->action( *this );
      it->draw( *this );
   } // for
}


int Milieu::nbVoisins( const Bestiole & b )
{
   int         nb = 0;
   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
      if ( !(b == *it) && b.jeTeVois(*it) )
         ++nb;
   return nb;
}

void Milieu::printInfo() const {
   cout << "Nombre de bestioles : " << listeBestioles.size() << endl;
   int nNageoires = 0;
   int nCarapaces = 0;
   int nCamouflages = 0;
   int nYeux = 0;
   int nOreilles = 0;
   
   for (auto b : listeBestioles) {
       for (auto acc : b.getAccessoires()) {
           if (acc->getType() == NAGEOIRES) {
               nNageoires++;
           }
           else if (acc->getType() == CARAPACE) {
               nCarapaces++;
           }
           else if (acc->getType() == CAMOUFLAGE) {
               nCamouflages++;
           }
       }
       
       if (b.possedeYeux()) {
           nYeux++;
       }
       
       if (b.possedeOreilles()) {
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
           if (it1 != it2) {
               double dist = std::sqrt(
                   (it1->getX() - it2->getX()) * (it1->getX() - it2->getX()) +
                   (it1->getY() - it2->getY()) * (it1->getY() - it2->getY())
               );

               if (dist < Configuration::AFF_SIZE) {
                   double probaBase = Configuration::SURVIVE_COLLISION;
                   double proba1 = it1->getResistanceCollision(probaBase);
                   double proba2 = it2->getResistanceCollision(probaBase);

                   bool it1Survives = (std::rand() % 100) < proba1 * 100;
                   bool it2Survives = (std::rand() % 100) < proba2 * 100;

                   if (!it1Survives) { 
                       it1Died = true;
                       continue;
                   }

                   if (!it2Survives) {
                       it2 = listeBestioles.erase(it2);
                       continue;
                   }

                   // Si les deux survivent, elles rebondissent l'une contre l'autre
                   if (it1Survives && it2Survives) {
                       // Calculer le vecteur entre les deux bestioles
                       double dx = it2->getX() - it1->getX();
                       double dy = it2->getY() - it1->getY();
                       
                       // Calculer l'angle de collision
                       double collisionAngle = std::atan2(-dy, dx);
                       
                       // Obtenir les orientations actuelles
                       double ori1 = it1->getOrientation();
                       double ori2 = it2->getOrientation();
                       
                       // Appliquer l'effet de rebond (réflexion par rapport à l'angle de collision)
                       double newOri1 = 2 * collisionAngle - ori1;
                       double newOri2 = 2 * collisionAngle - ori2;
                       
                       // Normaliser les angles entre 0 et 2π si nécessaire
                       while (newOri1 < 0) newOri1 += 2 * M_PI;
                       while (newOri1 >= 2 * M_PI) newOri1 -= 2 * M_PI;
                       while (newOri2 < 0) newOri2 += 2 * M_PI;
                       while (newOri2 >= 2 * M_PI) newOri2 -= 2 * M_PI;
                       
                       // Mettre à jour les orientations
                       it1->setOrientation(newOri1);
                       it2->setOrientation(newOri2);
                       
                       // Légèrement séparer les bestioles pour éviter des collisions répétées
                       double pushDistance = (Configuration::AFF_SIZE - dist) / 2 + 1;
                       double pushX = pushDistance * std::cos(collisionAngle);
                       double pushY = -pushDistance * std::sin(collisionAngle);
                       
                       paire_t coords1 = it1->getCoords();
                       paire_t coords2 = it2->getCoords();
                       
                       coords1.x -= pushX;
                       coords1.y -= pushY;
                       coords2.x += pushX;
                       coords2.y += pushY;
                       
                       it1->setCoords(coords1);
                       it2->setCoords(coords2);
                     }
               }
           }
           ++it2;
       }

       if (it1Died) {
           it1 = listeBestioles.erase(it1);
       } else {
           ++it1;
       }
   }
}

void Milieu::processNaturalEvents() {
   // Naissances spontanées
   if ((std::rand() % 1000) < (Configuration::GENERATION_RATE * 10)) {
       BestioleFactory* factory = BestioleFactory::getInstance();
       Bestiole b = factory->createBestioleWithRandomSensors();
       b.initCoords(width, height);
       
       // Ajouter éventuellement des accessoires
       AccessoireFactory* accFactory = AccessoireFactory::getInstance();
       if ((std::rand() % 100) < (Configuration::TAUX_ACCESSOIRES * 100)) {
           int typeAcc = std::rand() % 3;
           switch (typeAcc) {
               case 0: b.ajouterAccessoire(accFactory->createNageoires()); break;
               case 1: b.ajouterAccessoire(accFactory->createCarapace()); break;
               case 2: b.ajouterAccessoire(accFactory->createCamouflage()); break;
           }
       }
       std::cout << "Nouvelle bestiole née!" << std::endl;
       addMember(b);
   }
   
   // Clonages
   for (auto it = listeBestioles.begin(); it != listeBestioles.end(); ++it) {
       if ((std::rand() % 1000) < (Configuration::CLONE_RATE * 10)) {
           // Créer un clone avec les mêmes propriétés
           Bestiole clone = *it;
           clone.initCoords(width, height);  // Nouvelle position
           std::cout << "Bestiole clonée!" << std::endl;
           addMember(clone);
       }
   }
}