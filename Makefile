main: main.cpp plateau.o
	g++ --std='c++17' -o main main.cpp plateau.o -lfltk 

plateau.o: plateau.cpp plateau.hpp
	g++ -c --std='c++17' plateau.cpp

