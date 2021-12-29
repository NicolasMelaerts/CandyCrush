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


/*--------------------------------------------------

AfficherScoreAndNb_coups class.

--------------------------------------------------*/

class AfficherScoreAndNb_coups{
    private:
        shared_ptr<jeu> j;
        shared_ptr<ScoreAndNbcoups> ptrScoreAndNb_coups;

    public:
        AfficherScoreAndNb_coups(shared_ptr<jeu> j):j(j){};
        void draw();
};


/*--------------------------------------------------

Menu class.

--------------------------------------------------*/

class Menu{
    private:
        shared_ptr<jeu> j;
        TextRectangle niv{{200, 15}, 20,20, "1", 20};
        int time=0;

    public:
        Menu(shared_ptr<jeu> j):j{j}{};

        void draw();
        void changeNiv();
        void AffichagePendantPartie();

        int getniv(){
            return stoi(niv.getString());
        }
        
};

/*--------------------------------------------------

EcranAccueil class.

--------------------------------------------------*/

class EcranAccueil{
    private:
        Glacage g{{3,5}, 45, 45};
    public:
    EcranAccueil(){g.DoExplosion();};

    void draw();

};

#endif