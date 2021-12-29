run:
	make main && ./main

main: main.cpp Afficher.o Animation.o Control.o ElementDeJeu.o Jeu.o Shapes.o Text.o Score.o
	g++ --std='c++17' -o main main.cpp Afficher.o Animation.o Control.o ElementDeJeu.o Jeu.o Shapes.o Text.o Score.o -lfltk

Afficher.o: Afficher.cpp Afficher.hpp
	g++ -c --std='c++17' Afficher.cpp

Animation.o: Animation.cpp Animation.hpp
	g++ -c --std='c++17' Animation.cpp

Control.o: Control.cpp Control.hpp
	g++ -c --std='c++17' Control.cpp

ElementDeJeu.o: ElementDeJeu.cpp ElementDeJeu.hpp
	g++ -c --std='c++17' ElementDeJeu.cpp

Jeu.o: Jeu.cpp Jeu.hpp 
	g++ -c --std='c++17' Jeu.cpp

Shapes.o: Shapes.cpp Jeu.hpp
	g++ -c --std='c++17' Shapes.cpp

Text.o: Text.cpp Text.hpp
	g++ -c --std='c++17' Text.cpp

Score.o: Score.cpp Score.hpp
	g++ -c --std='c++17' Score.cpp