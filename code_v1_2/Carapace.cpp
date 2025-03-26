#include "Carapace.h"

// Énumération des types d'accessoires (cohérente entre les implémentations)
enum AccessoireType { NAGEOIRES = 1, CARAPACE = 2, CAMOUFLAGE = 3 };

// Constructeur avec valeurs par défaut pour résistance et réduction
Carapace::Carapace(double resistance, double reduction) 
    : coeffResistance(resistance), coeffReduction(reduction) {
    // Initialisation directe par liste d'initialisation
}

// Destructeur (vide car pas de gestion de mémoire dynamique)
Carapace::~Carapace() {
}

// Modifier la vitesse en divisant par le coefficient de réduction
double Carapace::modulerVitesse(double vitesse) const {
    // Réduit la vitesse proportionnellement au coefficient de réduction
    return vitesse / coeffReduction;
}

// Modifier la probabilité de mort en divisant par le coefficient de résistance
double Carapace::modulerResistance(double proba) const {
    // Augmente la probabilité de survie en réduisant la probabilité de mort
    return proba / coeffResistance;
}

// Aucun effet de camouflage pour la carapace
double Carapace::getCoeffCamoufflage() const {
    return 0.0;
}

// Créer une copie profonde de la carapace
IAccessoire* Carapace::clone() const {
    return new Carapace(*this);
}

// Identifier le type d'accessoire pour la visualisation
int Carapace::getType() const {
    return CARAPACE;
}

// Accesseur du coefficient de résistance
double Carapace::getCoeffResistance() const {
    return coeffResistance;
}

// Modificateur du coefficient de résistance avec validation minimale
void Carapace::setCoeffResistance(double coeff) {
    // Garantir que le coefficient est au moins de 1.0
    coeffResistance = (coeff < 1.0) ? 1.0 : coeff;
}

// Accesseur du coefficient de réduction
double Carapace::getCoeffReduction() const {
    return coeffReduction;
}

// Modificateur du coefficient de réduction avec validation minimale
void Carapace::setCoeffReduction(double coeff) {
    // Garantir que le coefficient est au moins de 1.0
    coeffReduction = (coeff < 1.0) ? 1.0 : coeff;
}