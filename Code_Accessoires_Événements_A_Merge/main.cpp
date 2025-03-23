#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "AccessoireFactory.h"

#include <iostream>

using namespace std;

int main()
{
   // Initialize the accessory factory with custom configuration
   AccessoireFactory* factory = AccessoireFactory::getInstance();
   factory->setConfig(2.5, 2.2, 1.8, 0.3, 0.8);

   Aquarium ecosysteme(640, 480, 20);

   ecosysteme.run();

   return 0;
}