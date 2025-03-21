#include "BestioleFactory.h"
#include "Bestiole.h"
#include "IBestiole.h"
#include "ICapteur.h"
#include "ComportementGregaire.h"
#include "ComportementKamikaze.h"
#include "ComportementPeureux.h"
#include "ComportementPrevoyant.h"
#include "ComportementMultiple.h"

#include "Yeux.h"
#include "Oreilles.h"
#include "Camouflage.h"
#include "Carapace.h"

#include <iostream>
#include <random>


BestioleFactory::BestioleFactory() {
    config = Configuration::getInstance();
}


// Initialiser les attributs d'une bestiole
void BestioleFactory::initialiserAttributsBestiole(Bestiole& bestiole) {
    // Initialiser l'âge limite aléatoirement entre les bornes définies dans la configuration
    bestiole.ageLimite = generate_shuffled_list(VIE);
}

double BestioleFactory::random_between(double a, double b) {
    // Générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());

    // Distribution uniforme entre a et b
    std::uniform_real_distribution<double> dist(a, b);

    return dist(gen);
}

std::vector<int> generate_shuffled_list(int nombreTotal) {
    std::vector<int> numbers(nombreTotal);
    
    // Remplir le vecteur avec les valeurs de 0 à nombreTotal - 1
    for (int i = 0; i < nombreTotal; ++i) {
        numbers[i] = i;
    }

    // Mélanger la liste de façon aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);

    return numbers;
} 

// Créer une population de bestioles
std::vector<std::unique_ptr<Bestiole>> BestioleFactory::creerPopulationBestioles(int nombreTotal) {
    std::vector<std::unique_ptr<Bestiole>> population;


    // Liste Aléotoire
    std::vector<int>  listeAl = generate_shuffled_list(nombreTotal) ;
    // Calculer le nombre de bestioles pour chaque comportement
    int nbGregaires = static_cast<int>(nombreTotal * config->tauxGregaire);
    int nbPeureuses = static_cast<int>(nombreTotal * config->tauxPeureuse);
    int nbKamikazes = static_cast<int>(nombreTotal * config->tauxKamikaze);
    int nbPrevoyantes = static_cast<int>(nombreTotal * config->tauxPrevoyante);
    int nbMultiples = nombreTotal - (nbGregaires + nbPeureuses + nbKamikazes + nbPrevoyantes);

    // Créer les bestioles grégaires
    for (int i = 0; i < nbGregaires; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(std::make_unique<ComportementGregaire>().release());
        initialiserAttributsBestiole(*bestiole);
        population.push_back(bestiole);
    }

    // Créer les bestioles peureuses
    for (int i = 0; i < nbPeureuses; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(std::make_unique<ComportementPeureux>().release());
        initialiserAttributsBestiole(*bestiole);
        population.push_back(bestiole);
    }

    // Créer les bestioles kamikazes
    for (int i = 0; i < nbKamikazes; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(std::make_unique<ComportementKamikaze>().release());
        initialiserAttributsBestiole(*bestiole);
        population.push_back(bestiole);
    }

    // Créer les bestioles prévoyantes
    for (int i = 0; i < nbPrevoyantes; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(std::make_unique<ComportementPrevoyant>().release());
        initialiserAttributsBestiole(*bestiole);
        population.push_back(std::move(bestiole));
    }

    // Créer les bestioles multiples
    for (int i = 0; i < nbMultiples; ++i) {
        auto bestiole = std::make_unique<Bestiole>();
        bestiole->setComportement(std::make_unique<ComportementMultiple>().release());
        initialiserAttributsBestiole(*bestiole);
        population.push_back(std::move(bestiole));
    }

    // Calculer le nombre de bestioles avec des capteurs
    int nbBestiolesAvecCapteurs = static_cast<int>(nombreTotal * config->tauxCapteurs);

    // Calculer le nombre de Yeux et Oreilles en fonction des proportions
    int nbYeux = static_cast<int>(nbBestiolesAvecCapteurs * config->tauxCapteurs);
    int nbOreilles = nbBestiolesAvecCapteurs - nbYeux;

    // Ajouter des Yeux aux bestioles
    for (int i = 0; i < nbYeux; ++i) {
        double delta = random_between(config->dMin, config->dMax);
        double GAMA_O = random_between(config->MIN_GAMA_O, config->MAX_GAMA_O);
        population[listeAl[i]]->ajouterCapteur(new Yeux(delta, GAMA_O));
    }

    // Ajouter des Oreilles aux bestioles
    for (int i = nbYeux; i < nbYeux + nbOreilles; ++i) {
        double angle = random_between(config->angleMin, config->angleMax);
        double delta = random_between(config->dMin, config->dMax);
        double GAMA_O = random_between(config->MIN_GAMA_O, config->MAX_GAMA_O);

        population[listeAl[i]]->ajouterCapteur(new Oreilles(config->dMin, config->dMax, config->MIN_GAMA_O, config->MAX_GAMA_O));
    }

    return population;
}

