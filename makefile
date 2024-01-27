all : run

run : 
	g++ -c main.cpp  ; g++ AffichageDonnees.cpp bonus.cpp FeuDepart.cpp obstacle.cpp voiture.cpp jeu.cpp main.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app

clean:
	rm -f sfml-app *.o