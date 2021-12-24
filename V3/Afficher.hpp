#ifndef __AFFICHER_H__
#define __AFFICHER_H__

#include "Jeu.hpp"
#include "Text.hpp"

/*--------------------------------------------------

Canvas class.

--------------------------------------------------*/

class Canvas{
    private:
        shared_ptr<jeu> j;
        shared_ptr<vector< vector<shared_ptr<ElementDeJeu>> >> ptrPlateau;

        
    public:
        Canvas(shared_ptr<jeu> j):j(j){};

        void draw();
};

class AfficherScoreAndNb_coups{
    private:
        shared_ptr<jeu> j;
        shared_ptr<ScoreAndNbcoups> ptrScoreAndNb_coups;

    public:
        AfficherScoreAndNb_coups(shared_ptr<jeu> j):j(j){};
        void draw();
};



#endif