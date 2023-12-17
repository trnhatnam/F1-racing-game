run : 
	g++ -c main_nhatnam.cpp  ; g++ obstacle.cpp jeu.cpp main_nhatnam.o  -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app
clean:
	rm -f sfml-app *.o