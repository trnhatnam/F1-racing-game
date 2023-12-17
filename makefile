run_red: 
	g++ -c main_red.cpp  ; g++ voiture.cpp AffichageDonnees.cpp main_red.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app

run_ter: 
	g++ -c main_ter.cpp  ; g++ voiture.cpp main_ter.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app

run : 
	g++ -c main.cpp  ; g++ jeu.cpp  main.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app
clean:
	rm -f sfml-app *.o