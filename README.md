# Projet Bestioles

## Présentation du projet
Ce projet permet de simuler un écosystème de "bestioles" qui possèdent des caractéristiques différentes et leurs interactions entre elles et avec leur milieu (un aquarium).
Les bestioles peuvent être dotées (ou non) de capteurs (oreilles et/ou yeux) qui leur permettent de détecter les autres bestioles à proximité. Elles possèdent aussi une personnalité (grégaire, peureuse, prévoyante, kamikaze ou à personnalités multiples) qui influe sur leur comportement envers ces dernières. Elles peuvent également être munies d'accessoires (nageoires, carapace et/ou camouflage) qui permettent respectivement de se déplacer plus vite, de mieux résister aux collisions avec les autres bestioles (cela entraîne toutefois une réduction de vitesse de déplacement) et d'être moins bien détectées pat les bestioles environnantes.
Les bestioles naissent, meurent (notamment lors des collisions) et peuvent s'auto-cloner.

## Lancement de la simulation
Pour lancer la simulation, il suffit d'ouvrir un terminal et d'exécuter le makefile (commande make). Il est recommandé d'utiliser la commande make clean afinil  de supprimer les éventuels fichiers .o précédemment générés et ainsi d'éviter de potentiels conflits avec d'anciennes versions compilées et de libérer de l'espace en supprimant des fichiers inutiles. Il est fortement déconseillé de modifier le makefile car il impose certaines versions de plusieurs bibliothèques utilisées sans lesquelles le code ne peut s'exécuter. Il faut ensuite exécuter la simulation avec la commande ./main qui fait apparaître la fenêtre de simulation (gérée par la bibliothèque CImg). On peut alors observer les bestioles évoluer dans leur environnement et interagir entre elles.

## Gestion des paramètres de la simulation
En réalisant l'étape précédente, l'utilisateur lance la simulation avec des paramètres par défaut. Cependant, il a la possibilité de choisir les différents paramètres de celle-ci. Pour ce faire, il lui suffit d'ouvrir le fichier Configuration.cpp. Tout d'abord, il peut choisir le nombre de bestioles à générer initialement en modifiant la valeur de NOMBRE_BESTIOLES.la proportion en termes de comportements des bestioles générées, en modifiant 

## Auteurs : Sara Adi, Marine Delabaere, Titouan Dupasquier, Mouhamed Leye, Léa Miqueu
## Projet académique réalisé dans le cadre de l'UE H "Advanced C++ Programming" proposée par IMT Atlantique encadrée par Reda Bellafqira, Didier Guériot et Johanne Vincent
