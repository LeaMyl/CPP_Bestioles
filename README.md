# Projet Bestioles

## I/Présentation du projet
Ce projet permet de simuler un écosystème de "bestioles" qui possèdent des caractéristiques différentes et leurs interactions entre elles et avec leur milieu (un aquarium).
Les bestioles peuvent être dotées (ou non) de capteurs (oreilles et/ou yeux) qui leur permettent de détecter les autres bestioles à proximité. Elles possèdent aussi une personnalité (grégaire, peureuse, prévoyante, kamikaze ou à personnalités multiples) qui influe sur leur comportement envers ces dernières. Elles peuvent également être munies d'accessoires (nageoires, carapace et/ou camouflage) qui permettent respectivement de se déplacer plus vite, de mieux résister aux collisions avec les autres bestioles (cela entraîne toutefois une réduction de la vitesse de déplacement) et d'être moins bien détectées par les bestioles environnantes.
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

## III.3/Gestion de la proportion des capteurs 
De plus, on peut décider de la proportion de bestioles possédant un/des capteur(s) en modifiant la valeur de TAUX_CAPTEURS. <b>Celle-ci doit être comprise entre 0 et 3.</b> A cela s'ajoute la possibilité de modifier le pourcentage (pour les bestioles munies de capteur(s)) de possession d'yeux (en modifiant la valeur de TAUX_YEUX) et de possession d'oreilles (en modifiant la valeur de TAUX_OREILLES). <b>A noter que leus valeurs sont comprises entre 0 et 3 et que leur somme n'a pas d'obligation de valoir 3 puisque les bestioles peuvent posséder des oreilles ET des yeux.</b>

## III.4/Gestion des caractéristiques des capteurs
<b>A noter, pour des raisons évidentes que pour tout les paramètres avec une valeur MIN et une valeur MAX, la valeur MIN doit être inférieure à la valeur MAX.</b> 


L'utilisateur peut décider de l'étendue de la zone où les bestioles peuvent entendre en jouant sur les valeurs de MIN_DELTA_O et MAX_DELTA_O représentant respectivement la distance minimale et la distance maximale jusqu'à laquelle les bestioles générées peuvent entendre. Il peut également modifier MIN_GAMMA_O et MAX_GAMMA_O représentant respectivement la capacité (ou probabilité) de détection minimale et de détection maximale des bestioles situées à une distance inférieure ou égale à delta.

Quant aux yeux, ils sont gérés d'une part par les paramètres MIN_DELTA_Y, MAX_DELTA_Y, MIN_GAMMA_Y et MAX_GAMMA_Y qui fonctionnent exactement de la même manière que leurs homologues pour les oreilles et d'autre part par les paramètres MIN_ALPHA et MAX_ALPHA. Ces derniers permettent de gérer la plage du champ angulaire des bestioles générées (tandis que les oreilles étaient considérées comme efficientes à 360°).

## III.5/Gestion de la proportion des accessoires
Modifier la valeur de TAUX_ACCESSOIRES permet de modifier la proportion de bestioles munies d'accessoires. <b>A noter que sa valeur doit être comprise entre 0 et 3. Contrairement aux capteurs, il n'est pas possible de choisir le taux de chaque type de capteur. Pour chaque bestiole possédant un capteur, le choix de celui-ci se fait aléatoirement.</b>


## III.6/Gestion des paramètres des accessoires
L'utilisateur peut modifier la valeur maximale que peut prendre le coefficient multiplicateur des <b>nageoires</b> des bestioles qui en possèdent en changeant la valeur de MAX_NU. <b>Il est évident que celle-ci doit être strictement supérieure à 1.</b>

Concernant les <b>carapaces</b>, il est possible d'influer sur la probabilité de mort suite à une collision des bestioles qui en sont munies (donnée par l'inverse de oméga). La valeur de MAX_OMEGA correspond donc à la réduction maximale de probabilité de mort en collision des bestioles possédant une carapace. On peut aussi gérer le ralentissement maximal entraîné par la carapace via MAX_ETA. <b>MAX_OMEGA et MAX_ETA doivent donc être strictement supérieurs à 1.</b>

Enfin, la gestion de la plage de valeurs que peuvent prendre les <b>camouflages</b> se fait en modifiant les valeurs de MIN_PSI et MAX_PSI respectivement le coefficient de camouflage minimal et maximal.

## III.7/Gestion des paramètres de reproduction et de survie

## III.8/Autres paramètres modifiables

## IV/Fonctionnalités lors de l'exécution de la simulation
Voici les différentes possibilités offertes à l'utilisateur au cours de l'exécution de la simulation et les commandes associées :
    // - ESC : fermer la fenêtre
    // - N : ajouter des bestioles
    // - M : supprimer des bestioles
    // - ESPACE : mettre en pause/reprendre
    // - I : afficher les informations
    // - F : afficher/masquer les champs de vision

 ## V/Configuration de secours
 S'il arrivait à l'utilisateur de rentrer des valeurs incohérentes qui empêcheraient l'exécution de la simulation, de rencontrer un quelconque problème avec sa configuration personnalisée ou s'il souhaite simplement revenir à la configuration par défaut, cette dernière est accessible dans le dossier CPP_Bestioles.


## Auteurs : Sara Adi, Marine Delabaere, Titouan Dupasquier, Mouhamed Leye et Léa Miqueu
## Projet académique réalisé dans le cadre de l'UE H "Advanced C++ Programming" proposée par IMT Atlantique (Ecole nationale supérieure Mines-Télécom Atlantique Bretagne Pays de la Loire) et encadrée par Reda Bellafqira, Didier Guériot et Johanne Vincent
