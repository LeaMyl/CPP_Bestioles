<<<<<<< HEAD
main : main.cpp Aquarium.o Bestiole.o Milieu.o
	g++ -Wall -std=c++14 -o main main.cpp Aquarium.o Bestiole.o Milieu.o -I . -I /opt/X11/include -lX11 -lpthread -L /opt/X11/lib
	
=======
main : main.cpp Aquarium.o Bestiole.o Milieu.o Capteurs.o
	g++ -Wall -std=c++11 -o main main.cpp Aquarium.o Bestiole.o Milieu.o Capteurs.o -I . -lX11 -lpthread

>>>>>>> 5313af5 (d)
Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Capteurs.o : Capteurs.h Capteurs.cpp
	g++ -Wall -std=c++11  -c Capteurs.cpp -I .
clean:
	rm -rf *.o main

