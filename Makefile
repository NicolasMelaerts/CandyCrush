run:
	make main && ./main && rm plateau.o && rm jeu.o

main: main.cpp plateau.o jeu.o
	g++ --std='c++17' -o main main.cpp plateau.o jeu.o -lfltk 

plateau.o: plateau.cpp plateau.hpp
	g++ -c --std='c++17' plateau.cpp

jeu.o: jeu.cpp jeu.hpp 
	g++ -c --std='c++17' jeu.cpp
