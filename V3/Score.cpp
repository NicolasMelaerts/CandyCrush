#include "Score.hpp"



void ScoreAndNbcoups::augmente_score(int niv){
    score += 100;
    if (score>meilleur_score){
        write_meilleur_score(niv, score);
    }
}

void ScoreAndNbcoups::write_meilleur_score(int niv, int s){
    cout << "Ecriture dans " << to_string(niv) << endl;
    fstream Info("NiveauDeJeu/Info"+to_string(niv), ios::out);

    if (Info.is_open()){
        Info << to_string(score)<< "\n";
        Info << to_string(nb_coups_restants+nb_coups_joue);
    }
    else{
        cout << "Problème d'écriture dans le fichier" << endl;
    }
    meilleur_score = score;
}

