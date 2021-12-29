#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "Jeu.hpp"
#include "Shapes.hpp"

/*--------------------------------------------------

ControlJeu class.

--------------------------------------------------*/

struct DoublePoint{
    Point p1,p2;
};


class ControlJeu{
    private:
        shared_ptr<jeu> j;
        vector<Point> ForDrag;
        shared_ptr<vector< vector<shared_ptr<ElementDeJeu>> >> ptrPlateau;

    public:
        ControlJeu(shared_ptr<jeu> j):j(j){
            ptrPlateau=j.get()->PtrPlateau();
        };

        void mouseMove(Point mouseLoc);
        void drag(Point mouseLoc);
        void mouseClick(Point mouseLoc);
        void changeNiv(int niv){
            j.get()->setGame(niv);
        }

        vector<Point> getForDrag(){
            return ForDrag;
        }

        void tentativeSwap();
        DoublePoint inter_tentativeSwap(int idxForDrag);
        void inter2_tentativeSwap(Point p1, Point p2, Point idx1, Point idx2);


        bool get_jeu_en_cours(){
            return j.get()->get_jeu_en_cours();
        }

        void reset_meilleur_score(){
            j.get()->reset_meilleur_score();
        }
};

#endif