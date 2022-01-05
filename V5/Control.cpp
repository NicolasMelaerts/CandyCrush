#include "Control.hpp"

/*--------------------------------------------------

ControlJeu class.

--------------------------------------------------*/

ControlJeu::ControlJeu(shared_ptr<jeu> j):j(j){
            ptrPlateau=j.get()->getPtrPlateau();
        };


void ControlJeu::mouseMove(Point mouseLoc){
    // pour changer les contours d'un élément de jeu si la souris est sur celui-ci

    ptrPlateau=j.get()->getPtrPlateau();
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
    // renvoie le point du bonbon qui devra être swapper
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
    // swapping de deux bonbons avec les animations dans un sens pour un bonbon et le sens 
    // inverse pour l'autre bonbon

    j.get()->set_jeu_est_en_cours(1);

    if (p1_debut.x == p1_fin.x && p1_debut.y == p1_fin.y+1){
        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->ElementMove(3);  //gauche 
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->ElementMove(2);  //droite
    }
    if (p1_debut.x == p1_fin.x && p1_debut.y == p1_fin.y-1){
        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->ElementMove(2); // droite
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->ElementMove(3);  //gauche
    }
    if (p1_debut.x == p1_fin.x+1 && p1_debut.y == p1_fin.y){
        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->ElementMove(1);  // haut
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->ElementMove(0);  // bas 
    }
    if (p1_debut.x == p1_fin.x-1 && p1_debut.y == p1_fin.y){
        ptrPlateau.get()->at(p2_debut.x).at(p2_debut.y).get()->ElementMove(0);  // bas 
        ptrPlateau.get()->at(p2_fin.x).at(p2_fin.y).get()->ElementMove(1);  //haut
    }
                    
    j.get()->wait_anim();
    j.get()->set_jeu_est_en_cours(0);
                 
}

void ControlJeu::SwapIfCoupPossible(Point p1_debut, Point p1_fin, Point p2_debut, Point p2_fin){
    // vérifie si le swap voulu par l'utilisateur est possible 
    // si c'est un swap entre un bonbon et un cookie c'est toujours possible

    ptrPlateau = j.get()->getPtrPlateau();

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


        // si notre coup induit d'autre combinaison et fait tomber les bonbons et en rajoute des nouveau 
        j.get()->set_jeu_est_en_cours(1); // attendre fin du coup pour rejouer
        j.get()->search_combinaison();
        j.get()->set_jeu_est_en_cours(0); // on peut continuer a jouer  
    }  
}

void ControlJeu::tentativeSwap(){
    if (j.get()->jeu_possible() and !j.get()->get_jeu_en_cours()){
        ptrPlateau=j.get()->getPtrPlateau();

        DoublePoint debut{findBonbonToSwap(0)};
        DoublePoint fin{findBonbonToSwap(ForDrag.size()-1)};

        Point p1_debut{debut.point1}, p1_fin{fin.point1}, p2_debut{debut.point2}, p2_fin{fin.point2};


        if (p1_debut.x != -1 && p1_fin.x != -1){
            // bonbons doivent être adjacent pour être swap
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

