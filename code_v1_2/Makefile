# Règle pour créer l'exécutable final
main : main.cpp Aquarium.o Bestiole.o Milieu.o ComportementGregaire.o ComportementPeureux.o ComportementKamikaze.o  Configuration.o ComportementPrevoyant.o BestioleFactory.o Yeux.o Oreilles.o AccessoireFactory.o Nageoires.o Carapace.o Camouflage.o 
	g++ -Wno-deprecated-declarations -g -std=c++14 -o main main.cpp Aquarium.o Bestiole.o Milieu.o ComportementGregaire.o ComportementPeureux.o ComportementKamikaze.o ComportementPrevoyant.o Configuration.o BestioleFactory.o Yeux.o Oreilles.o AccessoireFactory.o Nageoires.o Carapace.o Camouflage.o  -I . -lX11 -lpthread
# Règle pour compiler Aquarium.o
Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Aquarium.cpp -I .

# Règle pour compiler Bestiole.o
Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Bestiole.cpp -I .

# Règle pour compiler configuration.o
Configuration.o : Configuration.h Configuration.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Configuration.cpp -I .

# Règle pour compiler Milieu.o
Milieu.o : Milieu.h Milieu.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Milieu.cpp -I .

# Règle pour compiler ComportementGregaire.o
ComportementGregaire.o : ComportementGregaire.h ComportementGregaire.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c ComportementGregaire.cpp -I .

# Règle pour compiler ComportementGregaire.o
ComportementMultiple.o : ComportementMultiple.h ComportementMultiple.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c ComportementMultiple.cpp -I .


# Règle pour compiler ComportementPeureux.o
ComportementPeureux.o : ComportementPeureux.h ComportementPeureux.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c ComportementPeureux.cpp -I .

# Règle pour compiler ComportementPrevoyant.o
ComportementPrevoyant.o : ComportementPrevoyant.h ComportementPrevoyant.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c ComportementPrevoyant.cpp -I .

# Règle pour compiler ComportementKamikaze.o
ComportementKamikaze.o : ComportementKamikaze.h ComportementKamikaze.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c ComportementKamikaze.cpp -I .

Capteurs.o : Capteurs.h Capteurs.cpp
	g++ -Wno-deprecated-declarations -std=c++14  -c Capteurs.cpp -I .

# Règle pour compiler BestioleFactory.o
BestioleFactory.o : BestioleFactory.h BestioleFactory.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c BestioleFactory.cpp -I .


# Règle pour compiler BestioleFactory.o
Yeux.o : Yeux.h Yeux.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Yeux.cpp -I .


Oreilles.o : Oreilles.h Oreilles.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Oreilles.cpp -I .

AccessoireFactory.o : AccessoireFactory.h AccessoireFactory.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c AccessoireFactory.cpp -I .

Nageoires.o : Nageoires.h Nageoires.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Nageoires.cpp -I .

Carapace.o : Carapace.h Carapace.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Carapace.cpp -I .

Camouflage.o : Camouflage.h Camouflage.cpp
	g++ -Wno-deprecated-declarations -std=c++14 -c Camouflage.cpp -I .

clean:	
	clear
	rm -rf *.o main

