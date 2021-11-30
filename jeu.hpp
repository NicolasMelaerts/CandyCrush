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
    struct coord{
        int i;
        int j;
    };
    
    
public:
    jeu(){initialize();};
    void check_lines();
    void check_rows();
    void fall();
    void afficher_plateau_de_jeu();
    void search_combinaison();

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
};


