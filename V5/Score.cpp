#include "Score.hpp"



void ScoreAndNbcoups::augmente_score(int niv, int point){
    score += point;
    if (score>meilleur_score){  // nouveau meilleur score
        write_meilleur_score(niv, score);
    }
}

void ScoreAndNbcoups::write_meilleur_score(int niv, int s){
    fstream Info("NiveauDeJeu/Info"+to_string(niv), ios::out);   // écriture dans le fichier info du niv

    // ligne 1 le meilleur score
    // ligne 2 le nombre de coups pour le niveau
    if (Info.is_open()){
        Info << to_string(score)<< "\n";
        Info << to_string(nb_coups_restants+nb_coups_joue);
    }
    else{
        cout << "Problème d'écriture dans le fichier" << endl;
    }
    meilleur_score = score;
}

void ScoreAndNbcoups::reset_nb_coup_joue(){
    nb_coups_joue = 0;
}

