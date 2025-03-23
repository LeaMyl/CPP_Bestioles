#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"
#include "Configuration.h"
#include "AccessoireFactory.h"
#include "BestioleFactory.h"

#include <iostream>
#include <vector>

using namespace std;


class Milieu : public UImg
{
public :
   static bool showFieldOfView;

private :
   static const T          white[];
   int                     width, height;
   std::vector<Bestiole>   listeBestioles;

public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );

   void addMember( const Bestiole & b ) { listeBestioles.push_back(b); listeBestioles.back().initCoords(width, height); }
   void removeMember( const Bestiole & b ) { listeBestioles.pop_back(); }
   int nbVoisins( const Bestiole & b );

   const std::vector<Bestiole>& getListeBestioles() const { return listeBestioles; }

   // Méthode printInfo :
   void printInfo() const;

   void toggleFieldOfView();
   bool getShowFieldOfView() const;

   void gererCollisions();
   void processNaturalEvents();
};


#endif
