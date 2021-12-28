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

        Text poss{"Pas de combinaison possible, nouveaux bonbons", {250, 270}, 21, FL_RED};
        int time=0;

        
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
        TextRectangle niv{{200, 15}, 20,20, "1", 20};
    public:
        Menu(){};

        void draw();
        void changeNiv();

        int getniv(){
            return stoi(niv.getString());
        }
        
};

class EcranAccueil{
    private:
        Glacage g{{3,6}, 45, 45};
    public:
    EcranAccueil(){g.DoExplosion();};

    void draw(){
        Text("Projet candy crush par Nicolas Melaerts", {180,30},20).draw();
        Text("Langages de programmation 2", {140,60},20).draw();

        Bonbon{{1,2}, FL_RED, 35,35}.draw();
        Bonbon{{1,3}, FL_BLUE, 35,35}.draw();
        Bonbon{{2,2}, FL_MAGENTA, 35,35}.draw();
        Bonbon{{2,3}, FL_YELLOW, 35,35}.draw();
        Bonbon{{3,2}, FL_GREEN, 35,35}.draw();
        Bonbon{{3,3}, fl_rgb_color(251, 139, 35), 35,35}.draw();

        Mur({2,6}, 35,35).draw();

        BonbonSpecialRond{{4,2}, FL_RED, 22}.draw();
        BonbonSpecialRond{{4,3}, FL_BLUE, 22}.draw();
        BonbonSpecialRond{{5,2}, FL_MAGENTA, 22}.draw();
        BonbonSpecialRond{{5,3}, FL_YELLOW, 22}.draw();
        BonbonSpecialRond{{6,2}, FL_GREEN, 22}.draw();
        BonbonSpecialRond{{6,3}, fl_rgb_color(251, 139, 35), 22}.draw();


        g.draw();
        Glacage{{4,6}, 45, 45}.draw();

    }

};

#endif