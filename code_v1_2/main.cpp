#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
//#include "ComportementMultiple.h"
#include "Aquarium.h"
#include <iostream>

int main() {

    Aquarium       ecosysteme( 960, 720, 30 );
    // Création de l'écosystème (Aquarium)

    // Étape 2 : Créer une instance de BestioleFactory avec la configuration
    BestioleFactory factory; 

    
    // Étape 3 : Créer une population de bestioleTAUX_CAPTEURSs
   
    // Démarre l'écosystème
    ecosysteme.run();

    return 0;
}