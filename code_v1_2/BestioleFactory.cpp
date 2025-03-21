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
    cout<<"Factory Creer "<<endl;
}

double BestioleFactory::random_between(double a, double b) {
    // Générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());

    // Distribution uniforme entre a et b
    std::uniform_real_distribution<double> dist(a, b);

    return dist(gen);
}

BestioleFactory::BestioleFactory(Configuration* config) : config(config) {}

BestioleFactory::~BestioleFactory()
{
    // Si la factory gère des ressources internes, les libérer ici
    // Par exemple, si config est alloué dynamiquement :
    if (config != nullptr) {
        delete config;
        config = nullptr;
    }
    cout<<"Factory  "<<endl;
    // Pas besoin de détruire les bestioles, elles sont gérées par des std::unique_ptr
}

int BestioleFactory::initialiserAttributsAgeLimite(Configuration* config)
{
    // Récupération de la configuration
    int ageLimiteMax = config->VIE*1.2 ;
    int ageLimiteMin = config->VIE*1.2 ;
    int ageLimite = rand() % (ageLimiteMax- ageLimiteMin + 1) + ageLimiteMin;

    

    return ageLimite ;
 
};

double BestioleFactory::initialiserAttributsVitesse(Configuration* config)
{

    double vitesse = static_cast<double>(rand()) / RAND_MAX * config->MAX_VITESSE;

    return vitesse;
 
};

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

    if (!config) {
        std::cerr << "Erreur : config est nullptr !" << std::endl;
        return {}; // Retourne un vector vide
    }
    
    std::vector<std::unique_ptr<Bestiole>> population;
    int age_limite;
    double vitesse ;

    // Liste Aléotoire
    std::vector<int>  listeO = generate_shuffled_list(nombreTotal) ;
    std::vector<int>  listeY = generate_shuffled_list(nombreTotal) ;
    // Calculer le nombre de bestioles pour chaque comportement
    int nbGregaires = static_cast<int>(nombreTotal * config->TAUX_GREGAIRE);
    int nbPeureuses = static_cast<int>(nombreTotal * config->TAUX_PEUREUSE);
    int nbKamikazes = static_cast<int>(nombreTotal * config->TAUX_KAMIKAZE);
    int nbPrevoyantes = static_cast<int>(nombreTotal * config->TAUX_PREVOYANTE);
    int nbMultiples = nombreTotal - (nbGregaires + nbPeureuses + nbKamikazes + nbPrevoyantes);

    // Créer les bestioles grégaires
    for (int i = 0; i < nbGregaires; ++i) {
        age_limite = initialiserAttributsAgeLimite(config);
        vitesse = initialiserAttributsVitesse(config);
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementGregaire>(new ComportementGregaire()).release());
        population.push_back(std::move(bestiole));
    }

    // Créer les bestioles peureuses
    for (int i = 0; i < nbPeureuses; ++i) {
        age_limite = initialiserAttributsAgeLimite(config);
        vitesse = initialiserAttributsVitesse(config);
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementPeureux>(new ComportementPeureux()).release());
        population.push_back(std::move(bestiole));
    }

    // Créer les bestioles kamikazes
    for (int i = 0; i < nbKamikazes; ++i) {
        age_limite = initialiserAttributsAgeLimite(config);
        vitesse = initialiserAttributsVitesse(config);
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementKamikaze>(new ComportementKamikaze()).release());
        population.push_back(std::move(bestiole));
        
    }

    // Créer les bestioles prévoyantes
    for (int i = 0; i < nbPrevoyantes; ++i) {
        age_limite = initialiserAttributsAgeLimite(config);
        vitesse = initialiserAttributsVitesse(config);
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementPrevoyant>(new ComportementPrevoyant()).release());
        population.push_back(std::move(bestiole));
    }
    // Vérifier si la population est bien remplie
    /*
    // Créer les bestioles multiples
    for (int i = 0; i < nbMultiples; ++i) {
        
        age_limite = initialiserAttributsAgeLimite(config);
        vitesse = initialiserAttributsVitesse(config);
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementMultiple>(new ComportementMultiple()).release());
        population.push_back(std::move(bestiole));
    }
    */
    // Calculer le nombre de bestioles avec des capteurs
    int nbBestiolesAvecCapteurs = static_cast<int>(nombreTotal * config->TAUX_CAPTEURS);

    // Calculer le nombre de Yeux et Oreilles en fonction des proportions
    int nbYeux = static_cast<int>(nbBestiolesAvecCapteurs * config->TAUX_CAPTEURS);
    int nbOreilles = nbBestiolesAvecCapteurs - nbYeux;

    cout<< "nbBestiolesAvecCapteurs = "<<nbBestiolesAvecCapteurs<< " , nbYeux = " << nbYeux<< " nbOreilles = " <<nbOreilles<<endl;
    // Ajouter des Yeux aux bestioles
    for (int i = 0; i < nbYeux; ++i) {
        double angle = random_between(config->MIN_ALPHA, config->MIN_ALPHA);
        double delta = random_between(config->MIN_DELTA_Y, config->MAX_DELTA_Y);
        double gama = random_between(config->MIN_GAMMA_Y, config->MAX_GAMMA_Y);
        population[listeY[i]]->ajouterCapteur(std::unique_ptr<Yeux>(new Yeux(angle, delta, gama)).release());
        
    }

    // Ajouter des Oreilles aux bestioles
    for (int i = nbYeux; i < nbYeux + nbOreilles; ++i) {
        double delta = random_between(config->MAX_DELTA_O, config->MIN_DELTA_O);
        double gama = random_between(config->MIN_GAMMA_O, config->MAX_GAMMA_O);

        population[listeO[i]]->ajouterCapteur(std::unique_ptr<Oreilles>(new Oreilles(delta,gama)).release());
    }
    // Vérifier si la population est bien remplie
    std::cout << "Nombre de bestioles créées : " << population.size() << std::endl;
    return population;
}

