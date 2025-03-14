// Bestiole.cpp
#include "Bestiole.h"
#include "Milieu.h"
#include "Configuration.h"

#include <cstdlib>
#include <cmath>

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_VITESSE = 10.;
const double Bestiole::LIMITE_VUE = 30.;

int Bestiole::next = 0;

Bestiole::Bestiole()
{
    identite = ++next;
    age = 0;
    
    // Récupération de la configuration
    Configuration* config = Configuration::getInstance();
    ageLimite = rand() % (config->ageLimiteMax - config->ageLimiteMin + 1) + config->ageLimiteMin;
    
    cout << "const Bestiole (" << identite << ") par defaut" << endl;

    x = y = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
    vitesse = static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE;

    couleur = new T[3];
    couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    
    comportement = nullptr;
}

Bestiole::Bestiole(const Bestiole& b)
{
    identite = ++next;
    age = 0;
    ageLimite = b.ageLimite;

    cout << "const Bestiole (" << identite << ") par copie" << endl;

    x = b.x;
    y = b.y;
    cumulX = cumulY = 0.;
    orientation = b.orientation;
    vitesse = b.vitesse;
    
    couleur = new T[3];
    memcpy(couleur, b.couleur, 3 * sizeof(T));
    
    // Copie des capteurs
    for (const auto& capteur : b.capteurs) {
        capteurs.push_back(capteur->clone());
    }
    
    // Copie des accessoires
    for (const auto& accessoire : b.accessoires) {
        accessoires.push_back(accessoire->clone());
    }
    
    // Copie du comportement
    if (b.comportement != nullptr) {
        comportement = b.comportement->clone();
    } else {
        comportement = nullptr;
    }
}

Bestiole::~Bestiole()
{
    delete[] couleur;
    
    // Libération des capteurs
    for (auto& capteur : capteurs) {
        delete capteur;
    }
    
    // Libération des accessoires
    for (auto& accessoire : accessoires) {
        delete accessoire;
    }
    
    // Libération du comportement
    if (comportement != nullptr) {
        delete comportement;
    }

    cout << "dest Bestiole" << endl;
}

void Bestiole::initCoords(int xLim, int yLim)
{
    x = rand() % xLim;
    y = rand() % yLim;
}

void Bestiole::bouge(int xLim, int yLim)
{
    double nx, ny;
    double dx = cos(orientation) * vitesse;
    double dy = -sin(orientation) * vitesse;
    int cx, cy;

    cx = static_cast<int>(cumulX); cumulX -= cx;
    cy = static_cast<int>(cumulY); cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;

    if ((nx < 0) || (nx > xLim - 1)) {
        orientation = M_PI - orientation;
        cumulX = 0.;
    }
    else {
        x = static_cast<int>(nx);
        cx = static_cast<int>(nx);
        cumulX += nx - x;
    }

    if ((ny < 0) || (ny > yLim - 1)) {
        orientation = -orientation;
        cumulY = 0.;
    }
    else {
        y = static_cast<int>(ny);
        cumulY += ny - y;
    }
}

void Bestiole::action(Milieu& monMilieu)
{
    // Appliquer le comportement si présent
    if (comportement != nullptr) {
        double nouvelleOrientation = comportement->calculerNouvelleDirection(*this, monMilieu);
        changeOrientation(nouvelleOrientation);
    }
    
    // Appliquer les accessoires sur la vitesse
    double vitesseModifiee = vitesse;
    for (const auto& accessoire : accessoires) {
        vitesseModifiee = accessoire->modulerVitesse(vitesseModifiee);
    }
    
    // Sauvegarder l'ancienne vitesse
    double ancienneVitesse = vitesse;
    vitesse = vitesseModifiee;
    
    // Déplacer la bestiole
    bouge(monMilieu.getWidth(), monMilieu.getHeight());
    
    // Restaurer la vitesse d'origine
    vitesse = ancienneVitesse;
    
    // Vieillir la bestiole
    vieillir();
}

void Bestiole::draw(UImg& support)
{
    double xt = x + cos(orientation) * AFF_SIZE / 2.1;
    double yt = y - sin(orientation) * AFF_SIZE / 2.1;

    support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5., -orientation / M_PI * 180., couleur);
    support.draw_circle(xt, yt, AFF_SIZE / 2., couleur);
}

bool Bestiole::jeTeVois(const IBestiole& b) const
{
    return detecte(b) && estDetectee(b);
}

bool Bestiole::detecte(const IBestiole& autre) const
{
    if (capteurs.empty()) {
        // Si aucun capteur, utiliser la détection par défaut
        auto pos = autre.getPosition();
        double dist = std::sqrt((x - pos.first) * (x - pos.first) + (y - pos.second) * (y - pos.second));
        return (dist <= LIMITE_VUE);
    }
    
    // Sinon, utiliser les capteurs
    for (const auto& capteur : capteurs) {
        if (capteur->detecte(*this, autre)) {
            return true;
        }
    }
    
    return false;
}

bool Bestiole::estDetectee(const IBestiole& autre) const
{
    // Calcul de la probabilité de détection en fonction du camouflage
    double coeff = getCoeffCamouflage();
    double proba = static_cast<double>(rand()) / RAND_MAX;
    
    return proba <= coeff;
}

double Bestiole::getCoeffCamouflage() const
{
    double coeff = 1.0; // Par défaut, pas de camouflage
    
    for (const auto& accessoire : accessoires) {
        double coeff_accessoire = accessoire->getCoeffCamoufflage();
        if (coeff_accessoire < coeff) {
            coeff = coeff_accessoire;
        }
    }
    
    return coeff;
}

void Bestiole::changeOrientation(double nouvelleOrientation)
{
    orientation = nouvelleOrientation;
    
    // Normaliser l'orientation entre 0 et 2π
    while (orientation < 0) orientation += 2 * M_PI;
    while (orientation >= 2 * M_PI) orientation -= 2 * M_PI;
}

void Bestiole::vieillir()
{
    age++;
}

bool Bestiole::meurt()
{
    return age >= ageLimite;
}

IBestiole* Bestiole::clone() const
{
    return new Bestiole(*this);
}

void Bestiole::ajouterCapteur(ICapteur* capteur)
{
    capteurs.push_back(capteur);
}

void Bestiole::ajouterAccessoire(IAccessoire* accessoire)
{
    accessoires.push_back(accessoire);
}

void Bestiole::setComportement(IComportement* comp)
{
    if (comportement != nullptr) {
        delete comportement;
    }
    comportement = comp;
}

bool operator==(const Bestiole& b1, const Bestiole& b2)
{
    return (b1.identite == b2.identite);
}