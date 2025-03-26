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


// Initialize static instance
BestioleFactory* BestioleFactory::instance = nullptr;


BestioleFactory::BestioleFactory() {
    //factory = AccessoireFactory::getInstance();
    // cout<<"Factory Creer "<<endl;
}

double BestioleFactory::random_between(double a, double b) {
    // Générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());

    // Distribution uniforme entre a et b
    std::uniform_real_distribution<double> dist(a, b);

    return dist(gen);
}

//BestioleFactory::BestioleFactory(Configuration* Configuration::) : Configuration::(Configuration::) {
    //factory = AccessoireFactory::getInstance();
//}

BestioleFactory::~BestioleFactory()
{
    // Si la factory gère des ressources internes, les libérer ici
   
    // cout<<"Factory  "<<endl;
    // Pas besoin de détruire les bestioles, elles sont gérées par des std::unique_ptr
}


BestioleFactory* BestioleFactory::getInstance() {
    if (instance == nullptr) {
        instance = new BestioleFactory();
    }
    return instance;
}

int BestioleFactory::initialiserAttributsAgeLimite()
{
    // Récupération de la configuration
    int ageLimiteMax = Configuration::VIE*1.2 ;
    int ageLimiteMin = Configuration::VIE*1.2 ;
    int ageLimite = rand() % (ageLimiteMax- ageLimiteMin + 1) + ageLimiteMin;

    

    return ageLimite ;
 
};

double BestioleFactory::initialiserAttributsVitesse()
{

    double vitesse = static_cast<double>(rand()) / RAND_MAX * Configuration::MAX_VITESSE;

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
    
    std::vector<std::unique_ptr<Bestiole>> population;
    int age_limite;
    double vitesse ;

    // Liste Aléotoire
    std::vector<int>  listeO = generate_shuffled_list(nombreTotal) ;
    
    std::vector<int>  listeY = generate_shuffled_list(nombreTotal) ;

    std::vector<int>  listeBestioleAccessoires = generate_shuffled_list(nombreTotal) ;

    // Calculer le nombre de bestioles pour chaque comportement
    int nbGregaires = static_cast<int>(nombreTotal * Configuration::TAUX_GREGAIRE);
    int nbPeureuses = static_cast<int>(nombreTotal * Configuration::TAUX_PEUREUSE);
    int nbKamikazes = static_cast<int>(nombreTotal * Configuration::TAUX_KAMIKAZE);
    int nbPrevoyantes = static_cast<int>(nombreTotal * Configuration::TAUX_PREVOYANTE);
    int nbMultiples = nombreTotal - (nbGregaires + nbPeureuses + nbKamikazes + nbPrevoyantes);

    // std::cout << "Nombre de bestioles gregaires : " << nbGregaires << std::endl;
    // std::cout << "Nombre de bestioles peureuses : " << nbPeureuses << std::endl;
    // std::cout << "Nombre de bestioles kamikazes : " << nbKamikazes << std::endl;
    // std::cout << "Nombre de bestioles prevoyantes : " << nbPrevoyantes << std::endl;
    // std::cout << "Nombre de bestioles multiples : " << nbMultiples << std::endl;

    // std::cout << "Création des gregaires" << std::endl;
    // Créer les bestioles grégaires
    for (int i = 0; i < nbGregaires; ++i) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementGregaire>(new ComportementGregaire()).release());
        population.push_back(std::move(bestiole));
    }

    // std::cout << "Création des peureuses" << std::endl;
    // Créer les bestioles peureuses
    for (int i = 0; i < nbPeureuses; ++i) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementPeureux>(new ComportementPeureux()).release());
        population.push_back(std::move(bestiole));
    }

    // std::cout << "Création des kamikaazes" << std::endl;
    // Créer les bestioles kamikazes
    for (int i = 0; i < nbKamikazes; ++i) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementKamikaze>(new ComportementKamikaze()).release());
        population.push_back(std::move(bestiole));
        
    }

    // std::cout << "Création des prevoyantes" << std::endl;
    // Créer les bestioles prévoyantes
    for (int i = 0; i < nbPrevoyantes; ++i) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementPrevoyant>(new ComportementPrevoyant()).release());
        population.push_back(std::move(bestiole));
    }

    // Créer les bestioles multiples
    for (int i = 0; i < nbMultiples; ++i) {
        
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementMultiple>(new ComportementMultiple()).release());
        population.push_back(std::move(bestiole));
    }

    // Calculer le nombre de bestioles avec des capteurs
    int nbBestiolesAvecCapteurs = static_cast<int>(nombreTotal * Configuration::TAUX_CAPTEURS);
    // std::cout << "Nombre de bestioles avec capteurs : " << nbBestiolesAvecCapteurs << std::endl;

    // Calculer le nombre de Yeux et Oreilles en fonction des proportions
    int nbYeux = static_cast<int>(nbBestiolesAvecCapteurs * Configuration::TAUX_YEUX);
    int nbOreilles = static_cast<int>(nbBestiolesAvecCapteurs * Configuration::TAUX_OREILLES);
    // std::cout << "Nombre de bestioles avec Yeux : " << nbYeux << std::endl;
    // std::cout << "Nombre de bestioles avec Oreilles : " << nbOreilles << std::endl;

    // std::cout << "Création des Yeux" << std::endl;
    // Ajouter des Yeux aux bestioles
    for (int i = 0; i < nbYeux; ++i) {
        double angle = random_between(Configuration::MIN_ALPHA, Configuration::MIN_ALPHA);
        double delta = random_between(Configuration::MIN_DELTA_Y, Configuration::MAX_DELTA_Y);
        double gama = random_between(Configuration::MIN_GAMMA_Y, Configuration::MAX_GAMMA_Y);
        population[listeY[i]]->ajouterCapteur(std::unique_ptr<ICapteur>(new Yeux(angle, delta, gama)));

    }

    // std::cout << "Création des Oreilles" << std::endl;
    // Ajouter des Oreilles aux bestioles
    for (int i = 0; i <  nbOreilles; ++i) {
        double delta = random_between(Configuration::MAX_DELTA_O, Configuration::MIN_DELTA_O);
        double gama = random_between(Configuration::MIN_GAMMA_O, Configuration::MAX_GAMMA_O);
        population[listeO[i]]->ajouterCapteur(std::unique_ptr<ICapteur>(new Oreilles(delta, gama)));
    }

    // std::cout << "Création des accessoires" << std::endl;
    //Ajouter des Accessoires
     // Ajouter des accessoires aléatoires
    int nbBestiolesAvecAccessoires = static_cast<int>(nombreTotal * Configuration::TAUX_ACCESSOIRES);
    for (int i = 0; i <  nbBestiolesAvecAccessoires; ++i) {
        IAccessoire* accessoire = AccessoireFactory::getInstance()->createRandomAccessoire();
        population[listeBestioleAccessoires[i]]->ajouterAccessoire(accessoire);
    }

    // Vérifier si la population est bien remplie
    // std::cout << "Nombre de bestioles créées : " << population.size() << std::endl;


    return population;
}

// Création d'une bestiole avec des capteurs aléatoires
std::unique_ptr<Bestiole> BestioleFactory::createBestioleWithRandomBestiole() {
    // cout<<"create Random Bestiole"<<endl;
    int age_limite = initialiserAttributsAgeLimite();
    double vitesse = initialiserAttributsVitesse();
    
    auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse)); 

    //Ajouter Random Comportement
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
            // cout<<"ComportementMultiple a implementer"<<endl;
        default:
            // cout<<"Pas de comportement ajouter "<<randomValue <<endl;
    }

    // Determine if bestiole will have eyes based on configuration
    if ((static_cast<double>(rand()) / RAND_MAX) < Configuration::TAUX_CAPTEURS) {
        // Add eyes
        
        double angle = random_between(Configuration::MIN_ALPHA, Configuration::MIN_ALPHA);
        double delta = random_between(Configuration::MIN_DELTA_Y, Configuration::MAX_DELTA_Y);
        double gama = random_between(Configuration::MIN_GAMMA_Y, Configuration::MAX_GAMMA_Y);
        bestiole->ajouterCapteur(std::unique_ptr<ICapteur>(new Yeux(angle, delta, gama)));

    }
    
    // Determine if bestiole will have ears based on configuration
    if ((static_cast<double>(rand()) / RAND_MAX) < Configuration::TAUX_CAPTEURS) {
        // Add ears
        
        double delta = random_between(Configuration::MAX_DELTA_O, Configuration::MIN_DELTA_O);
        double gama = random_between(Configuration::MIN_GAMMA_O, Configuration::MAX_GAMMA_O);
        bestiole->ajouterCapteur(std::unique_ptr<ICapteur>(new Oreilles(delta, gama)));
      
    }
    
    // Ajouter des accessoires
    // Determine if bestiole will have eyes based on configuration
    if ((static_cast<double>(rand()) / RAND_MAX) < Configuration::TAUX_ACCESSOIRES)
    {
        IAccessoire* accessoire = AccessoireFactory::getInstance()->createRandomAccessoire();
        bestiole->ajouterAccessoire(accessoire);
    }

    return bestiole;
}

std::unique_ptr<IBestiole> BestioleFactory::cloneBestiole(const IBestiole& bestioleToClone) {
    return std::unique_ptr<IBestiole>(bestioleToClone.clone());
}

std::vector<std::unique_ptr<IBestiole>> BestioleFactory::ajouterBestiole(const std::vector<IBestiole*>& population, int nombre) {
    std::vector<std::unique_ptr<IBestiole>> nouvellesBestioles;
    
    for (int i = 0; i < nombre; ++i) {
        auto nouvelleBestiole = createBestioleWithRandomBestiole();
        
        // Vérifier les ratios actuels de comportements dans la population
        int nbTotal = population.size();
        int nbGregaires = 0, nbPeureuses = 0, nbKamikazes = 0, nbPrevoyantes = 0, nbMultiples = 0;

        for (const auto& bestiole : population) {
            if (dynamic_cast<ComportementGregaire*>(dynamic_cast<Bestiole*>(bestiole)->getComportement())) {
                nbGregaires++;
            } else if (dynamic_cast<ComportementPeureux*>(dynamic_cast<Bestiole*>(bestiole)->getComportement())) {
                nbPeureuses++;
            } else if (dynamic_cast<ComportementKamikaze*>(dynamic_cast<Bestiole*>(bestiole)->getComportement())) {
                nbKamikazes++;
            } else if (dynamic_cast<ComportementPrevoyant*>(dynamic_cast<Bestiole*>(bestiole)->getComportement())) {
                nbPrevoyantes++;
            } else if (dynamic_cast<ComportementMultiple*>(dynamic_cast<Bestiole*>(bestiole)->getComportement())) {
                nbMultiples++;
            }
        }

        // Calculer les taux actuels
        double tauxGregaire = static_cast<double>(nbGregaires) / nbTotal;
        double tauxPeureux = static_cast<double>(nbPeureuses) / nbTotal;
        double tauxKamikaze = static_cast<double>(nbKamikazes) / nbTotal;
        double tauxPrevoyante = static_cast<double>(nbPrevoyantes) / nbTotal;
        double tauxMultiple = static_cast<double>(nbMultiples) / nbTotal;

        // Vérifier si l'ajout respecte les ratios de configuration
        bool respecteRatios = 
            (std::abs(tauxGregaire - Configuration::TAUX_GREGAIRE) < 0.1) &&
            (std::abs(tauxPeureux - Configuration::TAUX_PEUREUSE) < 0.1) &&
            (std::abs(tauxKamikaze - Configuration::TAUX_KAMIKAZE) < 0.1) &&
            (std::abs(tauxPrevoyante - Configuration::TAUX_PREVOYANTE) < 0.1) &&
            (std::abs(tauxMultiple - Configuration::TAUX_MULTIPLE) < 0.1);

        if (respecteRatios) {
            // Ajouter la nouvelle bestiole à la liste des nouvelles bestioles
            nouvellesBestioles.push_back(std::move(nouvelleBestiole));
        } else {
            // Ajuster le comportement de la nouvelle bestiole 
            // pour respecter les proportions configurées
            std::unique_ptr<Bestiole> bestioleAjustee = ajusterComportementSelonRatios(std::move(nouvelleBestiole), population);
            nouvellesBestioles.push_back(std::move(bestioleAjustee));
        }
    }

    return nouvellesBestioles;
}

std::unique_ptr<Bestiole> BestioleFactory::ajusterComportementSelonRatios(
    std::unique_ptr<Bestiole> bestiole, 
    const std::vector<IBestiole*>& population) 
{
    // Calculer les taux réels de comportements dans la population
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

    // Calculer les taux réels
    double tauxGregaire = static_cast<double>(nbGregaires) / nbTotal;
    double tauxPeureux = static_cast<double>(nbPeureuses) / nbTotal;
    double tauxKamikaze = static_cast<double>(nbKamikazes) / nbTotal;
    double tauxPrevoyante = static_cast<double>(nbPrevoyantes) / nbTotal;
    double tauxMultiple = static_cast<double>(nbMultiples) / nbTotal;

    // Calculer les écarts par rapport aux taux de configuration
    double ecartGregaire = std::abs(tauxGregaire - Configuration::TAUX_GREGAIRE);
    double ecartPeureux = std::abs(tauxPeureux - Configuration::TAUX_PEUREUSE);
    double ecartKamikaze = std::abs(tauxKamikaze - Configuration::TAUX_KAMIKAZE);
    double ecartPrevoyante = std::abs(tauxPrevoyante - Configuration::TAUX_PREVOYANTE);
    double ecartMultiple = std::abs(tauxMultiple - Configuration::TAUX_MULTIPLE);

    // Tableau des écarts et des types de comportements
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

    // Trouver le comportement avec l'écart maximum
    ComportementEcart comportementChoisi = comportements[0];
    for (const auto& comp : comportements) {
        if (comp.ecart > comportementChoisi.ecart) {
            comportementChoisi = comp;
        }
    }

    // Définir le comportement de la bestiole
    bestiole->setComportement(comportementChoisi.createur());

    return bestiole;
}