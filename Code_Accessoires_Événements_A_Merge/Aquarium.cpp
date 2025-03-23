#include "Aquarium.h"

#include <iostream>


Aquarium::Aquarium( int width, int height, int _delay ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();


   cout << "const Aquarium" << endl;

   flotte = new Milieu( width, height );
   assign( *flotte, "Simulation d'ecosysteme" );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}


Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}


void Aquarium::run( void )
{  
   // Interactions avec l'utilisateur pour la simulation en fonction de la touche pressee avec 1 sec de delay entre chaque action
   // ESC : fermeture de la fenetre
   // N : ajout d'un nombre de bestioles (à spécifier dans le terminal)
   // M : suppression d'un nombre de bestioles (à spécifier dans le terminal)
   // ESPACE : pause de la simulation (si elle était en cours)
   // ESPACE : reprise de la simulation (si elle était en pause)
   // I : affichage des informations de la simulation dans le terminal : nombre de bestioles, nombre de bestioles de chaque type, nombre de bestioles avec chaque accessoire
   // F : affichage du champ de vision des bestioles et de leur champ d'écoute (si il est caché)
   // F : masquage du champ de vision des bestioles et de leur champ d'écoute (si il est affiché)
   // C : affichage des accessoires des bestioles (si ils sont cachés)
   // C : masquage des accessoires des bestioles (si ils sont affichés)

   cout << "running Aquarium" << endl;

   bool paused = false;
   
   // On crée la configuration
   Configuration config;

   // On initialise les paramètres de configuration
   double TAUX_ACCESSOIRES = config.TAUX_ACCESSOIRES;

   // Factory d'accessoires
   AccessoireFactory* factory = AccessoireFactory::getInstance();

   // Factory de bestioles
   BestioleFactory* bestioleFactory = BestioleFactory::getInstance();

   // On initialise
   initialisation(config, factory, bestioleFactory);

   while ( !is_closed() )
   {
      if ( is_key() )
      {
         if ( is_keyESC() ){close();}
         else if ( is_keySPACE() ){paused = !paused; wait(50 * delay); cout << "Simulation en Pause" << endl;}
         else if ( is_keyN() ){
            paused = true;
            int n;
            cout << "Combien de bestioles voulez-vous ajouter ? ";
            cin >> n;
            for (int i = 0; i < n; i++){
               Bestiole b = bestioleFactory->createBestiole();
               if (rand() % 3 == 0) {
                  b.ajouterAccessoire(factory->createNageoires());
               }
               if (rand() % 3 == 1) {
                  b.ajouterAccessoire(factory->createCarapace());
               }
               if (rand() % 3 == 2) {
                  b.ajouterAccessoire(factory->createCamouflage());
               }
               flotte->addMember(b);
            }
            display( *flotte );
            paused = false;
         }
         else if ( is_keyM() ){
            paused = true;
            int n;
            cout << "Combien de bestioles voulez-vous supprimer ? ";
            cin >> n;
            for (int i = 0; i < n; i++) {
               Bestiole b = flotte->getListeBestioles()[rand() % flotte->getListeBestioles().size()];
               flotte->removeMember(b);
               cout<<"Bestiole supprimée"<<endl;
            }
            display( *flotte );
            paused = false;
         }
         else if ( is_keyI() ){
            flotte->printInfo();
         }
         else if ( is_keyF() ){
            flotte->toggleFieldOfView();
         }
         // else if ( is_keyC() ){
         //    flotte->toggleAccessories();
         // }
         
         wait(1000); // On attends 1 seconde pour éviter les pressions multiples de touches
      }

      if (!paused)
      {
         flotte->step();
         display( *flotte );
      }
      display( *flotte );
      wait( delay );
   }
}


void Aquarium::initialisation(Configuration config, AccessoireFactory* factory, BestioleFactory* bestioleFactory)
{
    cout << "Initialisation de l'Aquarium" << endl;
    int n = 20;
    
    // On définit les taux explicitement si les valeurs de config sont à zéro
    double TAUX_ACCESSOIRES = config.TAUX_ACCESSOIRES > 0 ? config.TAUX_ACCESSOIRES : 0.3;
    double TAUX_CAPTEURS = config.TAUX_CAPTEURS > 0 ? config.TAUX_CAPTEURS : 0.3;
    
    cout << "TAUX_ACCESSOIRES: " << TAUX_ACCESSOIRES << endl;
    cout << "TAUX_CAPTEURS: " << TAUX_CAPTEURS << endl;
    
    // Nombre de bestioles qui doivent avoir chaque type d'accessoire
    int nbNageoires = static_cast<int>(n * TAUX_ACCESSOIRES);
    int nbCarapaces = static_cast<int>(n * TAUX_ACCESSOIRES);
    int nbCamouflages = static_cast<int>(n * TAUX_ACCESSOIRES);
    
    // Nombre de bestioles qui doivent avoir chaque type de capteur
    int nbYeux = static_cast<int>(n * TAUX_CAPTEURS);
    int nbOreilles = static_cast<int>(n * TAUX_CAPTEURS);
    
    // S'assurer qu'il y a au moins quelques accessoires et capteurs
    nbNageoires = nbNageoires > 0 ? nbNageoires : 6;
    nbCarapaces = nbCarapaces > 0 ? nbCarapaces : 6;
    nbCamouflages = nbCamouflages > 0 ? nbCamouflages : 6;
    nbYeux = nbYeux > 0 ? nbYeux : 6;
    nbOreilles = nbOreilles > 0 ? nbOreilles : 6;
    
    vector<Bestiole> bestioles;
    for (int i = 0; i < n; i++) {
        Bestiole b = bestioleFactory->createBestiole();
        bestioles.push_back(b);
    }
    
    // Initialisation du générateur de nombres aléatoires avec une graine différente
    srand(time(NULL));
    
    // Distribution aléatoire des nageoires
    vector<int> indicesNageoires;
    for (int i = 0; i < nbNageoires && i < n; i++) {
        int index = rand() % n;
        while (find(indicesNageoires.begin(), indicesNageoires.end(), index) != indicesNageoires.end()) {
            index = rand() % n;
        }
        indicesNageoires.push_back(index);
        bestioles[index].ajouterAccessoire(factory->createNageoires());
    }
    
    // Distribution aléatoire des carapaces
    vector<int> indicesCarapaces;
    for (int i = 0; i < nbCarapaces && i < n; i++) {
        int index = rand() % n;
        while (find(indicesCarapaces.begin(), indicesCarapaces.end(), index) != indicesCarapaces.end()) {
            index = rand() % n;
        }
        indicesCarapaces.push_back(index);
        bestioles[index].ajouterAccessoire(factory->createCarapace());
    }
    
    // Distribution aléatoire des camouflages
    vector<int> indicesCamouflages;
    for (int i = 0; i < nbCamouflages && i < n; i++) {
        int index = rand() % n;
        while (find(indicesCamouflages.begin(), indicesCamouflages.end(), index) != indicesCamouflages.end()) {
            index = rand() % n;
        }
        indicesCamouflages.push_back(index);
        bestioles[index].ajouterAccessoire(factory->createCamouflage());
    }
    
    // Distribution aléatoire des yeux
    vector<int> indicesYeux;
    for (int i = 0; i < nbYeux && i < n; i++) {
        int index = rand() % n;
        while (find(indicesYeux.begin(), indicesYeux.end(), index) != indicesYeux.end()) {
            index = rand() % n;
        }
        indicesYeux.push_back(index);
        bestioles[index].ajouterCapteur(Yeux::generateRandomYeux());
    }
    
    // Distribution aléatoire des oreilles
    vector<int> indicesOreilles;
    for (int i = 0; i < nbOreilles && i < n; i++) {
        int index = rand() % n;
        while (find(indicesOreilles.begin(), indicesOreilles.end(), index) != indicesOreilles.end()) {
            index = rand() % n;
        }
        indicesOreilles.push_back(index);
        bestioles[index].ajouterCapteur(Oreilles::generateRandomOreilles());
    }
    
    // Ajout des bestioles à l'aquarium
    for (auto& b : bestioles) {
        flotte->addMember(b);
    }
    
    cout << "Initialisation terminée avec " << n << " bestioles" << endl;
    cout << "Bestioles avec nageoires: " << nbNageoires << endl;
    cout << "Bestioles avec carapaces: " << nbCarapaces << endl;
    cout << "Bestioles avec camouflages: " << nbCamouflages << endl;
    cout << "Bestioles avec yeux: " << nbYeux << endl;
    cout << "Bestioles avec oreilles: " << nbOreilles << endl;
}