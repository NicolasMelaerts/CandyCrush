run:
	make main && ./main && rm *.o && rm main

main: main.cpp PlateauDeJeu.o Shapes.o ElementDeJeu.o Jeu.o
	g++ --std='c++17' -o main main.cpp PlateauDeJeu.o Shapes.o ElementDeJeu.o Jeu.o -lfltk

PlateauDeJeu.o: PlateauDeJeu.cpp PlateauDeJeu.hpp
	g++ -c --std='c++17' PlateauDeJeu.cpp

Shapes.o: Shapes.cpp Shapes.hpp
	g++ -c --std='c++17' Shapes.cpp

ElementDeJeu.o: ElementDeJeu.cpp ElementDeJeu.hpp
	g++ -c --std='c++17' ElementDeJeu.cpp

Jeu.o: Jeu.cpp Jeu.hpp 
	g++ -c --std='c++17' Jeu.cpp