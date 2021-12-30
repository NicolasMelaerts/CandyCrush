#include "Jeu.hpp"

/*--------------------------------------------------

jeu class

--------------------------------------------------*/

void jeu::ouvertureNiv(int niv){
    E.clear();
    ifstream Niv("NiveauDeJeu/Niv"+to_string(niv));  //Ouverture d'un fichier en lecture
    if(Niv){
        string Case;
        int i= 0, j=0;
        E.push_back({});
        while(Niv >> Case){
            if (j==9){
                i++;
                j=0;
                E.push_back({});
            }
            int ajout = stoi(Case);
            if (ajout==0){
                Mur m{{i,j}, 40, 40};
                E[i].push_back(make_shared<Mur>(m));
            }
            if (ajout >= 1 && ajout <= 6){
                Bonbon b{{i,j}, Colors[ajout-1], 35, 35};
                E[i].push_back(make_shared<Bonbon>(b));
            }
            if (ajout <= -1 && ajout >= -6){
                BonbonSpecialHorizontal bsh{{i,j}, Colors[abs(ajout+1)%6], 40,20};
                E[i].push_back(make_shared<BonbonSpecialHorizontal>(bsh));
            }
            if (ajout <= -7 && ajout >= -12){
                BonbonSpecialVertical bsv{{i,j}, Colors[abs(ajout+1)%6], 20,40};
                E[i].push_back(make_shared<BonbonSpecialVertical>(bsv));
            }
            if (ajout >= -18 && ajout <= -13){
                BonbonSpecialRond bsr{{i,j}, Colors[abs(ajout+1)%6], 20};
                E[i].push_back(make_shared<BonbonSpecialRond>(bsr));
            }
            if (ajout ==-19){
                BonbonSpecialRondCookies bsrc{{i, j}, FL_BLACK, 20};
                E[i].push_back(make_shared<BonbonSpecialRondCookies>(bsrc));
            }
            if (ajout ==30){ // cerise
                Ingredient ingr{{i, j}, "C", 20, 20};
                E[i].push_back(make_shared<Ingredient>(ingr));
            }
            if (ajout ==31){ //noisette
                Ingredient ingr{{i, j}, "N", 20, 20};
                E[i].push_back(make_shared<Ingredient>(ingr));
            }
            if (ajout==20){
                Glacage g{{i,j}, 45, 45};
                E[i].push_back(make_shared<Glacage>(g));
            }

            j++;
        }
        Niv.close();
    }
    else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}

void jeu::ouvertureInfo(int niv){

    ifstream Info("NiveauDeJeu/Info"+to_string(niv));
    

    if(Info){
        string inf;
        int i = 0;
        while(Info >> inf){
            if (i==0)
                c.set_meilleur_score(stoi(inf));
            if (i==1)
                c.set_nb_coups_restants(stoi(inf));
            i++;
        }
        Info.close();
    }
    else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}


vector<Point> jeu::setToExplose(){
    vector <Point> to_explose;
    for (int i = 0; i<9;i++){
        for (int k = 0; k<9;k++){
            if (getelemplateau(i,k)==-20){
                to_explose.push_back({i,k});
                c.augmente_score(niv, 100);
            }   
        }
    }
    return to_explose;
}

void jeu::DoExplose(vector<Point> to_explose){
    for (auto &b: to_explose)
        E[b.x][b.y].get()->DoExplosion();
    
    wait_anim();
    for (auto &b: to_explose)
        E[b.x][b.y].get()->setPosPlat({1000,1000});
}

void jeu::DoExploseGlacage(){
    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau(); k++){
            if (plateau[i][k] == 20){
                if (plateau[i+1][k] == -20 or plateau[i-1][k] == -20 or plateau[i][k+1] == -20 or plateau[i][k-1] == -20){
                    cout << i << ", " << k<< endl;
                    if (E[i][k].get()->getMyId() == 20){
                        E[i][k].get()->DoExplosion();
                        c.augmente_score(niv, 150);
                    }
                    else{
                        plateau[i][k] = -20;
                        E[i][k].get()->setPosPlat({1000,1000});
                        c.augmente_score(niv, 250);
                    }
                    
                }
            }

        }
    }
}

void jeu::check_ingredient(){
    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau(); k++){
            if (plateau[i][k]==30){
                if (i==8){
                    plateau[i][k] = -20;
                    E[i][k].get()->setPosPlat({1000,1000});
                    c.augmente_score(niv, 300);
                }
            }
        }
    } 
}



vector<vector<int> > jeu::check_lines(vector<vector<int> > plat){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plat[i][j] == plat[i][j+1] && plat[i][j] == plat[i][j+2]&&plat[i][j+1] == plat[i][j+2]){ // si a = b et a = c alors b = c
                if (plat[i][j] != 0 && plat[i][j]!=20 and plat[i][j]!=21 && plat[i][j]!=30){ // MURs
                    //if (j<taille_plateau-3){
                        //if (plat[i][j+3] == plat[j][i]){
                            //plat[i][j+3] = -20;  //devient un bonbon spécial -> (plat[i][j+3]*-1)-12;
                        //}
                    //}
                    plat[i][j] = -20;
                    plat[i][j+1] = -20;
                    plat[i][j+2] = -20;
                }
            }
        }
    }
    return plat;
}

vector<vector<int> > jeu::check_rows(vector<vector<int> > plat){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plat[j][i] == plat[j+1][i] && plat[j][i] == plat[j+2][i]){
                if (plat[j][i]!=0 && plat[j][i]!=20 and plat[j][i]!=21 && plat[i][j]!=30){ //MURs
                    //if (i<taille_plateau-3){
                        //if (plat[j+3][i] == plat[j][i])
                            //plat[j+3][i] = -20;   // devient un bonbon spécial -> plat[j+3][i] = (plat[j+3][i]*-1)-12;
                    //}
                    plat[j][i] = -20;
                    plat[j+1][i] = -20;
                    plat[j+2][i] = -20;
                }
            }
        }
    }
    return plat;
}

void jeu::coup_cookie(int id, Point cookie_to_delete){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){
            if (E[i][j].get()->getMyId()==id){
                plateau[i][j] = -20;
            }
        }
    }
    plateau[cookie_to_delete.x][cookie_to_delete.y] = -20;
}

void jeu::check_5bonbons(){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-4; j++){
            //horizontal
            if (plateau[i][j] == plateau[i][j+1] && plateau[i][j] == plateau[i][j+2] && plateau[i][j] == plateau[i][j+3] && plateau[i][j] == plateau[i][j+4]){ // si a = b et a = c alors b = c
                if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30 and plateau[i][j]!=-20){ // MURs

                    plateau[i][j] = -20;
                    plateau[i][j+1] = -20;

                    plateau[i][j+2] = 19;
                    BonbonSpecialRondCookies bsrc{{i, j+2}, FL_BLACK, 20};
                    E[i][j+2] = make_shared<BonbonSpecialRondCookies>(bsrc);

                    plateau[i][j+3] = -20;
                    plateau[i][j+4] = -20;
                }
            }
            if (plateau[j][i] == plateau[j+1][i] && plateau[j][i] == plateau[j+2][i] && plateau[j][i] == plateau[j+3][i] && plateau[j][i] == plateau[j+4][i]){ // si a = b et a = c alors b = c
                if (plateau[j][i] != 0 && plateau[j][i]!=20 and plateau[j][i]!=21 && plateau[j][i]!=30 and plateau[j][i]!=-20){ // MURs

                    plateau[j][i] = -20;
                    plateau[j+1][i] = -20;

                    plateau[j+2][i] = 19;
                    BonbonSpecialRondCookies bsrc{{j+2, i}, FL_BLACK, 20};
                    E[j+2][i] = make_shared<BonbonSpecialRondCookies>(bsrc);

                    plateau[j+3][i] = -20;
                    plateau[j+4][i] = -20;
                }
            }
        }
    }
}

void jeu::check_4bonbons(){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-4; j++){
            //horizontal
            if (plateau[i][j] == plateau[i][j+1] && plateau[i][j] == plateau[i][j+2] && plateau[i][j] == plateau[i][j+3]){
                if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30 and plateau[i][j]!=-20){ // MURs

                    plateau[i][j] = -20;
                    plateau[i][j+1] = -20;

                    plateau[i][j+2] = ((E[i][j].get()->getMyId())*-1);

                    BonbonSpecialHorizontal bsh{{i,j+2}, Colors[E[i][j].get()->getMyId()-1], 40,20};
                    E[i][j+2] = make_shared<BonbonSpecialHorizontal>(bsh);

                    plateau[i][j+3] = -20;
                }
            }
            if (plateau[j][i] == plateau[j+1][i] && plateau[j][i] == plateau[j+2][i] && plateau[j][i] == plateau[j+3][i]){
                if (plateau[j][i] != 0 && plateau[j][i]!=20 and plateau[j][i]!=21 && plateau[j][i]!=30 and plateau[i][j]!=-20){ // MURs

                    plateau[j][i] = -20;
                    plateau[j+1][i] = -20;

                    plateau[j+2][i] = ((E[i][j].get()->getMyId())*-1)-6;
                    BonbonSpecialVertical bsv{{j+2,i}, Colors[E[j][i].get()->getMyId()-1], 20,40};
                    E[j+2][i] = make_shared<BonbonSpecialVertical>(bsv);

                    plateau[j+3][i] = -20;
                }
            }
        }
    }
}


void jeu::init_plateau(vector< vector<shared_ptr<ElementDeJeu>> > E){
    plateau.clear();
    for (int i =0; i<taille_plateau; i++){
        plateau.push_back({});
        for (int j=0; j<taille_plateau; j++){
            plateau[i].push_back(E[i][j].get()->getMyId());
        }
    }
}


void jeu::search_combinaison(){
    
    check_5bonbons();
    check_4bonbons();

    set_plateau(check_rows(get_plateau()));
    set_plateau(check_lines(get_plateau()));
    DoExploseGlacage();  

    while (get_finish_fall()){
        cout << "MAJ_CANVAS" << endl;

        DoExplose(setToExplose());

        vector<vector<int >> ancien_plateau;

        fall_mur_diagonale();
        
        while (ancien_plateau != get_plateau()){
            ancien_plateau = get_plateau();
            fall();
        }
        check_ingredient();

        check_5bonbons();
        set_plateau(check_rows(get_plateau()));
        set_plateau(check_lines(get_plateau()));

        while (!coup_possible()){  
            cout << "Auncun coup possible on melange" << endl;
            set_aucun_coup_poss(1);
            melanger();
        }
    }
    c.do_coup();
    
}

void jeu::fall(){
     
    vector <Point> to_fall;


    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau()-1; k++){
            if (plateau[k+1][i]==-20 and plateau[k][i]!=-20 and E[k][i].get()->getMyId()!=0 and E[k][i].get()->getMyId()!=20 and E[k][i].get()->getMyId()!=21){
                to_fall.push_back({k,i});
            }
        }
    }

    for (auto &f: to_fall){
        E[f.x][f.y].get()->ElementMove(0);
        wait_anim();
        E[f.x][f.y].get()->setPosPlat({f.x+1, f.y});
        echange(f, {f.x+1, f.y});
    }


    // ajout new bb
    for (int i=0; i<get_taille_plateau();i++){
        if (plateau[0][i] == -20){
            plateau[0][i] = rand()%nb_couleurs_bonbon+1;
            Bonbon b{{0,i}, Colors[getelemplateau(0,i)-1], 35,35};
            E[0][i] = make_shared<Bonbon>(b);
        }
    }

}

bool jeu::get_finish_fall(){
    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau(); k++){
            if (plateau[k][i]==-20)
                return 1;
        }
    }
    return 0;
}

void jeu::fall_mur_diagonale(){
    bool stop = false;
    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau(); k++){
            if (k>0){
                if ((plateau[k][i]==-20 and plateau[k-1][i]==0) or (plateau[k][i]==-20 and plateau[k-1][i]==20) or (plateau[k][i]==-20 and plateau[k-1][i]==21)){
                    cout << "Attention = " << k-1 << ", " << i << endl;
                    if (i<8 and E[k-1][i+1].get()->getMyId()!=0){
                        E[k-1][i+1].get()->ElementMove(4);
                        wait_anim();
                        E[k-1][i+1].get()->setPosPlat({k, i});
                        echange({k-1, i+1}, {k,i});
                    }
                    else{
                        if (E[k-1][i-1].get()->getMyId()!=0){
                            E[k-1][i-1].get()->ElementMove(5);
                            wait_anim();
                            E[k-1][i-1].get()->setPosPlat({k, i});
                            echange({k-1, i-1}, {k,i});
                        }
                    }
                }
            }
        }
    }
}



void jeu::afficher_plateau_de_jeu(){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){
            //if (E[i][j].get()->getEnlever() == 0){cout <<  "BONB ,";}
            //else {cout << "RIEN ,";}

            if (plateau[i][j] == 1){cout <<  "BR  ,";}
            if (plateau[i][j] == 2){cout <<  "BB  ,";}
            if (plateau[i][j] == 3){cout <<  "BJ  ,";}
            if (plateau[i][j] == 4){cout <<  "BV  ,";}
            if (plateau[i][j] == 5){cout <<  "BM  ,";}
            if (plateau[i][j] == 6){cout <<  "BO  ,";}

            if (plateau[i][j] == -20){cout << "RDT ,";}
            if (plateau[i][j] == 0){cout << "MUR ,";}
            if (plateau[i][j] == 20){cout << "GLA ,";}

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

void jeu::echange(Point a, Point b){
    swap(plateau[a.x][a.y], plateau[b.x][b.y]);
    swap(E[a.x][a.y], E[b.x][b.y]);
}

bool jeu::coup_possible(Point a, Point b){
    vector<vector<int >> test_plateau = get_plateau();
    swap(test_plateau[a.x][a.y], test_plateau[b.x][b.y]);
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

void jeu::wait_anim(){
    bool anim_en_cours=true;
    while (anim_en_cours){
        anim_en_cours = false;
        for (auto &l:E)
            for (auto &e:l)
                if (e.get()->animation_is_complete())
                    anim_en_cours = true;

        if (anim_en_cours)
            Fl::wait();
        }
}

bool jeu::coup_possible(){

    //ligne 
    for (int i=0; i<taille_plateau-1; i++){
        for (int j=0; j<taille_plateau; j++){
            if (E[i][j].get()->getMyId() != 0 and E[i][j].get()->getMyId() != 20 and E[i][j].get()->getMyId() != 21
            and E[i+1][j].get()->getMyId() != 0 and E[i+1][j].get()->getMyId() != 20 and E[i+1][j].get()->getMyId() != 21)
                if (coup_possible({i,j},{i+1, j}))
                    return true;
        }
    }

    //colonne
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-1; j++){
            if (E[i][j].get()->getMyId() != 0 and E[i][j].get()->getMyId() != 20 and E[i][j].get()->getMyId() != 21
            and E[i][j+1].get()->getMyId() != 0 and E[i][j+1].get()->getMyId() != 20 and E[i][j+1].get()->getMyId() != 21)
                if (coup_possible({i,j},{i, j+1}))
                    return true;
        }
    }

    return false;
}

void jeu::melanger(){
    for (int i =0; i<taille_plateau; i++){
        for (int j =0; j<taille_plateau; j++){
            if (E[i][j].get()->getMyId()>0 and E[i][j].get()->getMyId()<7){
                Bonbon b{{i,j}, Colors[rand()%6], 35, 35};
                E[i][j] = make_shared<Bonbon>(b);
            }
        }
    }
    init_plateau(E);
    search_combinaison();
}