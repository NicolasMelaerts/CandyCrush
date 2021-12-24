#include "Score.hpp"



void ScoreAndNbcoups::augmente_score(int niv){
    score += 100;
    if (score>meilleur_score){
        write_meilleur_score(niv);
    }
}

void ScoreAndNbcoups::write_meilleur_score(int niv){
    fstream Info("NiveauDeJeu/Info"+to_string(niv));

    if (Info.is_open()){
        Info << to_string(score)<< "\n";
        Info << to_string(nb_coups_restants+nb_coups_joue) << "\n";
    }
    else{
        cout << "Problème d'écriture dans le fichier" << endl;
    }
    meilleur_score = score;
}