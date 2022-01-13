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
#include <algorithm>
#include <memory>

#include "ElementDeJeu.hpp"
#include "Score.hpp"
#include "Animation.hpp"

using namespace std;

/*--------------------------------------------------

Classe jeu

--------------------------------------------------*/

class jeu{
private:
    vector<vector<int> > plateau;
    vector< vector<shared_ptr<ElementDeJeu>> > E;
    vector<Fl_Color > Colors{FL_RED, FL_BLUE,FL_YELLOW, FL_GREEN, FL_MAGENTA, fl_rgb_color(251, 139, 35)};

    ScoreAndNbcoups c;
    

    int taille_plateau = 9;
    int nb_couleurs_bonbon = 6;
    int niv;
    bool jeu_en_cours = 0;
    bool aucun_coups_poss = 0;

    void ouvertureNiv(int niv);
    void ouvertureInfo(int niv);

public:

    jeu(int niv);

    void setGame(int niveau);

    // getteur et setteur
    shared_ptr<vector< vector<shared_ptr<ElementDeJeu>> >> getPtrPlateau(){
        return make_shared<vector< vector<shared_ptr<ElementDeJeu>> >>(E);
    }

    shared_ptr<ScoreAndNbcoups> getPtrScoreAndNb_coups(){
        return make_shared<ScoreAndNbcoups>(c);
    }

    vector<vector<int> > get_plateau(){
        return plateau;
    }

    bool get_aucun_coup_poss(){
        return aucun_coups_poss;
    }

    void set_aucun_coup_poss(bool coup_poss){
        aucun_coups_poss = coup_poss;
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

    void reset_meilleur_score(){
        c.write_meilleur_score(niv, 0);
    }


    //méthodes
    void init_plateau(vector< vector<shared_ptr<ElementDeJeu>> > E);

    void search_combinaison();
    vector<vector<int> > check_3bonbons(vector<vector<int> > plat);


    void check_5bonbons();
    void coup_cookie(int id, Point cookie_to_delete);
    void check_4bonbons();
    void check_L();

    void echange(Point a, Point b);
    bool coup_possible(Point a, Point b);   // swap autorisé
    bool coup_possible();       // vérif si coup possible sur le plateau si non -> mélanger()
    void melanger();    // si pas la poss de faire une combi de 3 bonbons


    vector<Point> setToExplose();
    void DoExplose(vector<Point> to_explose);
    void Explose(vector<Point> to_explose);
    void ExploseLigne(int l);
    void ExploseColonne(int c);
    void ExploseBBspecialRond(Point empl);
    void DoExploseGlacage();
    void check_ingredient();


    void fall();
    void fall_mur_diagonale();
    bool get_finish_fall();


    void afficher_plateau_de_jeu();

    void wait_anim();
};



#endif