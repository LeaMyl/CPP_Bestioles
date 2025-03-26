# Projet Bestioles

## I/Présentation du projet
Ce projet permet de simuler un écosystème de "bestioles" qui possèdent des caractéristiques différentes et leurs interactions entre elles et avec leur milieu (un aquarium).
Les bestioles peuvent être dotées (ou non) de capteurs (oreilles et/ou yeux) qui leur permettent de détecter les autres bestioles à proximité. Elles possèdent aussi une personnalité (grégaire, peureuse, prévoyante, kamikaze ou à personnalités multiples) qui influe sur leur comportement envers ces dernières. Elles peuvent également être munies d'accessoires (nageoires, carapace et/ou camouflage) qui permettent respectivement de se déplacer plus vite, de mieux résister aux collisions avec les autres bestioles (cela entraîne toutefois une réduction de vitesse de déplacement) et d'être moins bien détectées pat les bestioles environnantes.
Les bestioles naissent, meurent (notamment lors des collisions) et peuvent s'auto-cloner.

## II/Lancement de la simulation
Pour lancer la simulation, il suffit d'ouvrir un terminal et d'exécuter le makefile (commande make). Il est recommandé d'utiliser la commande make clean afin  de supprimer les éventuels fichiers .o précédemment générés et ainsi d'éviter de potentiels conflits avec d'anciennes versions compilées et de libérer de l'espace en supprimant des fichiers inutiles. 
<b>Il est fortement déconseillé de modifier le makefile car il impose certaines versions de plusieurs bibliothèques utilisées sans lesquelles le code ne peut s'exécuter.</b> 
Il faut ensuite exécuter la simulation avec la commande ./main qui fait apparaître la fenêtre de simulation (gérée par la bibliothèque CImg). On peut alors observer les bestioles évoluer dans leur environnement et interagir entre elles.

## III/Gestion des paramètres de la simulation
En réalisant l'étape précédente, l'utilisateur lance la simulation avec des paramètres par défaut. Cependant, il a la possibilité de choisir les différents paramètres de celle-ci. Pour ce faire, il lui suffit d'ouvrir le fichier Configuration.cpp. 

## III.1/Gestion du nombre de bestioles 
Tout d'abord, il peut choisir le nombre de bestioles à générer initialement en modifiant la valeur de NOMBRE_BESTIOLES.

## III.2/Gestion de la proportion des comportements
Il est également possible de gérer la proportion en termes de comportements des bestioles générées, en modifiant les valeurs de TAUX_GREGAIRE, TAUX_PEUREUSE, TAUX_KAMIKAZE, TAUX_PREVOYANTE et TAUX_MULTIPLE. <b>Pour des raisons évidentes, leurs valeurs doivent être comprises entre 0 et 6 et leur somme doit être égale à 6.</b> A noter que le comportement d'une bestiole peut être identifié grâce à sa couleur (bleu pour grégaire, rouge pour peureuse, orange pour kamikaze, vert pour prévoyante et violet pour multiple).

## III.3/Gestion de la proportion de capteurs 
De plus, on peut décider de la proportion de bestioles possédant un/des capteur(s) en modifiant la valeur de TAUX_CAPTEURS. <b>Celle-ci doit être comprise entre 0 et 3.</b> A cela s'ajoute la possibilité de modifier le pourcentage (pour les bestioles munies de capteur(s)) de possession d'yeux (en modifiant la valeur de TAUX_YEUX) et de possession d'oreilles (en modifiant la valeur de TAUX_OREILLES). <b>A noter que leus valeurs sont comprises entre 0 et 3 et que leur somme n'a pas d'obligation de valoir 3 puisque les bestioles peuvent posséder des oreilles ET des yeux.</b>

## III.4/Gestion de la proportion d'accessoires
Modifier la valeur de TAUX_ACCESSOIRES permet de modifier la proportion de bestioles munies d'accessoires. <b>A noter que sa valeur doit être comprise entre 0 et 3. Contrairement aux capteurs, il n'est pas possible de choisir le taux de chaque type de capteur. Pour chaque bestiole possédant un capteur, le choix de celui-ci se fait aléatoirement.</b>

## III.5/

## III.6/

## III.7/

## III.8/

## III.9/Autres paramètres modifiables



configuration dans le dossier CPP Bestioles si besoin de revenir aux parametres initiaux
 // Menu interactif de simulation :
    // - ESC : fermer la fenêtre
    // - N : ajouter des bestioles
    // - M : supprimer des bestioles
    // - ESPACE : mettre en pause/reprendre
    // - I : afficher les informations
    // - F : afficher/masquer les champs de vision

## Auteurs : Sara Adi, Marine Delabaere, Titouan Dupasquier, Mouhamed Leye et Léa Miqueu
## Projet académique réalisé dans le cadre de l'UE H "Advanced C++ Programming" proposée par IMT Atlantique et encadrée par Reda Bellafqira, Didier Guériot et Johanne Vincent
