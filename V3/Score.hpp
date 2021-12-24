#ifndef __SCORE_H__
#define __SCORE_H__

#include <fstream>
#include <iostream>

using namespace std;

class ScoreAndNbcoups{
    private:
        int meilleur_score;
        int score;
        int nb_coups_restants;
        int nb_coups_joue = 0;
        
        
    public:
        ScoreAndNbcoups(int meilleur_score, int nb_coups_restants, int score=0): 
        meilleur_score{meilleur_score},nb_coups_restants{nb_coups_restants} ,score{score}{};

        void do_coup(){nb_coups_restants--; nb_coups_joue++;}
        void set_nb_coups_restants(int new_nb_coups){nb_coups_restants = new_nb_coups;}
        int get_nb_coups_restants(){return nb_coups_restants;}

        void augmente_score(int niv);
        void set_score(int new_score){score = new_score;};
        int get_score(){return score;};

        void set_meilleur_score(int new_m_score){meilleur_score = new_m_score;}
        void write_meilleur_score(int niv);
        int get_meilleur_score(){return meilleur_score;}
};

#endif