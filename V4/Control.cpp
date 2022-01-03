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


DoublePoint ControlJeu::findBonbonToSwap(int idxForDrag){
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

void ControlJeu::SwapBonbonAnim(Point p1_debut, Point p1_fin, Point p2_debut, Point p2_fin){
    j.get()->set_jeu_est_en_cours(1);

    if (p1_debut.x == p1_fin.x && p1_debut.y == p1_fin.y+1){
        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->ElementMove(3);
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->ElementMove(2);
    }
    if (p1_debut.x == p1_fin.x && p1_debut.y == p1_fin.y-1){
        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->ElementMove(2);
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->ElementMove(3);
    }
    if (p1_debut.x == p1_fin.x+1 && p1_debut.y == p1_fin.y){
        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->ElementMove(1);
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->ElementMove(0);
    }
    if (p1_debut.x == p1_fin.x-1 && p1_debut.y == p1_fin.y){
        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->ElementMove(0);
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->ElementMove(1);
    }
                    
    j.get()->wait_anim();
                 
}

void ControlJeu::SwapIfCoupPossible(Point p1_debut, Point p1_fin, Point p2_debut, Point p2_fin){
    ptrPlateau = j.get()->PtrPlateau();
    cout << ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->getMyId();
    if (j.get()->coup_possible({p1_debut.x, p1_debut.y}, {p1_fin.x, p1_fin.y}) or ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->getMyId()== -19 or ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->getMyId()==-19){

        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->setPosPlat(p1_fin);
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->setPosPlat(p1_debut);

        j.get()->echange({p2_debut.x,p2_debut.y},{p2_fin.x,p2_fin.y});
                        
        if (ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->getMyId()== -19){
            j.get()->coup_cookie(ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->getMyId(), p2_fin);
        }
        if (ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->getMyId()==-19){
            j.get()->coup_cookie(ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->getMyId(), p2_debut);
        }

        j.get()->search_combinaison();
    }  
}

void ControlJeu::tentativeSwap(){
    if (j.get()->jeu_possible()){
        ptrPlateau=j.get()->PtrPlateau();

        DoublePoint debut{findBonbonToSwap(0)};
        DoublePoint fin{findBonbonToSwap(ForDrag.size()-1)};

        Point p1_debut{debut.point1}, p1_fin{fin.point1}, p2_debut{debut.point2}, p2_fin{fin.point2};


        cout << p2_debut.x << ", "<< p2_debut.y << endl;
        cout << p2_fin.x << ", "<< p2_fin.y << endl;
        cout << p1_debut.x << ", "<< p1_debut.y << endl;
        cout << p1_fin.x << ", "<< p1_fin.y << endl;

        if (p1_debut.x != -1 && p1_fin.x != -1){
            if ((p1_debut.x == p1_fin.x and p1_debut.y == p1_fin.y+1) || (p1_debut.x == p1_fin.x and p1_debut.y == p1_fin.y-1) || (p1_debut.x == p1_fin.x+1 and p1_debut.y == p1_fin.y) || (p1_debut.x == p1_fin.x-1 and p1_debut.y == p1_fin.y)){
                SwapBonbonAnim(p1_debut, p1_fin,p2_debut, p2_fin);
                SwapIfCoupPossible(p1_debut, p1_fin,p2_debut, p2_fin);
            }
        }
        if (!j.get()->jeu_possible())
            j.get()->set_jeu_est_en_cours(0);
            
    }
    ForDrag.clear();
}

