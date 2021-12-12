run:
	make main && ./main && rm PlateauDeJeu.o && rm Jeu.o && rm Animation.o && rm Shapes.o && rm ElementsDeJeu.o

main: main.cpp PlateauDeJeu.o Jeu.o Animation.o Shapes.o ElementsDeJeu.o
	g++ --std='c++17' -o main main.cpp PlateauDeJeu.o Jeu.o Animation.o Shapes.o ElementsDeJeu.o -lfltk


PlateauDeJeu.o: PlateauDeJeu.cpp PlateauDeJeu.hpp
	g++ -c --std='c++17' PlateauDeJeu.cpp

Jeu.o: Jeu.cpp Jeu.hpp 
	g++ -c --std='c++17' Jeu.cpp

Animation.o: Animation.cpp Animation.hpp
	g++ -c --std='c++17' Animation.cpp

Shapes.o: Shapes.cpp Shapes.hpp
	g++ -c --std='c++17' Shapes.cpp

ElementsDeJeu.o: ElementsDeJeu.cpp ElementsDeJeu.hpp
	g++ -c --std='c++17' ElementsDeJeu.cpp
