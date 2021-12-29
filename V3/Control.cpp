#include "Control.hpp"

/*--------------------------------------------------

ControlJeu class.

--------------------------------------------------*/


void ControlJeu::mouseMove(Point mouseLoc){
    ptrPlateau=j.get()->PtrPlateau();
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            ptrPlateau.get()->at(i).at(j).get()->mouseMove(mouseLoc);
        }
    }
}

void ControlJeu::drag(Point mouseLoc){
    ForDrag.push_back(mouseLoc);
}

void ControlJeu::mouseClick(Point mouseLoc){
}


DoublePoint ControlJeu::inter_tentativeSwap(int idxForDrag){
    Point p;
    Point idx;

    bool stop = false;

    for (int i =0; i<9; i++){
        for (int j =0; j<9; j++){
            p = ptrPlateau.get()->at(i).at(j).get()->getPosPlatifcontain(ForDrag[idxForDrag]);
            idx = {i,j};
            if (p.x != -1){
                stop = true;
                break;
            }
        }
        if (stop){
            break;
        }
    }
    return {p, idx};
}

void ControlJeu::inter2_tentativeSwap(Point p1, Point p2, Point idx1, Point idx2){
                    j.get()->set_jeu_est_en_cours(1);

                    if (p1.x == p2.x && p1.y == p2.y+1){
                        ptrPlateau.get()->at(idx1.x).at(idx1.y).get()->ElementMove(3);
                        ptrPlateau.get()->at(idx2.x).at(idx2.y).get()->ElementMove(2);
                    }
                    if (p1.x == p2.x && p1.y == p2.y-1){
                        ptrPlateau.get()->at(idx1.x).at(idx1.y).get()->ElementMove(2);
                        ptrPlateau.get()->at(idx2.x).at(idx2.y).get()->ElementMove(3);
                    }
                    if (p1.x == p2.x+1 && p1.y == p2.y){
                        ptrPlateau.get()->at(idx1.x).at(idx1.y).get()->ElementMove(1);
                        ptrPlateau.get()->at(idx2.x).at(idx2.y).get()->ElementMove(0);
                    }
                    if (p1.x == p2.x-1 && p1.y == p2.y){
                        ptrPlateau.get()->at(idx1.x).at(idx1.y).get()->ElementMove(0);
                        ptrPlateau.get()->at(idx2.x).at(idx2.y).get()->ElementMove(1);
                    }
                    
                    j.get()->wait_anim();

                    if (j.get()->coup_possible({p1.x, p1.y}, {p2.x, p2.y})){

                        ptrPlateau.get()->at(idx1.x).at(idx1.y).get()->setPosPlat(p2);
                        ptrPlateau.get()->at(idx2.x).at(idx2.y).get()->setPosPlat(p1);

                        j.get()->echange({idx1.x,idx1.y},{idx2.x,idx2.y});
                        
                        j.get()->search_combinaison();

                    }
                    
}

void ControlJeu::tentativeSwap(){
    if (j.get()->jeu_possible()){
        ptrPlateau=j.get()->PtrPlateau();

        DoublePoint w{inter_tentativeSwap(0)};
        DoublePoint w1{inter_tentativeSwap(ForDrag.size()-1)};

        Point p1{w.p1}, p2{w1.p1}, idx1{w.p2}, idx2{w1.p2};


        cout << idx1.x << ", "<< idx1.y << endl;
        cout << idx2.x << ", "<< idx2.y << endl;
        cout << p1.x << ", "<< p1.y << endl;
        cout << p2.x << ", "<< p2.y << endl;

        if (p1.x != -1 && p2.x != -1){
            if ((p1.x == p2.x and p1.y == p2.y+1) || (p1.x == p2.x and p1.y == p2.y-1) || (p1.x == p2.x+1 and p1.y == p2.y) || (p1.x == p2.x-1 and p1.y == p2.y)){
                inter2_tentativeSwap(p1, p2,idx1, idx2);
            }
        }
        if (!j.get()->jeu_possible())
            j.get()->set_jeu_est_en_cours(0);
            
    }
    ForDrag.clear();
}

