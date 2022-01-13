#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "Jeu.hpp"
#include "Shapes.hpp"



/*--------------------------------------------------

Classe ControlJeu. Récupère les événements effectués sur la GUI tel que les mouvements 
de la souris les clics, le swapping de bonbons, les appuis sur des touches
et va effectuer des changements dans le jeu via la classe jeu.

--------------------------------------------------*/


class ControlJeu{
    private:
        shared_ptr<jeu> j;
        vector<Point> ForDrag; // coordonnée souris lors d'un swapping
        shared_ptr<vector< vector<shared_ptr<ElementDeJeu>> >> ptrPlateauE;

    public:
        ControlJeu(shared_ptr<jeu> j);

        void mouseMove(Point mouseLoc);
        void drag(Point mouseLoc);
        void mouseClick(Point mouseLoc);


        void tentativeSwap();
        DoublePoint findBonbonToSwap(int idxForDrag);
        void SwapIfCoupPossible(Point p1, Point p2, Point idx1, Point idx2);
        void SwapBonbonAnim(Point p1, Point p2, Point idx1, Point idx2);

        void changeNiv(int niv){
            j.get()->setGame(niv);
        }

        bool get_jeu_en_cours(){
            return j.get()->get_jeu_en_cours();
        }

        void reset_meilleur_score(){
            j.get()->reset_meilleur_score();
        }

        vector<Point> getForDrag(){
            return ForDrag;
        }
};

#endif