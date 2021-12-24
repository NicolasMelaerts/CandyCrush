#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "Jeu.hpp"
#include "Shapes.hpp"

/*--------------------------------------------------

ControlJeu class.

--------------------------------------------------*/

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

        bool get_jeu_en_cours(){
            return j.get()->get_jeu_en_cours();
        }
};

#endif