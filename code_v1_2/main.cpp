<<<<<<< HEAD
#include "Milieu.h"
#include "Bestiole.h"
#include "ComportementGregaire.h"
#include "ComportementPeureux.h"
#include "ComportementKamikaze.h"
#include "Aquarium.h"
#include <iostream>

int main() {

    Aquarium       ecosysteme( 640, 480, 30 );
    // Création de l'écosystème (Aquarium)


  
    // Création des comportements
    ComportementGregaire comportementGregaire;
    ComportementPeureux comportementPeureux;
    ComportementKamikaze comportementKamikaze;

    // Création et ajout des bestioles au milieu
    //int identite = 1;

    // Ajouter 8 bestioles avec comportement grégaire
    for (int i = 0; i < 8; ++i) {
        auto bestiole = std::make_unique<Bestiole>();  // Utiliser le constructeur par défaut
        bestiole->setComportement(&comportementGregaire);  // Comportement Grégaire
        ecosysteme.getMilieu().addMember(bestiole.get());  // Ajouter au milieu
        ecosysteme.getMilieu().addMember(bestiole.release());  // Relâche la propriété du pointeur unique
    }

    // Ajouter 5 bestioles avec comportement peureux
    for (int i = 0; i < 5; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(&comportementPeureux);  // Comportement Peureux
        ecosysteme.getMilieu().addMember(bestiole.get());
        ecosysteme.getMilieu().addMember(bestiole.release());
    }

    // Ajouter 7 bestioles avec comportement kamikaze
    for (int i = 0; i < 7; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(&comportementKamikaze);  // Comportement Kamikaze
        ecosysteme.getMilieu().addMember(bestiole.get());
        ecosysteme.getMilieu().addMember(bestiole.release());
    }

    // Démarre l'écosystème
    ecosysteme.run();

=======
#include <iostream>
#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "BestioleFactory.h"
#include "Configuration.h"
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const int INIT_NBBESTIOLES = 10;
const int FRAMERATE_DELAY = 30;

int main()
{
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));
    
    // Chargement de la configuration
    Configuration* config = Configuration::getInstance();
    config->setConfigDefault();
    
    // Création de l'aquarium
    Aquarium aquarium(WIDTH, HEIGHT, FRAMERATE_DELAY);
    
    // Récupération du milieu
    Milieu& milieu = aquarium.getMilieu();
    
    // Création de la factory de bestioles
    BestioleFactory factory;
    
    // Création des bestioles initiales
    for (int i = 0; i < INIT_NBBESTIOLES; ++i) {
        // Création d'une bestiole via la factory
        IBestiole* bestiole = factory.IBestiole();
        
        // Initialisation des coordonnées aléatoires
        bestiole->initCoords(WIDTH, HEIGHT);
        
        // Ajout de la bestiole au milieu
        milieu.addMember(bestiole);
    }
    
    // Lancement de la simulation
    cout << "Début de la simulation..." << endl;
    aquarium.run();
    
>>>>>>> 1e9c5d9 (main version 1)
    return 0;
}