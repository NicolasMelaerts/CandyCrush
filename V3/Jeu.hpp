#ifndef __JEU_H__
#define __JEU_H__

#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include <array>
#include <fstream>
#include <stdlib.h>

#include "ElementDeJeu.hpp"
#include "Score.hpp"

using namespace std;

/*--------------------------------------------------

jeu class.

--------------------------------------------------*/

class jeu{
private:
    vector<vector<int> > plateau;
    vector< vector<shared_ptr<ElementDeJeu>> > E;
    

    int taille_plateau = 9;
    int nb_couleurs_bonbon = 6;
    vector<Fl_Color > Colors{FL_RED, FL_BLUE,FL_YELLOW, FL_GREEN, FL_MAGENTA, fl_rgb_color(251, 139, 35)};

    ScoreAndNbcoups c;
    int niv;

    vector<vector<int> > plateau_glacage;

    void ouvertureNiv(int niv);
    void ouvertureInfo(int niv);
    void ouvertureGlacage(int niv);

    bool jeu_en_cours = 0;
    
public:

    jeu(int niv):c{0,0}, niv{niv}{
        setGame(niv);
    };


    void setGame(int niv){
        ouvertureNiv(niv);
        ouvertureInfo(niv);
        ouvertureGlacage(niv);
        init_plateau(E);
        c.set_score(0);
    }

    shared_ptr<vector< vector<shared_ptr<ElementDeJeu>> >> PtrPlateau(){
        return make_shared<vector< vector<shared_ptr<ElementDeJeu>> >>(E);
    }

    shared_ptr<ScoreAndNbcoups> PtrScoreAndNb_coups(){
        return make_shared<ScoreAndNbcoups>(c);
    }

    vector<vector<int> > get_plateau(){
        return plateau;
    }
    void init_plateau(vector< vector<shared_ptr<ElementDeJeu>> > E){
        plateau.clear();
        for (int i =0; i<taille_plateau; i++){
            plateau.push_back({});
            for (int j=0; j<taille_plateau; j++){
                plateau[i].push_back(E[i][j].get()->getMyId());
            }
        }
    }

    bool jeu_possible(){
        return c.get_nb_coups_restants()>0;
    }

    bool get_jeu_en_cours(){
        return jeu_en_cours;
    }

    void set_jeu_est_en_cours(bool en_cours){
        jeu_en_cours = en_cours;
    }

    int get_taille_plateau(){
        return taille_plateau;
    }

    void set_plateau(vector<vector<int>> newplat){
        plateau = newplat;
    }

    int get_nb_couleur(){
        return nb_couleurs_bonbon;
    }

    int getelemplateau(int a, int b){
        return plateau[a][b];
    }


    bool again_fall(vector< vector<shared_ptr<ElementDeJeu>> > E);
    vector<vector<int> > check_lines(vector<vector<int> > plat);
    vector<vector<int> > check_rows(vector<vector<int> > plat);
    vector<Point> setToExplose();
    void DoExplose(vector<Point> to_explose);

    void search_combinaison();
    void fall();
    void fall_plat();
    void afficher_plateau_de_jeu();
    void echange(Point a, Point b);
    bool coup_possible(Point a, Point b);
    
    bool pas_de_coup_possible();
    void melanger();    // si pas la poss de faire une combi de 3 bonbons

    void wait_anim();
};



#endif