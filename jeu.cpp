#include "jeu.hpp"

void jeu::start(){
    for (int i=0; i<taille_plateau; i++){
        plateau.push_back({});
        for (int j=0; j<taille_plateau; j++){
            plateau[i].push_back(rand()%nb_couleurs_bonbon);
        }
    }
    search_combinaison();
}

void jeu::check_lines(){
    cout << "check_lines" << endl;
    for (int i=8; i>=0; i--){
        for (int j=0; j<taille_plateau-2; j++){
            if (plateau[i][j] == plateau[i][j+1] && plateau[i][j] == plateau[i][j+2]){ // si a = b et a = c alors b = c
                plateau[i][j] = -1;
                plateau[i][j+1] = -1;
                plateau[i][j+2] = -1;
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
            }
        }
    }
}

void jeu::search_combinaison(){
    vector<vector<int >> ancien_plateau;
    while (ancien_plateau != plateau){
        ancien_plateau = plateau;
        check_rows();
        check_lines();
        fall();
    }
}

void jeu::fall(){
    vector<int> col;
    for (int i=0; i<taille_plateau; i++){
        for (int j=taille_plateau-1; j>=0; j--){
            if (plateau[j][i]!=-1){
                col.push_back(plateau[j][i]);
            }
        }
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
            if (plateau[i][j] == 0){cout << "B ,";}
            if (plateau[i][j] == 1){cout << "G ,";}
            if (plateau[i][j] == 4){cout << "Y ,";}
            if (plateau[i][j] == 2){cout << "R ,";}
            if (plateau[i][j] == 5){cout << "C ,";}
            if (plateau[i][j] == 3){cout << "M ,";}
            if (plateau[i][j] == 6){cout << "O ,";}
        }
        cout << endl;
    }
    cout << endl;
}

void jeu::echange(coord a, coord b){
    swap(plateau[a.i][a.j], plateau[b.i][b.j]);
}

bool jeu::coup_possible(coord a, coord b){
    vector<vector<int >> test_plateau;
    swap(test_plateau[a.i][a.j], test_plateau[b.i][b.j]);
    check_lines();
    check_rows();
    for (auto &l: test_plateau){
        for (auto &i: l){
            if (i==-1){
                return false;
            }
        }
    }
    return true;
}