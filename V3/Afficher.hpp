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
        Glacage g{{3,5}, 45, 45};
    public:
    EcranAccueil(){g.DoExplosion();};

    void draw(){
        Text("Projet candy crush par Nicolas Melaerts", {180,30},20).draw();
        Text("Langages de programmation 2", {140,60},20).draw();

        Text("Bonbons :", {50,120},20).draw();
        Bonbon{{1,2}, FL_RED, 35,35}.draw();
        Bonbon{{1,3}, FL_BLUE, 35,35}.draw();
        Bonbon{{1,4}, FL_MAGENTA, 35,35}.draw();
        Bonbon{{1,5}, FL_YELLOW, 35,35}.draw();
        Bonbon{{1,6}, FL_GREEN, 35,35}.draw();
        Bonbon{{1,7}, fl_rgb_color(251, 139, 35), 35,35}.draw();

        Text("Mur :", {30,170},20).draw();
        Mur({2,2}, 35,35).draw();

        Text("Glaçage :", {50,220},20).draw();
        Text("2 vies", {150,220},20).draw();
        Text("1 vie", {250,220},20).draw();
        g.draw();
        Glacage{{3,3}, 45, 45}.draw();

        Text("Bonbons spéciaux:", {90,290},20).draw();

        Text("Bonbons emballés", {90,320},15).draw();
        BonbonSpecialRond{{5,3}, FL_RED, 22}.draw();
        BonbonSpecialRond{{5,4}, FL_BLUE, 22}.draw();
        BonbonSpecialRond{{5,5}, FL_MAGENTA, 22}.draw();
        BonbonSpecialRond{{5,6}, FL_YELLOW, 22}.draw();
        BonbonSpecialRond{{5,7}, FL_GREEN, 22}.draw();
        BonbonSpecialRond{{5,8}, fl_rgb_color(251, 139, 35), 22}.draw();

        Text("Bonbons rayés verticaux", {90,370},15).draw();
        BonbonSpecialVertical{{6,3}, FL_RED, 20,40}.draw();
        BonbonSpecialVertical{{6,4}, FL_BLUE, 20,40}.draw();
        BonbonSpecialVertical{{6,5}, FL_MAGENTA, 20,40}.draw();
        BonbonSpecialVertical{{6,6}, FL_YELLOW, 20,40}.draw();
        BonbonSpecialVertical{{6,7}, FL_GREEN, 20,40}.draw();
        BonbonSpecialVertical{{6,8}, fl_rgb_color(251, 139, 35), 20,40}.draw();

        Text("Bonbons rayés horizontaux", {90,420},15).draw();
        BonbonSpecialHorizontal{{7,3}, FL_RED, 40,20}.draw();
        BonbonSpecialHorizontal{{7,4}, FL_BLUE, 40,20}.draw();
        BonbonSpecialHorizontal{{7,5}, FL_MAGENTA, 40,20}.draw();
        BonbonSpecialHorizontal{{7,6}, FL_YELLOW, 40,20}.draw();
        BonbonSpecialHorizontal{{7,7}, FL_GREEN, 40,20}.draw();
        BonbonSpecialHorizontal{{7,8}, fl_rgb_color(251, 139, 35), 40,20}.draw();

        Text("Cookie", {90,470},15).draw();
        BonbonSpecialRondCoockies{{8,3}, FL_BLACK, 22}.draw();
    }

};

#endif