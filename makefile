run_red : 
	g++ -c main_red.cpp  ; g++ AffichageDonnees.cpp obstacle.cpp voiture.cpp main_red.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app

run : 
	g++ -c main.cpp  ; g++ AffichageDonnees.cpp bonus.cpp obstacle.cpp voiture.cpp jeu.cpp main.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app

clean:
	rm -f sfml-app *.o