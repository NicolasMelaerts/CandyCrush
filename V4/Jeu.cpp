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

void jeu::ExploseLigne(int l){
    cout << "Explose Ligne" << endl;
    vector <Point> to_explose;

    for (int i = 0; i<9;i++){
        if (E[l][i].get()->getMyId()<0 or (E[l][i].get()->getMyId()>0 and E[l][i].get()->getMyId()<7)){
            to_explose.push_back({l,i});
            c.augmente_score(niv, 100);
            plateau[l][i] = -20;
        }
    }
    for (auto &b: to_explose)
        E[b.x][b.y].get()->DoExplosion();
    wait_anim();
    for (auto &b: to_explose){
        E[b.x][b.y].get()->setPosPlat({1000,1000});
        E[b.x][b.y].get()->setCouleur(FL_BLACK);
    }
}

void jeu::ExploseColonne(int col){
    cout << "Explose Colonne" << endl;
    vector <Point> to_explose;

    for (int i = 0; i<9;i++){
        if (E[i][col].get()->getMyId()<0 or (E[i][col].get()->getMyId()>0 and E[i][col].get()->getMyId()<7)){
            to_explose.push_back({i,col});
            c.augmente_score(niv, 100);
            plateau[i][col] = -20;
        }

    }
    for (auto &b: to_explose)
        E[b.x][b.y].get()->DoExplosion();
    wait_anim();
    for (auto &b: to_explose){
        E[b.x][b.y].get()->setPosPlat({1000,1000});
        E[b.x][b.y].get()->setCouleur(FL_BLACK);
    }
}
void jeu::ExploseBBspecialRond(Point empl){
    cout << "Explose BB special rond" << endl;
    vector <Point> to_explose;

    if (empl.x == 0){
        if (empl.y == 0){
            to_explose.push_back({empl.x+1, empl.y});
            to_explose.push_back({empl.x+1, empl.y+1});
            to_explose.push_back({empl.x, empl.y+1});
        }
        if (empl.y == 8){
            to_explose.push_back({empl.x, empl.y-1});
            to_explose.push_back({empl.x+1, empl.y-1});
            to_explose.push_back({empl.x+1, empl.y});
        }
        else{
            to_explose.push_back({empl.x, empl.y-1});
            to_explose.push_back({empl.x, empl.y+1});
            to_explose.push_back({empl.x+1, empl.y-1});
            to_explose.push_back({empl.x+1, empl.y});
            to_explose.push_back({empl.x+1, empl.y+1});
        }
    }

    else if (empl.x == 8){
        if (empl.y == 0){
            to_explose.push_back({empl.x-1, empl.y});
            to_explose.push_back({empl.x-1, empl.y+1});
            to_explose.push_back({empl.x, empl.y+1});
        }
        if (empl.y == 8){
            to_explose.push_back({empl.x, empl.y-1});
            to_explose.push_back({empl.x-1, empl.y-1});
            to_explose.push_back({empl.x-1, empl.y});
        }
        else{
            to_explose.push_back({empl.x, empl.y-1});
            to_explose.push_back({empl.x, empl.y+1});
            to_explose.push_back({empl.x-1, empl.y-1});
            to_explose.push_back({empl.x-1, empl.y});
            to_explose.push_back({empl.x-1, empl.y+1});
        }
    }

    else if (empl.y == 0 && empl.x != 0 and empl.x != 8){
        to_explose.push_back({empl.x-1, empl.y});
        to_explose.push_back({empl.x-1, empl.y+1});
        to_explose.push_back({empl.x, empl.y+1});
        to_explose.push_back({empl.x+1, empl.y+1});
        to_explose.push_back({empl.x+1, empl.y});
    }

    else if (empl.y == 8 && empl.x != 0 and empl.x != 8){
        to_explose.push_back({empl.x-1, empl.y});
        to_explose.push_back({empl.x-1, empl.y-1});
        to_explose.push_back({empl.x, empl.y-1});
        to_explose.push_back({empl.x+1, empl.y-1});
        to_explose.push_back({empl.x+1, empl.y});
    }

    else{
        to_explose.push_back({empl.x-1, empl.y-1});
        to_explose.push_back({empl.x-1, empl.y});
        to_explose.push_back({empl.x-1, empl.y+1});
        to_explose.push_back({empl.x, empl.y+1});
        to_explose.push_back({empl.x, empl.y-1});
        to_explose.push_back({empl.x+1, empl.y+1});
        to_explose.push_back({empl.x+1, empl.y});
        to_explose.push_back({empl.x+1, empl.y-1});
    }

    for (auto &b: to_explose){
        E[b.x][b.y].get()->DoExplosion();
    }
    wait_anim();
    for (auto &b: to_explose){
        if (plateau[b.x][b.y] != 0 && plateau[b.x][b.y]!=20 and plateau[b.x][b.y]!=21 && plateau[b.x][b.y]!=30 and plateau[b.x][b.y]!=-20){
            E[b.x][b.y].get()->setPosPlat({1000,1000});
            E[b.x][b.y].get()->setCouleur(FL_BLACK);
            plateau[b.x][b.y] = -20;
        }
    }
};

void jeu::DoExplose(vector<Point> to_explose){
    for (auto &b: to_explose)
        E[b.x][b.y].get()->DoExplosion();
    wait_anim();
    for (auto &b: to_explose){
        E[b.x][b.y].get()->setPosPlat({1000,1000});
        E[b.x][b.y].get()->setCouleur(FL_BLACK);
    }
    for (auto &b: to_explose){
        if (E[b.x][b.y].get()->getMyId()<0 and E[b.x][b.y].get()->getMyId()>-7){
            ExploseLigne(b.x);
        }
        if (E[b.x][b.y].get()->getMyId()<-6 and E[b.x][b.y].get()->getMyId()>-13){
            ExploseColonne(b.y);
        }
        if (E[b.x][b.y].get()->getMyId()<-12 and E[b.x][b.y].get()->getMyId()>-19){
            ExploseBBspecialRond(b);
        }
    }
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
    cout << "check lines" << endl;
    afficher_plateau_de_jeu();
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (E[i][j].get()->getcouleur() == E[i][j+1].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+2].get()->getcouleur()){
                if (E[i][j].get()->getcouleur()!=FL_BLACK ){
                    if (plat[i][j] != 0 && plat[i][j]!=20 and plat[i][j]!=21 && plat[i][j]!=30 && plat[i][j]!=-20 && plat[i][j+1]!=-20 && plat[i][j+2]!=-20){
                        plat[i][j] = -20;
                        plat[i][j+1] = -20;
                        plat[i][j+2] = -20;
                    }
                }
            }
        }
    }
    return plat;
}

vector<vector<int> > jeu::check_rows(vector<vector<int> > plat){
    cout << "check rows" << endl;
    afficher_plateau_de_jeu();
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (E[j][i].get()->getcouleur() == E[j+1][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+2][i].get()->getcouleur()){
                if (E[j][i].get()->getcouleur()!=FL_BLACK){
                    if (plat[j][i]!=0 && plat[j][i]!=20 and plat[j][i]!=21 && plat[i][j]!=30 && plat[j][i]!=-20 && plat[j+1][i]!=-20 && plat[j+2][i]!=-20){
                        plat[j][i] = -20;
                        plat[j+1][i] = -20;
                        plat[j+2][i] = -20;
                    }
                }
            }
        }
    }
    return plat;
}

void jeu::coup_cookie(int id, Point cookie_to_delete){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){
            if (plateau[i][j]==id){
                plateau[i][j] = -20;
            }
        }
    }
    plateau[cookie_to_delete.x][cookie_to_delete.y] = -20;
    cout << "cookie coup" << endl;
    afficher_plateau_de_jeu();
}

void jeu::check_5bonbons(){
    afficher_plateau_de_jeu();
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-4; j++){
            //horizontal
            if (E[i][j].get()->getcouleur() == E[i][j+1].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+2].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+3].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+4].get()->getcouleur()){
                if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30 and plateau[i][j]!=-20){

                    plateau[i][j] = -20;
                    plateau[i][j+1] = -20;

                    plateau[i][j+2] = -19;
                    BonbonSpecialRondCookies bsrc{{i, j+2}, FL_BLACK, 20};
                    E[i][j+2] = make_shared<BonbonSpecialRondCookies>(bsrc);

                    plateau[i][j+3] = -20;
                    plateau[i][j+4] = -20;
                }
            }
            if (E[j][i].get()->getcouleur() == E[j+1][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+2][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+3][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+4][i].get()->getcouleur()){
                if (plateau[j][i] != 0 && plateau[j][i]!=20 and plateau[j][i]!=21 && plateau[j][i]!=30 and plateau[j][i]!=-20){

                    plateau[j][i] = -20;
                    plateau[j+1][i] = -20;

                    plateau[j+2][i] = -19;
                    BonbonSpecialRondCookies bsrc{{j+2, i}, FL_BLACK, 20};
                    E[j+2][i] = make_shared<BonbonSpecialRondCookies>(bsrc);

                    plateau[j+3][i] = -20;
                    plateau[j+4][i] = -20;
                }
            }
        }
    }
    afficher_plateau_de_jeu();
}

void jeu::check_4bonbons(){
    cout << "check 4" << endl;
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-3; j++){
            //horizontal
            if (E[i][j].get()->getcouleur() == E[i][j+1].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+2].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+3].get()->getcouleur()){
                if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30 and plateau[i][j]!=-20){ // MURs

                    plateau[i][j] = -20;
                    plateau[i][j+1] = -20;

                    plateau[i][j+2] = ((E[i][j].get()->getMyId())*-1);

                    BonbonSpecialHorizontal bsh{{i,j+2}, E[i][j+2].get()->getcouleur(), 40,20};
                    E[i][j+2] = make_shared<BonbonSpecialHorizontal>(bsh);

                    plateau[i][j+3] = -20;
                }
            }
            if (E[j][i].get()->getcouleur() == E[j+1][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+2][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+3][i].get()->getcouleur()){
                if (plateau[j][i] != 0 && plateau[j][i]!=20 and plateau[j][i]!=21 && plateau[j][i]!=30 and plateau[i][j]!=-20){ // MURs

                    plateau[j][i] = -20;
                    plateau[j+1][i] = -20;

                    plateau[j+2][i] = ((E[j][i].get()->getMyId())*-1)-6;
                    BonbonSpecialVertical bsv{{j+2,i}, E[j+2][i].get()->getcouleur(), 20,40};
                    E[j+2][i] = make_shared<BonbonSpecialVertical>(bsv);

                    plateau[j+3][i] = -20;
                }
            }
        }
    }
}

void jeu::check_3bonbons(){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (E[i][j].get()->getcouleur() == E[i][j+1].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+2].get()->getcouleur()){
                if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30){
                    plateau[i][j] = -20;
                    plateau[i][j+1] = -20;
                    plateau[i][j+2] = -20;
                }
            }
            if (E[j][i].get()->getcouleur() == E[j+1][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+2][i].get()->getcouleur()){
                if (plateau[j][i]!=0 && plateau[j][i]!=20 and plateau[j][i]!=21 && plateau[i][j]!=30){
                    plateau[j][i] = -20;
                    plateau[j+1][i] = -20;
                    plateau[j+2][i] = -20;
                }
            }
        }
    }
}

void jeu::check_L(){
    cout << "check L" << endl;
    afficher_plateau_de_jeu();
    for (int i=0; i<taille_plateau-2; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30 and plateau[i][j]!=-20 and E[i][j].get()->getcouleur()!= FL_BLACK){
                if(E[i][j].get()->getcouleur() == E[i+1][j].get()->getcouleur() && E[i][j].get()->getcouleur()== E[i+2][j].get()->getcouleur() && 
                   E[i][j].get()->getcouleur()==E[i+2][j+1].get()->getcouleur() && E[i][j].get()->getcouleur()==E[i+2][j+2].get()->getcouleur()){
                    plateau[i][j] = ((E[i][j].get()->getMyId())*-1)-12;
                    BonbonSpecialRond bsr{{i,j}, E[i][j].get()->getcouleur(), 20};
                    E[i][j] = make_shared<BonbonSpecialRond>(bsr);
                    plateau[i+1][j] = -20;
                    plateau[i+2][j] = -20;
                    plateau[i+2][j+1] = -20;
                    plateau[i+2][j+2] = -20;
                }
                
                if(E[i][j].get()->getcouleur() == E[i+1][j].get()->getcouleur() && E[i][j].get()->getcouleur()== E[i+2][j].get()->getcouleur() && 
                   E[i][j].get()->getcouleur()==E[i][j+1].get()->getcouleur() && E[i][j].get()->getcouleur()==E[i][j+2].get()->getcouleur()){
                    
                    plateau[i][j] = ((E[i][j].get()->getMyId())*-1)-12;

                    BonbonSpecialRond bsr{{i,j}, E[i][j].get()->getcouleur(), 20};
                    E[i][j] = make_shared<BonbonSpecialRond>(bsr);
                    plateau[i+1][j] = -20;
                    plateau[i+2][j] = -20;
                    plateau[i][j+1] = -20;
                    plateau[i][j+2] = -20;
                    cout << "2.5" << endl;
                    afficher_plateau_de_jeu();
                }
                if(E[i+2][j].get()->getcouleur() == E[i+2][j+1].get()->getcouleur() && E[i+2][j].get()->getcouleur()== E[i+2][j+2].get()->getcouleur() && 
                   E[i+2][j].get()->getcouleur()==E[i+1][j+2].get()->getcouleur() && E[i+2][j].get()->getcouleur()==E[i][j+2].get()->getcouleur() and E[i+2][j].get()->getcouleur()!= FL_BLACK ){
                       cout << "3" << endl;
                    plateau[i+2][j] = ((E[i+2][j].get()->getMyId())*-1)-12;
                    BonbonSpecialRond bsr{{i+2,j}, E[i+2][j].get()->getcouleur(), 20};
                    E[i+2][j] = make_shared<BonbonSpecialRond>(bsr);
                    plateau[i+2][j+1] = -20;
                    plateau[i+2][j+2] = -20;
                    plateau[i+1][j+2] = -20;
                    plateau[i][j+2] = -20;
                }
                if(E[i][j].get()->getcouleur() == E[i][j+1].get()->getcouleur() && E[i][j].get()->getcouleur()== E[i][j+2].get()->getcouleur() && 
                   E[i][j].get()->getcouleur()==E[i+1][j+2].get()->getcouleur() && E[i][j].get()->getcouleur()==E[i+2][j+2].get()->getcouleur()){
                       cout << "4 = "<< i << j << endl;
                    plateau[i][j] = ((E[i][j].get()->getMyId())*-1)-12;
                    BonbonSpecialRond bsr{{i,j}, E[i][j].get()->getcouleur(), 20};
                    E[i][j] = make_shared<BonbonSpecialRond>(bsr);
                    plateau[i][j+1] = -20;
                    plateau[i][j+2] = -20;
                    plateau[i+1][j+2] = -20;
                    plateau[i+2][j+2] = -20;
                }
            }
        }
    }
    cout << "check L fin" << endl;
    afficher_plateau_de_jeu();
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
    check_L();

    set_plateau(check_rows(get_plateau()));
    set_plateau(check_lines(get_plateau()));

    afficher_plateau_de_jeu();

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
        check_4bonbons();
        check_L();
        
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
                    if (i<8 and E[k-1][i+1].get()->getMyId()!=0 and plateau[k-1][i+1]!=-20){
                        E[k-1][i+1].get()->ElementMove(4);
                        wait_anim();
                        E[k-1][i+1].get()->setPosPlat({k, i});
                        echange({k-1, i+1}, {k,i});
                    }
                    else{
                        if (E[k-1][i-1].get()->getMyId()!=0 and plateau[k-1][i+1]!=-20){
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
    cout << "Plateau :" << endl;
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

            if (plateau[i][j] == -1){cout <<  "BHR ,";}
            if (plateau[i][j] == -2){cout <<  "BHB ,";}
            if (plateau[i][j] == -3){cout <<  "BHJ ,";}
            if (plateau[i][j] == -4){cout <<  "BHV ,";}
            if (plateau[i][j] == -5){cout <<  "BHM ,";}
            if (plateau[i][j] == -6){cout <<  "BOH ,";}

            if (plateau[i][j] == -7){cout <<  "BVR ,";}
            if (plateau[i][j] == -8){cout <<  "BVB ,";}
            if (plateau[i][j] == -9){cout <<  "BVJ ,";}
            if (plateau[i][j] == -10){cout <<  "BVV ,";}
            if (plateau[i][j] == -11){cout <<  "BVM ,";}
            if (plateau[i][j] == -12){cout <<  "BVO ,";}

            if (plateau[i][j] == -13){cout <<  "BSR ,";}
            if (plateau[i][j] == -14){cout <<  "BSB ,";}
            if (plateau[i][j] == -15){cout <<  "BSJ ,";}
            if (plateau[i][j] == -16){cout <<  "BSV ,";}
            if (plateau[i][j] == -17){cout <<  "BSM ,";}
            if (plateau[i][j] == -18){cout <<  "BSO ,";}


            if (plateau[i][j] == -20){cout << "RDT ,";}
            if (plateau[i][j] == 0){cout << "MUR ,";}
            if (plateau[i][j] == 20){cout << "GLA ,";}
            if (plateau[i][j]==30){cout << "ING ,";}
            if (plateau[i][j]==-19){cout << "COO ,";}

            if (E[i][j].get()->getMyId() == 1){cout <<  "BR  ,";}
            if (E[i][j].get()->getMyId() == 2){cout <<  "BB  ,";}
            if (E[i][j].get()->getMyId() == 3){cout <<  "BJ  ,";}
            if (E[i][j].get()->getMyId() == 4){cout <<  "BV  ,";}
            if (E[i][j].get()->getMyId() == 5){cout <<  "BM  ,";}
            if (E[i][j].get()->getMyId() == 6){cout <<  "BO  ,";}

            if (E[i][j].get()->getMyId() == -1){cout <<  "BHR ,";}
            if (E[i][j].get()->getMyId() == -2){cout <<  "BHB ,";}
            if (E[i][j].get()->getMyId() == -3){cout <<  "BHJ ,";}
            if (E[i][j].get()->getMyId() == -4){cout <<  "BHV ,";}
            if (E[i][j].get()->getMyId() == -5){cout <<  "BHM ,";}
            if (E[i][j].get()->getMyId() == -6){cout <<  "BOH ,";}

            if (E[i][j].get()->getMyId() == -7){cout <<  "BVR ,";}
            if (E[i][j].get()->getMyId() == -8){cout <<  "BVB ,";}
            if (E[i][j].get()->getMyId() == -9){cout <<  "BVJ ,";}
            if (E[i][j].get()->getMyId() == -10){cout <<  "BVV ,";}
            if (E[i][j].get()->getMyId() == -11){cout <<  "BVM ,";}
            if (E[i][j].get()->getMyId() == -12){cout <<  "BVO ,";}

            if (E[i][j].get()->getMyId() == -13){cout <<  "BSR ,";}
            if (E[i][j].get()->getMyId() == -14){cout <<  "BSB ,";}
            if (E[i][j].get()->getMyId() == -15){cout <<  "BSJ ,";}
            if (E[i][j].get()->getMyId() == -16){cout <<  "BSV ,";}
            if (E[i][j].get()->getMyId() == -17){cout <<  "BSM ,";}
            if (E[i][j].get()->getMyId() == -18){cout <<  "BSO ,";}


            if (E[i][j].get()->getMyId() == -20){cout << "RDT ,";}
            if (E[i][j].get()->getMyId() == 0){cout << "MUR ,";}
            if (E[i][j].get()->getMyId() == 20){cout << "GLA ,";}
            if (E[i][j].get()->getMyId() == 21){cout << "GLA ,";}
            if (E[i][j].get()->getMyId()==30){cout << "ING ,";}
            if (E[i][j].get()->getMyId()==-19){cout << "COO ,";}
        }
        cout << endl;
    }
    cout << endl;


    cout << "E :" << endl;
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){
            //if (E[i][j].get()->getEnlever() == 0){cout <<  "BONB ,";}
            //else {cout << "RIEN ,";}

            if (E[i][j].get()->getMyId() == 1){cout <<  "BR  ,";}
            if (E[i][j].get()->getMyId() == 2){cout <<  "BB  ,";}
            if (E[i][j].get()->getMyId() == 3){cout <<  "BJ  ,";}
            if (E[i][j].get()->getMyId() == 4){cout <<  "BV  ,";}
            if (E[i][j].get()->getMyId() == 5){cout <<  "BM  ,";}
            if (E[i][j].get()->getMyId() == 6){cout <<  "BO  ,";}

            if (E[i][j].get()->getMyId() == -1){cout <<  "BHR ,";}
            if (E[i][j].get()->getMyId() == -2){cout <<  "BHB ,";}
            if (E[i][j].get()->getMyId() == -3){cout <<  "BHJ ,";}
            if (E[i][j].get()->getMyId() == -4){cout <<  "BHV ,";}
            if (E[i][j].get()->getMyId() == -5){cout <<  "BHM ,";}
            if (E[i][j].get()->getMyId() == -6){cout <<  "BOH ,";}

            if (E[i][j].get()->getMyId() == -7){cout <<  "BVR ,";}
            if (E[i][j].get()->getMyId() == -8){cout <<  "BVB ,";}
            if (E[i][j].get()->getMyId() == -9){cout <<  "BVJ ,";}
            if (E[i][j].get()->getMyId() == -10){cout <<  "BVV ,";}
            if (E[i][j].get()->getMyId() == -11){cout <<  "BVM ,";}
            if (E[i][j].get()->getMyId() == -12){cout <<  "BVO ,";}

            if (E[i][j].get()->getMyId() == -13){cout <<  "BSR ,";}
            if (E[i][j].get()->getMyId() == -14){cout <<  "BSB ,";}
            if (E[i][j].get()->getMyId() == -15){cout <<  "BSJ ,";}
            if (E[i][j].get()->getMyId() == -16){cout <<  "BSV ,";}
            if (E[i][j].get()->getMyId() == -17){cout <<  "BSM ,";}
            if (E[i][j].get()->getMyId() == -18){cout <<  "BSO ,";}


            if (E[i][j].get()->getMyId() == -20){cout << "RDT ,";}
            if (E[i][j].get()->getMyId() == 0){cout << "MUR ,";}
            if (E[i][j].get()->getMyId() == 20){cout << "GLA ,";}
            if (E[i][j].get()->getMyId() == 21){cout << "GLA ,";}
            if (E[i][j].get()->getMyId()==30){cout << "ING ,";}
            if (E[i][j].get()->getMyId()==-19){cout << "COO ,";}
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
    swap(E[a.x][a.y], E[b.x][b.y]);
    test_plateau = check_lines(test_plateau);
    test_plateau = check_rows(test_plateau);
    for (auto &l: test_plateau){
        for (auto &i: l){
            if (i==-20){
                swap(E[a.x][a.y], E[b.x][b.y]);
                return true;
            }
        }
    }
    swap(E[a.x][a.y], E[b.x][b.y]);
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