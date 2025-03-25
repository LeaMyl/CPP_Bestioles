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

//BestioleFactory::BestioleFactory(Configuration* Configuration::) : Configuration::(Configuration::) {
    //factory = AccessoireFactory::getInstance();
//}

BestioleFactory::~BestioleFactory()
{
    // Si la factory gère des ressources internes, les libérer ici
   
    cout<<"Factory  "<<endl;
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

    // Créer les bestioles grégaires
    for (int i = 0; i < nbGregaires; ++i) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementGregaire>(new ComportementGregaire()).release());
        population.push_back(std::move(bestiole));
    }

    // Créer les bestioles peureuses
    for (int i = 0; i < nbPeureuses; ++i) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementPeureux>(new ComportementPeureux()).release());
        population.push_back(std::move(bestiole));
    }

    // Créer les bestioles kamikazes
    for (int i = 0; i < nbKamikazes; ++i) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementKamikaze>(new ComportementKamikaze()).release());
        population.push_back(std::move(bestiole));
        
    }

    // Créer les bestioles prévoyantes
    for (int i = 0; i < nbPrevoyantes; ++i) {
        age_limite = initialiserAttributsAgeLimite();
        vitesse = initialiserAttributsVitesse();
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementPrevoyant>(new ComportementPrevoyant()).release());
        population.push_back(std::move(bestiole));
    }
    // Vérifier si la population est bien remplie
    /*
    // Créer les bestioles multiples
    for (int i = 0; i < nbMultiples; ++i) {
        
        age_limite = initialiserAttributsAgeLimite(Configuration::);
        vitesse = initialiserAttributsVitesse(Configuration::);
        auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse));  
        bestiole->setComportement(std::unique_ptr<ComportementMultiple>(new ComportementMultiple()).release());
        population.push_back(std::move(bestiole));
    }
    */
    // Calculer le nombre de bestioles avec des capteurs
    int nbBestiolesAvecCapteurs = static_cast<int>(nombreTotal * Configuration::TAUX_CAPTEURS);

    // Calculer le nombre de Yeux et Oreilles en fonction des proportions
    int nbYeux = static_cast<int>(nbBestiolesAvecCapteurs * Configuration::TAUX_YEUX);
    int nbOreilles = static_cast<int>(nbBestiolesAvecCapteurs * Configuration::TAUX_OREILLES);

    //cout<< "nbBestiolesAvecCapteurs = "<<nbBestiolesAvecCapteurs<< " , nbYeux = " << nbYeux<< " nbOreilles = " <<nbOreilles<<endl;
    // Ajouter des Yeux aux bestioles
    for (int i = 0; i < nbYeux; ++i) {
        double angle = random_between(Configuration::MIN_ALPHA, Configuration::MIN_ALPHA);
        double delta = random_between(Configuration::MIN_DELTA_Y, Configuration::MAX_DELTA_Y);
        double gama = random_between(Configuration::MIN_GAMMA_Y, Configuration::MAX_GAMMA_Y);
        population[listeY[i]]->ajouterCapteur(std::unique_ptr<ICapteur>(new Yeux(angle, delta, gama)));

    }

    // Ajouter des Oreilles aux bestioles
    for (int i = 0; i <  nbOreilles; ++i) {
        double delta = random_between(Configuration::MAX_DELTA_O, Configuration::MIN_DELTA_O);
        double gama = random_between(Configuration::MIN_GAMMA_O, Configuration::MAX_GAMMA_O);
        population[listeO[i]]->ajouterCapteur(std::unique_ptr<ICapteur>(new Oreilles(delta, gama)));
    }


    //Ajouter des Accessoires
     // Ajouter des accessoires aléatoires
    int nbBestiolesAvecAccessoires = static_cast<int>(nombreTotal * Configuration::TAUX_ACCESSOIRES);
    for (int i = 0; i <  nbBestiolesAvecAccessoires; ++i) {
        IAccessoire* accessoire = AccessoireFactory::getInstance()->createRandomAccessoire();
        population[listeBestioleAccessoires[i]]->ajouterAccessoire(accessoire);
    }

    // Vérifier si la population est bien remplie
    std::cout << "Nombre de bestioles créées : " << population.size() << std::endl;


    return population;
}

// Création d'une bestiole avec des capteurs aléatoires
std::unique_ptr<Bestiole> BestioleFactory::createBestioleWithRandomBestiole() {
    cout<<"create Random Bestiole"<<endl;
    int age_limite = initialiserAttributsAgeLimite();
    double vitesse = initialiserAttributsVitesse();
    
    auto bestiole = std::unique_ptr<Bestiole>(new Bestiole(age_limite, vitesse)); 

    //Ajouter Random Comportement
    int randomValue = rand() % 5; 
    switch (randomValue) {
        case 1:
            
            bestiole->setComportement(std::unique_ptr<ComportementGregaire>(new ComportementGregaire()).release());
            
            break;
        case 2:
           
            bestiole->setComportement(std::unique_ptr<ComportementPeureux>(new ComportementPeureux()).release());
            
            break;
        case 3:
            
            bestiole->setComportement(std::unique_ptr<ComportementKamikaze>(new ComportementKamikaze()).release());
            break;
        case 4:
            bestiole->setComportement(std::unique_ptr<ComportementPrevoyant>(new ComportementPrevoyant()).release());
            break;
        case 5: 
            //bestiole->setComportement(std::unique_ptr<ComportementMultiple>(new ComportementMultiple()).release());
            cout<<"ComportementMultiple a implementer"<<endl;
        default:
            cout<<"Pas de comportement ajouter "<<randomValue <<endl;
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
