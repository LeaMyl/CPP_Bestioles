#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include "UImg.h"

#include <iostream>
#include <map>
#include <vector>
#include <memory>

class Milieu;
class IAccessoire;
class ICapteur;
struct ParametresBestioles;

using namespace std;
using Dictionnaire_Parametres = std::map<std::string, ParametresBestioles*>;

class Milieu;

typedef struct paire {
   int x;
   int y;
   double ori;
   double vite;
} paire_t;

struct ParametresBestioles
{
   ParametresBestioles();
   virtual ~ParametresBestioles();
   void PushWith(string key, Dictionnaire_Parametres& pd);
   virtual void Add(Dictionnaire_Parametres& pd) = 0;
   virtual ParametresBestioles* cppm() const = 0;
};

class Bestiole
{
private:
   double GAMMA_O;
   double GAMMA_Y;
   double ALPHA;
   double DELTA_O;
   double DELTA_Y;
   static int              next;

   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   double            baseVitesse; // Vitesse originale avant modifications par accessoires

   T               * couleur;
   
   int               age;
   int               ageLimite;
   
   // Vecteur d'accessoires et de capteurs
   std::vector<IAccessoire*> accessoires;
   std::vector<ICapteur*> capteurs;

public:                                           // Forme canonique :
   Bestiole( void );                               // Constructeur par défaut
   Bestiole( const Bestiole & b );                 // Constructeur de copie
   ~Bestiole( void );                              // Destructeur

   void action( Milieu & monMilieu );
   void draw( UImg & support );
   void bouge( int xLim, int yLim );
   bool jeTeVois( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );
   
   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );

   paire_t getCoords() const;
   void setCoords(paire_t coords);
   
   // Méthodes pour l'âge et la mort
   void vieillir();
   bool meurt() const;
   
   // Nouvelles méthodes pour les accessoires
   void ajouterAccessoire(IAccessoire* accessoire);
   double getVitesse() const;
   double getBaseVitesse() const;
   void setVitesse(double v);
   double getOrientation() const;
   double getResistanceCollision(double probaBase) const;
   double getCoeffCamoufflage() const;
   bool possedeAccessoire(int typeAccessoire) const;
   const std::vector<IAccessoire*>& getAccessoires() const;

   double getX() const { return x; }
   double getY() const { return y; }
   void setOrientation(double ori) { orientation = ori; }

   Bestiole& operator=(const Bestiole& b);

   // Gestion des capteurs
   void ajouterCapteur(ICapteur* capteur);
   std::vector<const Bestiole*> detecterBestioles(const std::vector<Bestiole>& autresBestioles) const;
   const std::vector<ICapteur*>& getCapteurs() const;
   bool possedeYeux() const;
   bool possedeOreilles() const;

   // Getters et setters
   double getGammaO() const { return GAMMA_O; }
   double getGammaY() const { return GAMMA_Y; }
   double getAlpha() const { return ALPHA; }
   double getDeltaO() const { return DELTA_O; }
   double getDeltaY() const { return DELTA_Y; }
   void setGammaO(double gamma) { GAMMA_O = gamma; }
   void setGammaY(double gamma) { GAMMA_Y = gamma; }
   void setAlpha(double alpha) { ALPHA = alpha; }
   void setDeltaO(double delta) { DELTA_O = delta; }
   void setDeltaY(double delta) { DELTA_Y = delta; }
};

#endif