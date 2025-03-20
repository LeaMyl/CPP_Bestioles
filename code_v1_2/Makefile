# Règle pour créer l'exécutable final
main : main.cpp Aquarium.o Bestiole.o Milieu.o ComportementGregaire.o ComportementPeureux.o ComportementKamikaze.o Configuration.o
	g++ -Wno-deprecated-declarations -std=c++14 -o main main.cpp Aquarium.o Bestiole.o Milieu.o ComportementGregaire.o ComportementPeureux.o ComportementKamikaze.o Configuration.o -I . -I /opt/X11/include -lX11 -lpthread -L /opt/X11/lib

# Règle pour compiler Aquarium.o
Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Aquarium.cpp -I .

# Règle pour compiler Bestiole.o
Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Bestiole.cpp -I .

# Règle pour compiler configuration.o
Configuration.o : Configuration.h Configuration.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Configuration.cpp -I .

# Règle pour compiler Milieu.o
Milieu.o : Milieu.h Milieu.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Milieu.cpp -I .

# Règle pour compiler ComportementGregaire.o
ComportementGregaire.o : ComportementGregaire.h ComportementGregaire.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c ComportementGregaire.cpp -I .

# Règle pour compiler ComportementPeureux.o
ComportementPeureux.o : ComportementPeureux.h ComportementPeureux.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c ComportementPeureux.cpp -I .

# Règle pour compiler ComportementKamikaze.o
ComportementKamikaze.o : ComportementKamikaze.h ComportementKamikaze.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c ComportementKamikaze.cpp -I .

Capteurs.o : Capteurs.h Capteurs.cpp
	g++ -Wno-deprecated-declarations -std=c++11  -c Capteurs.cpp -I .
clean:	
	clear
	rm -rf *.o main

