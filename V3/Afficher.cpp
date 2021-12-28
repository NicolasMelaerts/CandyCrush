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
    if (j.get()->get_aucun_coup_poss()){
        ++time;
    }
    if (time!=0){
        poss.draw();
    }
    if (time==100){
        time=0;
        j.get()->set_aucun_coup_poss(0);
    }
    if (!j.get()->jeu_possible()){

        Text("FINI, CHANGE DE NIV AVEC ESPACE", {250, 200}, 25, FL_BLACK).draw();
    }
}


/*--------------------------------------------------

AfficherScoreAndNb_coups class.

--------------------------------------------------*/

void AfficherScoreAndNb_coups::draw(){
    ptrScoreAndNb_coups=j.get()->PtrScoreAndNb_coups();
    Text(to_string(ptrScoreAndNb_coups.get()->get_score()), {390, 15}, 20, FL_BLACK).draw();

    Text(to_string(ptrScoreAndNb_coups.get()->get_nb_coups_restants()), {450, 40}, 20, FL_BLACK).draw();
    Text(to_string(ptrScoreAndNb_coups.get()->get_meilleur_score()), {200, 40}, 20, FL_BLACK).draw();
}


/*--------------------------------------------------

Menu class.

--------------------------------------------------*/

void Menu::draw(){
    Text("Selection Niveau : ", {100, 15}, 20, FL_BLACK).draw();
    Text("Meilleur Score : ", {100, 40}, 20, FL_BLACK).draw();
    Text("Score : ", {325, 15}, 20).draw();
    Text("Coups restants : ", {360, 40}, 20).draw();
    Text("Utilise la souris pour swapper des bonbons", {250, 500}, 20).draw();
    Text("Appuie sur 'Espace' pour changer de niveau", {250, 520}, 20).draw();
    Text("Appuie sur 'r' pour réinitialisé le meilleur score", {250, 540}, 20).draw();
    Text("Appuie sur 'q' pour quitter", {250, 560}, 20).draw();
    

    niv.draw();
}

void Menu::changeNiv(){
    niv.setNiveau();
}