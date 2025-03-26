#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_

// Inclusions des bibliothèques et classes nécessaires
#include "AccessoireFactory.h"
#include "BestioleFactory.h"
#include "Milieu.h"
#include "Configuration.h"

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

// Déclaration anticipée de la classe Milieu
class Milieu;

/**
 * @class Aquarium
 * @brief Classe représentant l'environnement de simulation des bestioles
 * 
 * Hérite de CImgDisplay pour la gestion de l'affichage graphique
 */
class Aquarium : public CImgDisplay
{
private:
    // ===== ATTRIBUTS PRIVÉS =====
    
    // Pointeur vers le milieu de simulation (ensemble des bestioles)
    Milieu* flotte;
    
    // Délai entre chaque mise à jour de la simulation
    int delay;

public:
    // ===== CONSTRUCTEURS ET DESTRUCTEUR =====
    
    /**
     * @brief Constructeur de l'aquarium
     * @param width Largeur de la fenêtre de simulation
     * @param height Hauteur de la fenêtre de simulation
     * @param _delay Délai entre chaque mise à jour
     */
    Aquarium(int width, int height, int _delay);
    
    /**
     * @brief Destructeur de l'aquarium
     * Libère les ressources allouées
     */
    ~Aquarium(void);

    // ===== ACCESSEURS =====
    
    /**
     * @brief Obtenir une référence au milieu de simulation
     * @return Référence au milieu (flotte de bestioles)
     */
    Milieu& getMilieu(void) { return *flotte; }

    // ===== MÉTHODES DE SIMULATION =====
    
    /**
     * @brief Lancer la simulation
     * Boucle principale de l'aquarium
     */
    void run(void);
    
    /**
     * @brief Initialiser la simulation
     * @param config Configuration de la simulation
     * @param factory Fabrique d'accessoires
     * @param bestioleFactory Fabrique de bestioles
     */
    void initialisation(
        Configuration config, 
        AccessoireFactory* factory, 
        BestioleFactory* bestioleFactory
    );
};

#endif // _AQUARIUM_H_