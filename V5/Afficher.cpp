#include "Afficher.hpp"

/*--------------------------------------------------

Canvas class.

--------------------------------------------------*/

void Canvas::draw(){
    ptrPlateau=j.get()->getPtrPlateau();

    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            ptrPlateau.get()->at(i).at(j).get()->draw();    // dessine tous les éléments du plateau
        }
    }
}


/*--------------------------------------------------

AfficherScoreAndNb_coups class.

--------------------------------------------------*/

void AfficherScoreAndNb_coups::draw(){
    ptrScoreAndNb_coups=j.get()->getPtrScoreAndNb_coups();

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
    

    info_niv.draw();

    AffichagePendantPartie();
}

void Menu::AffichagePendantPartie(){
    if (j.get()->get_aucun_coup_poss()){
        ++time;
    }
    if (time!=0){
        Text{"AUCUNE COMBINAISONS POSSIBLES, NOUVEAUX BONBONS", {250, 270}, 21, FL_RED}.draw();
    }
    if (time==100){
        time=0;
        j.get()->set_aucun_coup_poss(0);
    }
    if (!j.get()->jeu_possible()){
        Text("FINI, CHANGE DE NIV AVEC ESPACE", {250, 580}, 25, FL_RED).draw();
    }

}

void Menu::changeNiv(){
    int niv = stoi(info_niv.getString());
    if (niv<5){
        info_niv.setString(to_string(niv+1));
    }
    else {
        info_niv.setString(to_string(1));
    }
}

int Menu::getniv(){
    return stoi(info_niv.getString());
}


/*--------------------------------------------------

EcranAccueil class.

--------------------------------------------------*/


void EcranAccueil::draw(){
        Text("Projet candy crush par Nicolas Melaerts", {180,30},20).draw();
        Text("Langages de programmation 2", {140,60},20).draw();

        Text("Bonbons :", {50,120},20).draw();
        Bonbon{{1,2}, FL_RED, 35,35}.draw();
        Bonbon{{1,3}, FL_BLUE, 35,35}.draw();
        Bonbon{{1,4}, FL_MAGENTA, 35,35}.draw();
        Bonbon{{1,5}, FL_YELLOW, 35,35}.draw();
        Bonbon{{1,6}, FL_GREEN, 35,35}.draw();
        Bonbon{{1,7}, fl_rgb_color(251, 139, 35), 35,35}.draw();

        Text("Mur :", {30,170},20).draw();
        Mur({2,2}, 35,35).draw();

        Text("Glaçage :", {50,220},20).draw();
        Text("2 vies", {150,220},20).draw();
        Text("1 vie", {250,220},20).draw();
        g.draw();
        Glacage{{3,3}, 45, 45}.draw();

        Text("Bonbons spéciaux :", {90,290},20).draw();

        Text("Bonbons emballés", {90,320},15).draw();
        BonbonSpecialRond{{5,3}, FL_RED, 22}.draw();
        BonbonSpecialRond{{5,4}, FL_BLUE, 22}.draw();
        BonbonSpecialRond{{5,5}, FL_MAGENTA, 22}.draw();
        BonbonSpecialRond{{5,6}, FL_YELLOW, 22}.draw();
        BonbonSpecialRond{{5,7}, FL_GREEN, 22}.draw();
        BonbonSpecialRond{{5,8}, fl_rgb_color(251, 139, 35), 22}.draw();

        Text("Bonbons rayés verticaux", {90,370},15).draw();
        BonbonSpecialVertical{{6,3}, FL_RED, 20,40}.draw();
        BonbonSpecialVertical{{6,4}, FL_BLUE, 20,40}.draw();
        BonbonSpecialVertical{{6,5}, FL_MAGENTA, 20,40}.draw();
        BonbonSpecialVertical{{6,6}, FL_YELLOW, 20,40}.draw();
        BonbonSpecialVertical{{6,7}, FL_GREEN, 20,40}.draw();
        BonbonSpecialVertical{{6,8}, fl_rgb_color(251, 139, 35), 20,40}.draw();

        Text("Bonbons rayés horizontaux", {90,420},15).draw();
        BonbonSpecialHorizontal{{7,3}, FL_RED, 40,20}.draw();
        BonbonSpecialHorizontal{{7,4}, FL_BLUE, 40,20}.draw();
        BonbonSpecialHorizontal{{7,5}, FL_MAGENTA, 40,20}.draw();
        BonbonSpecialHorizontal{{7,6}, FL_YELLOW, 40,20}.draw();
        BonbonSpecialHorizontal{{7,7}, FL_GREEN, 40,20}.draw();
        BonbonSpecialHorizontal{{7,8}, fl_rgb_color(251, 139, 35), 40,20}.draw();

        Text("Cookie", {90,470},15).draw();
        BonbonSpecialRondCookies{{8,3}, FL_BLACK, 22}.draw();

        Text("Ingrédients : ", {90,520},20).draw();
        Text("(C = cerise)", {90,540},15).draw();
        Text("(N = noisette)", {90,560},15).draw();
        Ingredient{{9,3},"C", 20, 20}.draw();
        Ingredient{{9,4},"N", 20, 20}.draw();
    }