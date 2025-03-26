#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
#include "Aquarium.h"
#include <iostream>

int main() {
    // Création de l'écosystème (Aquarium) avec une largeur de 960, hauteur de 720, et 30 fps
    Aquarium ecosysteme(960, 720, 30);

    // Création d'une fabrique de bestioles
    BestioleFactory factory; 
   
    // Démarrage de la simulation de l'écosystème
    ecosysteme.run();

    return 0;
}