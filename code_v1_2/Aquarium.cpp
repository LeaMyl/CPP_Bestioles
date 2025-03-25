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
   
   cout << "running Aquarium" << endl;

   bool paused = false;
   
   // On crée la configuration
   Configuration config;

   // On initialise les paramètres de configuration
   double TAUX_ACCESSOIRES = config.TAUX_ACCESSOIRES;

   // Factory d'accessoires
   AccessoireFactory* factory = AccessoireFactory::getInstance();

   // Factory de bestioles
   BestioleFactory *bestioleFactory; 

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

            std::vector<std::unique_ptr<Bestiole>> population = bestioleFactory->creerPopulationBestioles(n);
            for (auto& bestiole : population) {
               flotte->addMember(bestiole.release());  // Ajouter au milieu et relâcher la propriété
       
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
               IBestiole* b = flotte->getListeBestioles()[rand() % flotte->getListeBestioles().size()];
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
    int nombreTotalBestioles = 12;  // Nombre total de bestioles à créer
    std::vector<std::unique_ptr<Bestiole>> population = bestioleFactory->creerPopulationBestioles(nombreTotalBestioles);
    cout<<"nb de bestiole "<<population.size()<<endl;
    for (auto& bestiole : population) {
        flotte->addMember(bestiole.release());  // Ajouter au milieu et relâcher la propriété

    }
    
    flotte->printInfo();
}