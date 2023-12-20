
run_red : 
	g++ -c main_red.cpp  ; g++ AffichageDonnees.cpp voiture.cpp main_red.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app

run : 
	g++ -c main_nhatnam.cpp  ; g++ obstacle.cpp jeu.cpp main_nhatnam.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app
clean:
	rm -f sfml-app *.o