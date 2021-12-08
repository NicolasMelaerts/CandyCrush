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
    void start();
    struct coord{
        int i;
        int j;
    };
    
    
public:
    jeu(){start();};

    vector<vector<int> > check_lines(vector<vector<int> > plat);
    vector<vector<int> > check_rows(vector<vector<int> > plat);
    void fall();
    void afficher_plateau_de_jeu();
    void search_combinaison();
    vector<vector<int> > get_plateau(){
        return plateau;
    }
    void set_plateau(vector<vector<int> > newPlateau){
        plateau = newPlateau;
    }

    int get_taille_plateau(){
        return taille_plateau;
    }

    int get_nb_couleur(){
        return nb_couleurs_bonbon;
    }

    int getelemplateau(int a, int b){
        return plateau[a][b];
    }

    void melanger();    // si pas la poss de faire une combi de 3 bonbons
    void echange(coord a, coord b);
    
    bool coup_possible(coord a, coord b);
};


