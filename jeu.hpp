#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include <array>

using namespace std;

class jeu{
private:
    vector<vector<int> > plateau;
    int taille_plateau = 9;
    int nb_couleurs_bonbon = 6;
    void initialize();
public:
    jeu(){initialize();};
    void check_lines();
    void check_rows();
    void fall();
    void afficher_plateau_de_jeu();
    void search_combinaison();

    void melanger();    // si pas la poss de faire une combi de 3 bonbons
    void swap();
};


