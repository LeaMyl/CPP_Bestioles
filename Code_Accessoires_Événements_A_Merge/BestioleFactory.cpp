#include "BestioleFactory.h"

// Initialize static instance
BestioleFactory* BestioleFactory::instance = nullptr;

// Constructeur de base
BestioleFactory::BestioleFactory(){
    factory = AccessoireFactory::getInstance();
}
   
// Destructeur de base
BestioleFactory::~BestioleFactory(){
    delete factory;
}

// Création d'une bestiole basique
Bestiole BestioleFactory::createBestiole(){
    return Bestiole();
}

// Création d'une bestiole avec un accessoire
Bestiole BestioleFactory::createBestiole(IAccessoire* accessoire){
    Bestiole b;
    b.ajouterAccessoire(accessoire);
    return b;
}

BestioleFactory* BestioleFactory::getInstance() {
    if (instance == nullptr) {
        instance = new BestioleFactory();
    }
    return instance;
}

// Création d'une bestiole avec des capteurs aléatoires
Bestiole BestioleFactory::createBestioleWithRandomSensors() {
    Bestiole b;
    
    // Determine if bestiole will have eyes based on configuration
    if ((static_cast<double>(rand()) / RAND_MAX) < Configuration::TAUX_CAPTEURS) {
        // Add eyes
        b.ajouterCapteur(Yeux::generateRandomYeux());
    }
    
    // Determine if bestiole will have ears based on configuration
    if ((static_cast<double>(rand()) / RAND_MAX) < Configuration::TAUX_CAPTEURS) {
        // Add ears
        b.ajouterCapteur(Oreilles::generateRandomOreilles());
    }
    
    return b;
}