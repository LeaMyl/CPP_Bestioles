main : main.cpp Aquarium.o Bestiole.o Milieu.o AccessoireFactory.o Nageoires.o Carapace.o Camouflage.o Configuration.o BestioleFactory.o Yeux.o Oreilles.o
	g++ -Wno-deprecated-declarations -std=c++14 -o main main.cpp Aquarium.o Bestiole.o Milieu.o AccessoireFactory.o Nageoires.o Carapace.o Camouflage.o Configuration.o BestioleFactory.o Yeux.o Oreilles.o -I . -I /opt/X11/include -lX11 -lpthread -L /opt/X11/lib
	
Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Milieu.cpp -I .

AccessoireFactory.o : AccessoireFactory.h AccessoireFactory.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c AccessoireFactory.cpp -I .

BestioleFactory.o : BestioleFactory.h BestioleFactory.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c BestioleFactory.cpp -I .

Nageoires.o : Nageoires.h Nageoires.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Nageoires.cpp -I .

Carapace.o : Carapace.h Carapace.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Carapace.cpp -I .

Camouflage.o : Camouflage.h Camouflage.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Camouflage.cpp -I .

Configuration.o : Configuration.h Configuration.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Configuration.cpp -I .

Yeux.o : Yeux.h Yeux.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Yeux.cpp -I .

Oreilles.o : Oreilles.h Oreilles.cpp
	g++ -Wno-deprecated-declarations -std=c++11 -c Oreilles.cpp -I .

clean:
	clear
	rm -rf *.o main