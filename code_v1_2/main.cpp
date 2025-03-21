#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
//#include "ComportementMultiple.h"
#include "Aquarium.h"
#include <iostream>

int main() {

    Aquarium       ecosysteme( 960, 720, 30 );
    // Création de l'écosystème (Aquarium)

    Configuration config; 
    // Étape 2 : Créer une instance de BestioleFactory avec la configuration
    BestioleFactory factory(&config); 

    
    // Étape 3 : Créer une population de bestioles
    int nombreTotalBestioles = 6;  // Nombre total de bestioles à créer
    std::vector<std::unique_ptr<Bestiole>> population = factory.creerPopulationBestioles(nombreTotalBestioles);
    cout<<"nb de bestiole "<<population.size()<<endl;
    for (auto& bestiole : population) {
        ecosysteme.getMilieu().addMember(bestiole.release());  // Ajouter au milieu et relâcher la propriété

    }
    // Démarre l'écosystème
    ecosysteme.run();

    return 0;
}