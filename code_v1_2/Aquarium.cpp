#include "Aquarium.h"
#include <iostream>

// Constructeur de l'Aquarium
// Initialise l'affichage et positionne la fenêtre au centre de l'écran
Aquarium::Aquarium(int width, int height, int _delay) : CImgDisplay(), delay(_delay) {
    int screenWidth = 1280;   // Largeur de l'écran
    int screenHeight = 1024;  // Hauteur de l'écran

    cout << "Constructeur de l'Aquarium" << endl;

    // Création du milieu de simulation
    flotte = new Milieu(width, height);
    assign(*flotte, "Simulation d'ecosysteme");

    // Centrer la fenêtre sur l'écran
    move(static_cast<int>((screenWidth - width) / 2), 
         static_cast<int>((screenHeight - height) / 2));
}

// Destructeur de l'Aquarium
// Libère les ressources allouées
Aquarium::~Aquarium() {
    delete flotte;
    cout << "Destructeur de l'Aquarium" << endl;
}

// Méthode principale de simulation
void Aquarium::run() {
    // Menu interactif de simulation :
    // - ESC : fermer la fenêtre
    // - N : ajouter des bestioles
    // - M : supprimer des bestioles
    // - ESPACE : mettre en pause/reprendre
    // - I : afficher les informations
    // - F : afficher/masquer les champs de vision

    cout << "Lancement de l'Aquarium" << endl;

    bool paused = false;
    Configuration config;
    double TAUX_ACCESSOIRES = config.TAUX_ACCESSOIRES;

    // Factories pour les accessoires et bestioles
    AccessoireFactory* factory = AccessoireFactory::getInstance();
    BestioleFactory *bestioleFactory; 

    // Initialisation de la simulation
    initialisation(config, factory, bestioleFactory);

    // Boucle principale de simulation
    while (!is_closed()) {
        // Gestion des événements clavier
        if (is_key()) {
            if (is_keyESC()) {
                close();
            }
            else if (is_keySPACE()) {
                paused = !paused; 
                wait(50 * delay);
                cout << "Simulation en Pause" << endl;
            }
            // Ajout de bestioles
            else if (is_keyN()) {
                paused = true;
                int n;
                cout << "Combien de bestioles voulez-vous ajouter ? ";
                cin >> n;

                const auto& listeBestioles = flotte->getListeBestioles();
                std::vector<std::unique_ptr<IBestiole>> population = 
                    bestioleFactory->ajouterBestiole(listeBestioles, n);

                for (auto& bestiole : population) {
                    // std::cout << "Ajout d'une bestiole" << std::endl;
                    flotte->addMember(bestiole.release());
                    // std::cout << "Bestiole ajoutée" << std::endl;
                }
                display(*flotte);
                paused = false;
            }
            // Suppression de bestioles
            else if (is_keyM()) {
                paused = true;
                int n;
                cout << "Combien de bestioles voulez-vous supprimer ? ";
                cin >> n;
                if (flotte->getListeBestioles().size() < n) {
                    n = flotte->getListeBestioles().size();
                }
                for (int i = 0; i < n; i++) {
                    IBestiole* b = flotte->getListeBestioles()[rand() % flotte->getListeBestioles().size()];
                    flotte->removeMember(b);
                    // cout << "Bestiole supprimée" << endl;
                }
                display(*flotte);
                paused = false;
            }
            // Afficher les informations
            else if (is_keyI()) {
                flotte->printInfo();
            }
            // Afficher/masquer les champs de vision
            else if (is_keyF()) {
                flotte->toggleFieldOfView();
            }
            
            wait(1000); // Éviter les pressions multiples de touches
        }

        // Mettre à jour et afficher la simulation
        if (!paused) {
            flotte->step();
            display(*flotte);
        }
        display(*flotte);
        wait(delay);
    }
}

// Initialisation de la population de bestioles
void Aquarium::initialisation(Configuration config, AccessoireFactory* factory, BestioleFactory* bestioleFactory) {
    cout << "Initialisation de l'Aquarium" << endl;
    
    // Créer une population initiale de bestioles
    int nombreTotalBestioles = Configuration::NOMBRE_BESTIOLES;
    std::vector<std::unique_ptr<Bestiole>> population = 
        bestioleFactory->creerPopulationBestioles(nombreTotalBestioles);
    
    cout << "Nombre de bestioles : " << population.size() << endl;
    
    // Ajouter les bestioles au milieu
    for (auto& bestiole : population) {
        flotte->addMember(bestiole.release());
    }
    
    // Afficher les informations initiales
    flotte->printInfo();
}