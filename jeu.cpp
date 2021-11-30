#include "jeu.hpp"

void jeu::initialize(){
    for (int i=0; i<taille_plateau; i++){
        plateau.push_back({});
        for (int j=0; j<taille_plateau; j++){
            plateau[i].push_back(rand()%nb_couleurs_bonbon);
        }
    }
}

void jeu::check_lines(){
    cout << "check_lines" << endl;
    for (int i=1; i<taille_plateau+1; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plateau[taille_plateau-i][j] == plateau[taille_plateau-i][j+1] && plateau[taille_plateau-i][j] == plateau[taille_plateau-i][j+2]){ // si a = b et a = c alors b = c
                plateau[taille_plateau-i][j] = -1;
                plateau[taille_plateau-i][j+1] = -1;
                plateau[taille_plateau-i][j+2] = -1;
                break;
            }
        }
    }
}

void jeu::check_rows(){
    cout << "check rows"<< endl;
    for (int i=1; i<taille_plateau+1; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plateau[j][taille_plateau-i] == plateau[j+1][taille_plateau-i] && plateau[j][taille_plateau-i] == plateau[j+2][taille_plateau-i]){
                plateau[j][taille_plateau-i] = -1;
                plateau[j+1][taille_plateau-i] = -1;
                plateau[j+2][taille_plateau-i] = -1;
                break;
            }
        }
    }
}

void jeu::search_combinaison(){
    vector<vector<int >> ancien_plateau;
    while (ancien_plateau != plateau){
        afficher_plateau_de_jeu();
        cout << endl;
        ancien_plateau = plateau;
        check_rows();
        check_lines();
        fall();
    }
}

void jeu::fall(){
    vector<int> col;
    for (int i=taille_plateau-1; i>=0; i--){
        for (int j=taille_plateau-1; j>=0; j--){
            if (plateau[j][i]!=-1){
                col.push_back(plateau[j][i]);
            }
        }
        cout << "size" << col.size()<< "  " << endl;;
        while (col.size()!=taille_plateau){
            col.push_back(rand()%nb_couleurs_bonbon); 
        }
        for (int j=0; j<taille_plateau; j++){
            plateau[taille_plateau-1-j][i] = col[j];
        }
        col.clear();
    }
}

void jeu::afficher_plateau_de_jeu(){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){
            cout << plateau[i][j] << " ,";
        }
        cout << endl;
    }
}
