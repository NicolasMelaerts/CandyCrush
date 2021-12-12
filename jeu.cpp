#include "Jeu.hpp"

void jeu::start(){
    for (int i=0; i<taille_plateau; i++){
        plateau.push_back({});
        for (int j=0; j<taille_plateau; j++){
            plateau[i].push_back(rand()%nb_couleurs_bonbon);
        }
    }
    search_combinaison();
}

vector<vector<int> > jeu::check_lines(vector<vector<int> > plat){
    cout << "check_lines" << endl;
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plat[i][j] == plat[i][j+1] && plat[i][j] == plat[i][j+2]){ // si a = b et a = c alors b = c
                plat[i][j] = -1;
                plat[i][j+1] = -1;
                plat[i][j+2] = -1;
            }
        }
    }
    return plat;
}

vector<vector<int> > jeu::check_rows(vector<vector<int> > plat){
    cout << "check rows"<< endl;
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plat[j][i] == plat[j+1][i] && plat[j][i] == plat[j+2][i]){
                plat[j][i] = -1;
                plat[j+1][i] = -1;
                plat[j+2][i] = -1;
            }
        }
    }
    return plat;
}

void jeu::search_combinaison(){
    vector<vector<int >> ancien_plateau;
    while (ancien_plateau != plateau){
        ancien_plateau = plateau;
        set_plateau(check_rows(plateau));
        set_plateau(check_lines(plateau));
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
            if (plateau[i][j] == 0){cout << " B ,";}
            if (plateau[i][j] == 1){cout << " G ,";}
            if (plateau[i][j] == 4){cout << " Y ,";}
            if (plateau[i][j] == 2){cout << " R ,";}
            if (plateau[i][j] == 5){cout << " C ,";}
            if (plateau[i][j] == 3){cout << " M ,";}
            if (plateau[i][j] == 6){cout << " O ,";}
            if (plateau[i][j] == -1){cout << "-1 ,";}
        }
        cout << endl;
    }
    cout << endl;
}

void jeu::echange(coord a, coord b){
    swap(plateau[a.i][a.j], plateau[b.i][b.j]);
}

bool jeu::coup_possible(coord a, coord b){
    vector<vector<int >> test_plateau = get_plateau();
    swap(test_plateau[a.i][a.j], test_plateau[b.i][b.j]);
    test_plateau = check_lines(test_plateau);
    test_plateau = check_rows(test_plateau);
    for (auto &l: test_plateau){
        for (auto &i: l){
            if (i==-1){
                return true;
            }
        }
    }
    return false;
}

