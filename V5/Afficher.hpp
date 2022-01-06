#ifndef __AFFICHER_H__
#define __AFFICHER_H__

#include "Jeu.hpp"
#include "Text.hpp"

/*--------------------------------------------------

Classe Canvas. Affiche le plateau de jeu

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

Classe AfficherScoreAndNb_coups. Affiche le score, le meilleur score et le
nombre de coups restants

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

Classe Menu. Affiche des informations sur le jeu et comment jouer ainsi que les 
affichages quand il n'y a pas de coup possible et quand le niveau est terminé.

--------------------------------------------------*/

class Menu{
    private:
        shared_ptr<jeu> j;
        Text info_niv{"1", {200, 15}, 20, FL_BLACK};
        int time=0;

    public:
        Menu(shared_ptr<jeu> j):j{j}{};

        void draw();
        void changeNiv();
        void AffichagePendantPartie();

        int getniv();
        
};

/*--------------------------------------------------

Class EcranAccueil. Pour afficher un court instant, au lancement du programme 
un écran d'acceuille contenant mon nom et prénom ainsi que tous les éléments
disponible dans le jeu. 

--------------------------------------------------*/

class EcranAccueil{
    private:
        Glacage g{{3,5}, 45, 45};// pour lui faire perdre une vie et afficher un glacage de rectangle_info_niv 1
    public:
        EcranAccueil(){g.DoExplosion();};

        void draw();

};

#endif