#include "Afficher.hpp"

/*--------------------------------------------------

Canvas class.

--------------------------------------------------*/

void Canvas::draw(){
    ptrPlateau=j.get()->PtrPlateau();


    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            ptrPlateau.get()->at(i).at(j).get()->draw();
        }
    }
}


void AfficherScoreAndNb_coups::draw(){
    ptrScoreAndNb_coups=j.get()->PtrScoreAndNb_coups();
    Text(to_string(ptrScoreAndNb_coups.get()->get_score()), {390, 15}, 20, FL_BLACK).draw();

    Text(to_string(ptrScoreAndNb_coups.get()->get_nb_coups_restants()), {450, 40}, 20, FL_BLACK).draw();
    Text(to_string(ptrScoreAndNb_coups.get()->get_meilleur_score()), {200, 40}, 20, FL_BLACK).draw();
}