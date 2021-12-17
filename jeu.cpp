#include "Jeu.hpp"

void jeu::ouvertureNiveau(){
    ifstream Niv("NiveauDeJeu/Niv2");  //Ouverture d'un fichier en lecture

    for (int i=0; i<taille_plateau; i++){
        plateau.push_back({});
        for (int j=0; j<taille_plateau; j++){
            plateau[i].push_back(-1);
        }
    }

    if(Niv){
        string Case;
        int i= 0, j=0;
        while(Niv >> Case){
            if (j==9){
                i++;
                j=0;
            }
            int k = stoi(Case);
            //cout << k << "[" << i << ", " << j  << "]" << endl; 
            plateau[i][j]= k;
            //afficher_plateau_de_jeu();
            j++;
            
        }
    }
    else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
    afficher_plateau_de_jeu();

}

vector<vector<int> > jeu::check_lines(vector<vector<int> > plat){
    cout << "check_lines" << endl;
    afficher_plateau_de_jeu();
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plat[i][j] == plat[i][j+1] && plat[i][j] == plat[i][j+2]){ // si a = b et a = c alors b = c
                if (plat[i][j] != 0){ // MURs
                    if (j<taille_plateau-3){
                        if (plat[i][j+3] == plat[j][i])
                            plat[i][j+3] = (plat[i][j+3]*-1)-12;
                    }
                    plat[i][j] = -20;
                    plat[i][j+1] = -20;
                    plat[i][j+2] = -20;
                }
            }
        }
    }
    afficher_plateau_de_jeu();
    return plat;
}

vector<vector<int> > jeu::check_rows(vector<vector<int> > plat){
    cout << "check rows"<< endl;
    afficher_plateau_de_jeu();
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plat[j][i] == plat[j+1][i] && plat[j][i] == plat[j+2][i]){
                if (plat[j][i]!=0){ //MURs
                    if (i<taille_plateau-3){
                        if (plat[j+3][i] == plat[j][i])
                            plat[j+3][i] = (plat[j+3][i]*-1)-12;
                    }
                    plat[j][i] = -20;
                    plat[j+1][i] = -20;
                    plat[j+2][i] = -20;
                }
            }
        }
    }
    afficher_plateau_de_jeu();
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
            if (plateau[j][i]!=-20){
                col.push_back(plateau[j][i]);
            }
        }
        while (col.size()!=taille_plateau){
            int new_bb;
            new_bb = rand()%nb_couleurs_bonbon;
            while (new_bb == 0){
                new_bb = rand()%nb_couleurs_bonbon;
            }
            cout << "Bonbon qui tombe = " << new_bb << endl;
            col.push_back(new_bb); 
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
            if (plateau[i][j] == 0){cout <<  "MUR ,";}

            if (plateau[i][j] == 1){cout <<  "BR  ,";}
            if (plateau[i][j] == 2){cout <<  "BB  ,";}
            if (plateau[i][j] == 3){cout <<  "BJ  ,";}
            if (plateau[i][j] == 4){cout <<  "BV  ,";}
            if (plateau[i][j] == 5){cout <<  "BM  ,";}
            if (plateau[i][j] == 6){cout <<  "BO  ,";}

            if (plateau[i][j] == -20){cout << "RDT ,";}

            if (plateau[i][j] ==-13){cout << "BSR ,";}
            if (plateau[i][j] ==-14){cout << "BSB ,";}
            if (plateau[i][j] ==-15){cout << "BSJ ,";}
            if (plateau[i][j] ==-16){cout << "BSV ,";}
            if (plateau[i][j] ==-17){cout << "BSM ,";}
            if (plateau[i][j] ==-18){cout << "BSO ,";}
            

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
            if (i==-20){
                return true;
            }
        }
    }
    return false;
}

