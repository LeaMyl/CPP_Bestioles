#include "Milieu.h"
#include "Bestiole.h"
#include "ComportementGregaire.h"
#include "ComportementPeureux.h"
#include "ComportementKamikaze.h"
#include "ComportementPrevoyant.h"
//#include "ComportementMultiple.h"
#include "Aquarium.h"
#include <iostream>

int main() {

    Aquarium       ecosysteme( 640, 480, 30 );
    // Création de l'écosystème (Aquarium)


  
    // Création des comportements
    ComportementGregaire comportementGregaire;
    ComportementPeureux comportementPeureux;
    ComportementKamikaze comportementKamikaze;
    ComportementPrevoyant comportementPrevoyant;
    //ComportementMultiple comportementMultiple;

    // Création et ajout des bestioles au milieu
    //int identite = 1;

    // Ajouter 2 bestioles avec comportement grégaire
    for (int i = 0; i < 2; ++i) {
        auto bestiole = std::make_unique<Bestiole>();  // Utiliser le constructeur par défaut
        bestiole->setComportement(&comportementGregaire);  // Comportement Grégaire
        ecosysteme.getMilieu().addMember(bestiole.get());  // Ajouter au milieu
        ecosysteme.getMilieu().addMember(bestiole.release());  // Relâche la propriété du pointeur unique
    }

    // Ajouter 2 bestioles avec comportement peureux
    for (int i = 0; i < 2; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(&comportementPeureux);  // Comportement Peureux
        ecosysteme.getMilieu().addMember(bestiole.get());
        ecosysteme.getMilieu().addMember(bestiole.release());
    }

    // Ajouter 2 bestioles avec comportement kamikaze
    for (int i = 0; i < 2; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(&comportementKamikaze);  // Comportement Kamikaze
        ecosysteme.getMilieu().addMember(bestiole.get());
        ecosysteme.getMilieu().addMember(bestiole.release());
    }

    // Ajouter 2 bestioles avec comportement prevoyant
    for (int i = 0; i < 2; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(&comportementPrevoyant);  // Comportement Prevoyant
        ecosysteme.getMilieu().addMember(bestiole.get());
        ecosysteme.getMilieu().addMember(bestiole.release());
    }

    // // Ajouter 2 bestioles avec comportement multiple
    // for (int i = 0; i < 2; ++i) {
    //     auto bestiole = std::make_unique<Bestiole>();
    //     bestiole->setComportement(&comportementMultiple);  // Comportement Multiple
    //     ecosysteme.getMilieu().addMember(bestiole.get());
    //     ecosysteme.getMilieu().addMember(bestiole.release());
    // }

    // Démarre l'écosystème
    ecosysteme.run();

    return 0;
}