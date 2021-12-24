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

void ControlJeu::tentativeSwap(){
    if (j.get()->jeu_possible()){
        ptrPlateau=j.get()->PtrPlateau();
        Point p1, p2;
        Point idx1, idx2;
        bool stop{false};

        for (int i =0; i<9; i++){
            for (int j =0; j<9; j++){
                p1 = ptrPlateau.get()->at(i).at(j).get()->getPosPlatifcontain(ForDrag[0]);
                idx1 = {i,j};
                if (p1.x != -1){
                    stop = true;
                    break;
                }
            }
            if (stop){
                break;
            }
        }

        stop = false;
        for (int i =0; i<9; i++){
            for (int j =0; j<9; j++){
                p2 = ptrPlateau.get()->at(i).at(j).get()->getPosPlatifcontain(ForDrag[ForDrag.size()-1]);
                idx2 = {i,j};
                if (p2.x != -1 and p2.y!=-1){
                    stop = true;
                    break;
                }
            }
            if (stop){
                break;
            }
        }

        cout << idx1.x << ", "<< idx1.y << endl;
        cout << idx2.x << ", "<< idx2.y << endl;
        cout << p1.x << ", "<< p1.y << endl;
        cout << p2.x << ", "<< p2.y << endl;

        if (p1.x != -1 && p2.x != -1){
            if ((p1.x == p2.x and p1.y == p2.y+1) || (p1.x == p2.x and p1.y == p2.y-1) || (p1.x == p2.x+1 and p1.y == p2.y) || (p1.x == p2.x-1 and p1.y == p2.y)){
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
                        
                        j.get()->set_plateau(j.get()->check_rows(j.get()->get_plateau()));
                        j.get()->set_plateau(j.get()->check_lines(j.get()->get_plateau()));

                        j.get()->search_combinaison();

                    }
                    
            }
        }
        if (!j.get()->jeu_possible())
            j.get()->set_jeu_est_en_cours(0);
            
    }
    ForDrag.clear();
}

