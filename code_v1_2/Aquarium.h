#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_

#include "AccessoireFactory.h"
#include "BestioleFactory.h"
#include "Milieu.h"
#include "Configuration.h"

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


class Milieu;


class Aquarium : public CImgDisplay
{

private :
   Milieu       * flotte;

   int            delay;

public :
   Aquarium( int width, int height, int _delay );
   ~Aquarium( void );

   Milieu & getMilieu( void ) { return *flotte; }

   void run( void );
   void initialisation( Configuration config, AccessoireFactory* factory, BestioleFactory* bestioleFactory );

};


#endif
