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

// Instance unique de la factory 
BestioleFactory* BestioleFactory::instance = nullptr;

// Constructeur privé pour le pattern
BestioleFactory::BestioleFactory() {
    // Initialisations potentielles
}

// Destructeur
BestioleFactory::~BestioleFactory() {
    // Libération des ressources si nécessaire
}

// Méthode pour obtenir l'instance unique de la factory
BestioleFactory* BestioleFactory::getInstance() {
    if (instance == nullptr) {
        instance = new BestioleFactory();
    }
    return instance;
}

// Génère un nombre aléatoire entre a et b
double BestioleFactory::random_between(double a, double b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(a, b);
    return dist(gen);
}

// Initialise l'âge limite d'une bestiole de manière aléatoire
int BestioleFactory::initialiserAttributsAgeLimite() {
    int ageLimiteMax = Configuration::VIE * 1.2;
    int ageLimiteMin = Configuration::VIE * 1.2;
    return rand() % (ageLimiteMax - ageLimiteMin + 1) + ageLimiteMin;
}

// Initialise la vitesse d'une bestiole de manière aléatoire
double BestioleFactory::initialiserAttributsVitesse() {
    return static_cast<double>(rand()) / RAND_MAX * Configuration::MAX_VITESSE;
}

// Génère une liste mélangée de nombres de 0 à nombreTotal - 1
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

// Crée une population de bestioles avec différents comportements et caractéristiques
std::vector<std::unique_ptr<Bestiole>> BestioleFactory::creerPopulationBestioles(int nombreTotal) {
    std::vector<std::unique_ptr<Bestiole>> population;
    int age_limite;
    double vitesse;

    // Listes aléatoires pour répartition des caractéristiques
    std::vector<int> listeO = generate_shuffled_list(nombreTotal);
    std::vector<int> listeY = generate_shuffled_list(nombreTotal);
    std::vector<int> listeBestioleAccessoires = generate_shuffled_list(nombreTotal);

    // Calcul du nombre de bestioles par comportement
    int nbGregaires = static_cast<int>(nombreTotal * Configuration::TAUX_GREGAIRE);
    int nbPeureuses = static_cast<int>(nombreTotal * Configuration::TAUX_PEUREUSE);
    int nbKamikazes = static_cast<int>(nombreTotal * Configuration::TAUX_KAMIKAZE);
    int nbPrevoyantes = static_cast<int>(nombreTotal * Configuration::TAUX_PREVOYANTE);
    int nbMultiples = nombreTotal - (nbGregaires + nbPeureuses + nbKamikazes + nbPrevoyantes);

    // Création des bestioles avec différents comportements
    auto creerBestioleAvecComportement = [&](auto comportementFactory) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(comportementFactory().release());
        population.push_back(std::move(bestiole));
    };

    for (int i = 0; i < nbGregaires; ++i) 
        creerBestioleAvecComportement([]() { return std::unique_ptr<ComportementGregaire>(new ComportementGregaire()); });
    
    for (int i = 0; i < nbPeureuses; ++i) 
        creerBestioleAvecComportement([]() { return std::unique_ptr<ComportementPeureux>(new ComportementPeureux()); });
    
    for (int i = 0; i < nbKamikazes; ++i) 
        creerBestioleAvecComportement([]() { return std::unique_ptr<ComportementKamikaze>(new ComportementKamikaze()); });
    
    for (int i = 0; i < nbPrevoyantes; ++i) 
        creerBestioleAvecComportement([]() { return std::unique_ptr<ComportementPrevoyant>(new ComportementPrevoyant()); });
    
    for (int i = 0; i < nbMultiples; ++i) 
        creerBestioleAvecComportement([]() { return std::unique_ptr<ComportementMultiple>(new ComportementMultiple()); });

    // Ajout des capteurs (Yeux et Oreilles)
    int nbBestiolesAvecCapteurs = static_cast<int>(nombreTotal * Configuration::TAUX_CAPTEURS);
    int nbYeux = static_cast<int>(nbBestiolesAvecCapteurs * Configuration::TAUX_YEUX);
    int nbOreilles = static_cast<int>(nbBestiolesAvecCapteurs * Configuration::TAUX_OREILLES);

    // Ajout des Yeux
    for (int i = 0; i < nbYeux; ++i) {
        double angle = random_between(Configuration::MIN_ALPHA, Configuration::MIN_ALPHA);
        double delta = random_between(Configuration::MIN_DELTA_Y, Configuration::MAX_DELTA_Y);
        double gama = random_between(Configuration::MIN_GAMMA_Y, Configuration::MAX_GAMMA_Y);
        population[listeY[i]]->ajouterCapteur(std::unique_ptr<ICapteur>(new Yeux(angle, delta, gama)));
    }

    // Ajout des Oreilles
    for (int i = 0; i <  nbOreilles; ++i) {
        double delta = random_between(Configuration::MAX_DELTA_O, Configuration::MIN_DELTA_O);
        double gama = random_between(Configuration::MIN_GAMMA_O, Configuration::MAX_GAMMA_O);
        population[listeO[i]]->ajouterCapteur(std::unique_ptr<ICapteur>(new Oreilles(delta, gama)));
    }

    // Ajout des accessoires
    int nbBestiolesAvecAccessoires = static_cast<int>(nombreTotal * Configuration::TAUX_ACCESSOIRES);
    for (int i = 0; i <  nbBestiolesAvecAccessoires; ++i) {
        IAccessoire* accessoire = AccessoireFactory::getInstance()->createRandomAccessoire();
        population[listeBestioleAccessoires[i]]->ajouterAccessoire(accessoire);
    }

    return population;
}

// Crée une bestiole unique avec des caractéristiques aléatoires
std::unique_ptr<Bestiole> BestioleFactory::createBestioleWithRandomBestiole() {
    int age_limite = initialiserAttributsAgeLimite();
    double vitesse = initialiserAttributsVitesse();
    
    auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse)); 

    // Attribution d'un comportement aléatoire
    int randomValue = rand() % 4; 
    switch (randomValue) {
        case 0:
            bestiole->setComportement(std::unique_ptr<ComportementGregaire>(new ComportementGregaire()).release());
            break;
        case 1:
            bestiole->setComportement(std::unique_ptr<ComportementPeureux>(new ComportementPeureux()).release());
            break;
        case 2:
            bestiole->setComportement(std::unique_ptr<ComportementKamikaze>(new ComportementKamikaze()).release());
            break;
        case 3:
            bestiole->setComportement(std::unique_ptr<ComportementPrevoyant>(new ComportementPrevoyant()).release());
            break;
        case 4: 
            bestiole->setComportement(std::unique_ptr<ComportementMultiple>(new ComportementMultiple()).release());
            break;
    }

    // Ajout de capteurs et accessoires selon des probabilités configurées
    if ((static_cast<double>(rand()) / RAND_MAX) < Configuration::TAUX_CAPTEURS) {
        double angle = random_between(Configuration::MIN_ALPHA, Configuration::MIN_ALPHA);
        double delta = random_between(Configuration::MIN_DELTA_Y, Configuration::MAX_DELTA_Y);
        double gama = random_between(Configuration::MIN_GAMMA_Y, Configuration::MAX_GAMMA_Y);
        bestiole->ajouterCapteur(std::unique_ptr<ICapteur>(new Yeux(angle, delta, gama)));
    }
    
    if ((static_cast<double>(rand()) / RAND_MAX) < Configuration::TAUX_CAPTEURS) {
        double delta = random_between(Configuration::MAX_DELTA_O, Configuration::MIN_DELTA_O);
        double gama = random_between(Configuration::MIN_GAMMA_O, Configuration::MAX_GAMMA_O);
        bestiole->ajouterCapteur(std::unique_ptr<ICapteur>(new Oreilles(delta, gama)));
    }
    
    if ((static_cast<double>(rand()) / RAND_MAX) < Configuration::TAUX_ACCESSOIRES) {
        IAccessoire* accessoire = AccessoireFactory::getInstance()->createRandomAccessoire();
        bestiole->ajouterAccessoire(accessoire);
    }

    return bestiole;
}

// Clone une bestiole existante
std::unique_ptr<IBestiole> BestioleFactory::cloneBestiole(const IBestiole& bestioleToClone) {
    return std::unique_ptr<IBestiole>(bestioleToClone.clone());
}

// Ajoute de nouvelles bestioles à une population existante
std::vector<std::unique_ptr<IBestiole>> BestioleFactory::ajouterBestiole(const std::vector<IBestiole*>& population, int nombre) {
    std::vector<std::unique_ptr<IBestiole>> nouvellesBestioles;
    std::vector<IBestiole*> populationMutable = population;
    
    for (int i = 0; i < nombre; ++i) {
        auto nouvelleBestiole = createBestioleWithRandomBestiole();
        
        // Directement passer à l'ajustement du comportement en utilisant la fonction existante
        std::unique_ptr<Bestiole> bestioleAjustee = ajusterComportementSelonRatios(std::move(nouvelleBestiole), populationMutable);
        nouvellesBestioles.push_back(std::move(bestioleAjustee));
        populationMutable.push_back(nouvellesBestioles.back().get());
    }

    return nouvellesBestioles;
}

// Ajuste le comportement d'une bestiole pour respecter les ratios de la population
std::unique_ptr<Bestiole> BestioleFactory::ajusterComportementSelonRatios(
    std::unique_ptr<Bestiole> bestiole, 
    const std::vector<IBestiole*>& population) 
{
    // Calcul des taux réels de comportements
    int nbTotal = population.size() + 1; // +1 pour la nouvelle bestiole
    int nbGregaires = 0, nbPeureuses = 0, nbKamikazes = 0, nbPrevoyantes = 0, nbMultiples = 0;

    for (const auto& existingBestiole : population) {
        IComportement* comportement = dynamic_cast<Bestiole*>(existingBestiole)->getComportement();
        
        if (dynamic_cast<ComportementGregaire*>(comportement)) {
            nbGregaires++;
        } else if (dynamic_cast<ComportementPeureux*>(comportement)) {
            nbPeureuses++;
        } else if (dynamic_cast<ComportementKamikaze*>(comportement)) {
            nbKamikazes++;
        } else if (dynamic_cast<ComportementPrevoyant*>(comportement)) {
            nbPrevoyantes++;
        } else if (dynamic_cast<ComportementMultiple*>(comportement)) {
            nbMultiples++;
        }
    }

    // Calcul des taux réels
    double tauxGregaire = static_cast<double>(nbGregaires) / nbTotal;
    double tauxPeureux = static_cast<double>(nbPeureuses) / nbTotal;
    double tauxKamikaze = static_cast<double>(nbKamikazes) / nbTotal;
    double tauxPrevoyante = static_cast<double>(nbPrevoyantes) / nbTotal;
    double tauxMultiple = static_cast<double>(nbMultiples) / nbTotal;

    // Calcul des écarts SIGNÉS par rapport aux taux de configuration
    double ecartGregaire   = tauxGregaire - Configuration::TAUX_GREGAIRE;
    double ecartPeureux    = tauxPeureux - Configuration::TAUX_PEUREUSE;
    double ecartKamikaze   = tauxKamikaze - Configuration::TAUX_KAMIKAZE;
    double ecartPrevoyante = tauxPrevoyante - Configuration::TAUX_PREVOYANTE;
    double ecartMultiple   = tauxMultiple - Configuration::TAUX_MULTIPLE;

    // Structure pour stocker les écarts et les créateurs de comportements
    struct ComportementEcart {
        double ecart;
        IComportement* (*createur)();
    };

    ComportementEcart comportements[] = {
        {ecartGregaire, []() -> IComportement* { return new ComportementGregaire(); }},
        {ecartPeureux, []() -> IComportement* { return new ComportementPeureux(); }},
        {ecartKamikaze, []() -> IComportement* { return new ComportementKamikaze(); }},
        {ecartPrevoyante, []() -> IComportement* { return new ComportementPrevoyant(); }},
        {ecartMultiple, []() -> IComportement* { return new ComportementMultiple(); }}
    };

    // Sélection du comportement avec l'écart maximum
    ComportementEcart comportementChoisi = comportements[0];
    std::vector<ComportementEcart> candidats;
    double maxEcart = 0;

    for (const auto& comp : comportements) {
        if (comp.ecart < maxEcart) {
            maxEcart = comp.ecart;
            candidats.clear();
            candidats.push_back(comp);
        } else if (comp.ecart == maxEcart) {
            candidats.push_back(comp);
        }
    }

    if (!candidats.empty()) {
        int index = rand() % candidats.size();
        comportementChoisi = candidats[index];
    }

    // std::cout << "Écarts : "
    //       << " Gregaire: " << ecartGregaire
    //       << ", Peureux: " << ecartPeureux
    //       << ", Kamikaze: " << ecartKamikaze
    //       << ", Prevoyant: " << ecartPrevoyante
    //       << ", Multiple: " << ecartMultiple
    //       << std::endl;



    // Définition du comportement de la bestiole
    bestiole->setComportement(comportementChoisi.createur());
    // std::cout << "Comportement choisi : " << typeid(*bestiole->getComportement()).name() << std::endl;


    return bestiole;
}