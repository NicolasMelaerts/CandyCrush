#include "Jeu.hpp"

/*--------------------------------------------------

Classe jeu

--------------------------------------------------*/

jeu::jeu(int niv):c{0,0}, niv{niv}{
    setGame(niv);
}


void jeu::setGame(int niveau){
    ouvertureNiv(niveau);
    ouvertureInfo(niveau);
    init_plateau(E);
    c.set_score(0);
    c.reset_nb_coup_joue();
    niv = niveau;
}


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
            if (ajout==20){ // Niv 2
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
            // ligne 1 le meilleur score
            // ligne 2 le nombre de coups pour le niveau
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


// Bonbon spécial horizontal
void jeu::ExploseLigne(int l){

    vector <Point> to_explose;

    for (int i = 0; i<9;i++){
        // si bonbon ou bonbons spécial
        if (E[l][i].get()->getMyId()<0 or (E[l][i].get()->getMyId()>0 and E[l][i].get()->getMyId()<7)){
            to_explose.push_back({l,i});
            c.augmente_score(niv, 500);
            plateau[l][i] = -20;
        }
    }
    Explose(to_explose);
}


// Bonbon spécial vertical
void jeu::ExploseColonne(int col){

    vector <Point> to_explose;

    for (int i = 0; i<9;i++){
        // si bonbon ou bonbons spécial
        if (E[i][col].get()->getMyId()<0 or (E[i][col].get()->getMyId()>0 and E[i][col].get()->getMyId()<7)){
            to_explose.push_back({i,col});
            c.augmente_score(niv, 500);
            plateau[i][col] = -20;
        }

    }
    Explose(to_explose);
}


// Bonbon emballé (bombe)
void jeu::ExploseBBspecialRond(Point empl){

    vector <Point> to_explose;

    // cas spéciaux sur les bords
    if (empl.x == 0){
        if (empl.y == 0){
            to_explose.push_back({empl.x+1, empl.y});
            to_explose.push_back({empl.x+1, empl.y+1});
            to_explose.push_back({empl.x, empl.y+1});
            c.augmente_score(niv, 500);
        }
        if (empl.y == 8){
            to_explose.push_back({empl.x, empl.y-1});
            to_explose.push_back({empl.x+1, empl.y-1});
            to_explose.push_back({empl.x+1, empl.y});
            c.augmente_score(niv, 500);
        }
        else{
            to_explose.push_back({empl.x, empl.y-1});
            to_explose.push_back({empl.x, empl.y+1});
            to_explose.push_back({empl.x+1, empl.y-1});
            to_explose.push_back({empl.x+1, empl.y});
            to_explose.push_back({empl.x+1, empl.y+1});
            c.augmente_score(niv, 500);
        }
    }

    else if (empl.x == 8){
        if (empl.y == 0){
            to_explose.push_back({empl.x-1, empl.y});
            to_explose.push_back({empl.x-1, empl.y+1});
            to_explose.push_back({empl.x, empl.y+1});
            c.augmente_score(niv, 500);
        }
        if (empl.y == 8){
            to_explose.push_back({empl.x, empl.y-1});
            to_explose.push_back({empl.x-1, empl.y-1});
            to_explose.push_back({empl.x-1, empl.y});
            c.augmente_score(niv, 500);
        }
        else{
            to_explose.push_back({empl.x, empl.y-1});
            to_explose.push_back({empl.x, empl.y+1});
            to_explose.push_back({empl.x-1, empl.y-1});
            to_explose.push_back({empl.x-1, empl.y});
            to_explose.push_back({empl.x-1, empl.y+1});
            c.augmente_score(niv, 500);
        }
    }

    else if (empl.y == 0 && empl.x != 0 and empl.x != 8){
        to_explose.push_back({empl.x-1, empl.y});
        to_explose.push_back({empl.x-1, empl.y+1});
        to_explose.push_back({empl.x, empl.y+1});
        to_explose.push_back({empl.x+1, empl.y+1});
        to_explose.push_back({empl.x+1, empl.y});
        c.augmente_score(niv, 500);
    }

    else if (empl.y == 8 && empl.x != 0 and empl.x != 8){
        to_explose.push_back({empl.x-1, empl.y});
        to_explose.push_back({empl.x-1, empl.y-1});
        to_explose.push_back({empl.x, empl.y-1});
        to_explose.push_back({empl.x+1, empl.y-1});
        to_explose.push_back({empl.x+1, empl.y});
        c.augmente_score(niv, 500);
    }

    // cas normal pas sur les bords
    else{
        to_explose.push_back({empl.x-1, empl.y-1});
        to_explose.push_back({empl.x-1, empl.y});
        to_explose.push_back({empl.x-1, empl.y+1});
        to_explose.push_back({empl.x, empl.y+1});
        to_explose.push_back({empl.x, empl.y-1});
        to_explose.push_back({empl.x+1, empl.y+1});
        to_explose.push_back({empl.x+1, empl.y});
        to_explose.push_back({empl.x+1, empl.y-1});
        c.augmente_score(niv, 500);
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
    Explose(to_explose);

    for (auto &b: to_explose){
        // Bonbon spécial horizontal
        if (E[b.x][b.y].get()->getMyId()<0 and E[b.x][b.y].get()->getMyId()>-7){
            ExploseLigne(b.x);
        }
        // Bonbon spécial vertical
        if (E[b.x][b.y].get()->getMyId()<-6 and E[b.x][b.y].get()->getMyId()>-13){
            ExploseColonne(b.y);
        }
        // Bonbon emballé (bombe)
        if (E[b.x][b.y].get()->getMyId()<-12 and E[b.x][b.y].get()->getMyId()>-19){
            ExploseBBspecialRond(b);
        }
    }
}


void jeu::Explose(vector<Point> to_explose){
    for (auto &b: to_explose)
        E[b.x][b.y].get()->DoExplosion();
    wait_anim();
    for (auto &b: to_explose){
        E[b.x][b.y].get()->setPosPlat({1000,1000});
        E[b.x][b.y].get()->setCouleur(FL_BLACK);
    }
}


void jeu::DoExploseGlacage(){
    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau(); k++){
            if (plateau[i][k] == 20){   // glacage
                // si un bonbon adjacent a explosé
                if (plateau[i+1][k] == -20 or plateau[i-1][k] == -20 or plateau[i][k+1] == -20 or plateau[i][k-1] == -20){
                    if (E[i][k].get()->getMyId() == 20){
                        E[i][k].get()->DoExplosion();   // glacage niv 2 devient glacage de niv 1
                        c.augmente_score(niv, 250);
                    }
                    else{
                        // glacage de niv 1 disparait
                        plateau[i][k] = -20;
                        E[i][k].get()->setPosPlat({1000,1000});
                        E[i][k].get()->setCouleur(FL_BLACK);
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
            if (plateau[i][k]==30){     // ingrédient
                if (i==8){  // tout en bas du plateau
                    plateau[i][k] = -20;
                    E[i][k].get()->setPosPlat({1000,1000});
                    c.augmente_score(niv, 1000);
                }
            }
        }
    } 
}


vector<vector<int> > jeu::check_3bonbons(vector<vector<int> > plat){
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
    // supprime tout les bonbons de la même couleur du bonbon qui a swap avec le cookie
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){
            if (plateau[i][j]==id){
                plateau[i][j] = -20;
            }
        }
    }
    // supprime le cookie aussi
    plateau[cookie_to_delete.x][cookie_to_delete.y] = -20;
}


void jeu::check_5bonbons(){
    // suite de 5 bonbons à l'horizontale ou à la verticale, devient bonbon spécial rond cookie = cookie
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-4; j++){
            //horizontal
            if (E[i][j].get()->getcouleur() == E[i][j+1].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+2].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+3].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+4].get()->getcouleur()){
                if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30 and plateau[i][j]!=-20){ // != Mur, Glacage, Ingrédient ou vide 

                    plateau[i][j] = -20;
                    plateau[i][j+1] = -20;

                    plateau[i][j+2] = -19;
                    BonbonSpecialRondCookies bsrc{{i, j+2}, FL_BLACK, 20};
                    E[i][j+2] = make_shared<BonbonSpecialRondCookies>(bsrc);

                    plateau[i][j+3] = -20;
                    plateau[i][j+4] = -20;
                }
            }
            //vertical
            if (E[j][i].get()->getcouleur() == E[j+1][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+2][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+3][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+4][i].get()->getcouleur()){
                if (plateau[j][i] != 0 && plateau[j][i]!=20 and plateau[j][i]!=21 && plateau[j][i]!=30 and plateau[j][i]!=-20){  // != Mur, Glacage, Ingrédient, vide

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
}


void jeu::check_4bonbons(){
    // suite de 4 bonbons à l'horizontale ou à la verticale, devient bonbon spécial horizontal/vertical
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-3; j++){
            //horizontal
            if (E[i][j].get()->getcouleur() == E[i][j+1].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+2].get()->getcouleur() && E[i][j].get()->getcouleur() == E[i][j+3].get()->getcouleur()){
                if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30 and plateau[i][j]!=-20 and E[i][j].get()->getcouleur()!= FL_BLACK){ // != Mur, Glacage, Ingrédient, vide

                    plateau[i][j] = -20;
                    plateau[i][j+1] = -20;

                    plateau[i][j+2] = ((E[i][j].get()->getMyId())*-1);

                    BonbonSpecialHorizontal bsh{{i,j+2}, E[i][j+2].get()->getcouleur(), 40,20};
                    E[i][j+2] = make_shared<BonbonSpecialHorizontal>(bsh);

                    plateau[i][j+3] = -20;
                }
            }
            //vertical
            if (E[j][i].get()->getcouleur() == E[j+1][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+2][i].get()->getcouleur() && E[j][i].get()->getcouleur() == E[j+3][i].get()->getcouleur()){
                if (plateau[j][i] != 0 && plateau[j][i]!=20 and plateau[j][i]!=21 && plateau[j][i]!=30 and plateau[j][i]!=-20 and E[j][i].get()->getcouleur()!= FL_BLACK){ // != Mur, Glacage, Ingrédient, vide

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


void jeu::check_L(){
// 4 types de L, devient bonbon spécial rond = bonbon emballé
//      -          -  -  -           -     -  -  -
//      -                -           -     -
//      -  -  -          _     -  -  -     -
    for (int i=0; i<taille_plateau-2; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plateau[i][j] != 0 && plateau[i][j]!=20 and plateau[i][j]!=21 && plateau[i][j]!=30 and plateau[i][j]!=-20 and E[i][j].get()->getcouleur()!= FL_BLACK){  // != Mur, Glacage, Ingrédient, vide
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
                }
                if(E[i+2][j].get()->getcouleur() == E[i+2][j+1].get()->getcouleur() && E[i+2][j].get()->getcouleur()== E[i+2][j+2].get()->getcouleur() && 
                   E[i+2][j].get()->getcouleur()==E[i+1][j+2].get()->getcouleur() && E[i+2][j].get()->getcouleur()==E[i][j+2].get()->getcouleur() and E[i+2][j].get()->getcouleur()!= FL_BLACK ){
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
}


void jeu::init_plateau(vector< vector<shared_ptr<ElementDeJeu>> > E){
    // plareau d'entier a partir de l'ID des elements de jeu
    plateau.clear();
    for (int i =0; i<taille_plateau; i++){
        plateau.push_back({});
        for (int j=0; j<taille_plateau; j++){
            plateau[i].push_back(E[i][j].get()->getMyId());
        }
    }
}


void jeu::search_combinaison(){

    // vérif toutes les combinaisons possibles
    check_5bonbons();
    check_4bonbons();
    check_L();
    set_plateau(check_3bonbons(get_plateau()));

    // les glacage explose seulement quand c'est un coup provoqué par le joueur
    DoExploseGlacage();  

    while (get_finish_fall()){      // encore des espace vide (-20) dans le plateau 

        DoExplose(setToExplose());  // faire exploser et disparaitre les bonbons qui on eu une combinaisons

        fall_mur_diagonale();   // espace vide en dessous d'un mur ou un glacage
        
        // pour faire tomber les bonbons dans les espaces vides
        vector<vector<int >> ancien_plateau;
        while (ancien_plateau != get_plateau()){
            ancien_plateau = get_plateau();
            fall();
        }

        check_ingredient();     // ingredient en bas du plateau 

        // vérif toutes les combinaisons possibles après fall
        check_5bonbons();
        check_4bonbons();
        check_L();
        set_plateau(check_3bonbons(get_plateau()));

        // cas ou le joueur ne peut pas faire de coups car aucune combinaison n'est possible
        while (!coup_possible()){  
            set_aucun_coup_poss(1);
            melanger();
        }
    }
    c.do_coup();    // total de coups restant - 1
    
}


void jeu::fall(){
     
    vector <Point> to_fall;

    // vérifie si le bonbon peut tomber d'un cran
    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau()-1; k++){
            if (plateau[k+1][i]==-20 and plateau[k][i]!=-20 and E[k][i].get()->getMyId()!=0 and E[k][i].get()->getMyId()!=20 and E[k][i].get()->getMyId()!=21){
                to_fall.push_back({k,i});
            }
        }
    }

    // animation des bonbon qui tombe et changement de leur position
    for (auto &f: to_fall){
        E[f.x][f.y].get()->ElementMove(0);
        wait_anim();
        E[f.x][f.y].get()->setPosPlat({f.x+1, f.y});
        echange(f, {f.x+1, f.y});
    }


    // ajout nouveau bonbon aléatoirement si espace libre en haut du plateau
    for (int i=0; i<get_taille_plateau();i++){
        if (plateau[0][i] == -20){
            plateau[0][i] = rand()%nb_couleurs_bonbon+1;
            Bonbon b{{0,i}, Colors[getelemplateau(0,i)-1], 35,35};
            E[0][i] = make_shared<Bonbon>(b);
        }
    }

}


bool jeu::get_finish_fall(){
    // vérifie si des emplacement son encore vide pour continuer aa faire tomber des bonbons
    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau(); k++){
            if (plateau[k][i]==-20)     // emplacement vide
                return 1;
        }
    }
    return 0;
}


void jeu::fall_mur_diagonale(){
    bool stop = false;
    for (int i=0; i<get_taille_plateau(); i++){
        for (int k=0; k<get_taille_plateau(); k++){
            if (k>0){  // mur ou glacage pas tout en bas du plateau

                if ((plateau[k][i]==-20 and plateau[k-1][i]==0) or (plateau[k][i]==-20 and plateau[k-1][i]==20) or (plateau[k][i]==-20 and plateau[k-1][i]==21)){ // mur, glacage niv 1 et 2
                    // va voir en haut a droite
                    if (i<8 and E[k-1][i+1].get()->getMyId()!=0 and plateau[k-1][i+1]!=-20){
                        E[k-1][i+1].get()->ElementMove(4);
                        wait_anim();
                        E[k-1][i+1].get()->setPosPlat({k, i});
                        echange({k-1, i+1}, {k,i});
                    }
                    // va voir en haut a gauche
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


// affuicher le plateau avec les entier ou le plateau des éléments de jeu 
// utile pour débugger
void jeu::afficher_plateau_de_jeu(){
    cout << "Plateau :" << endl;
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){

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
        }
        cout << endl;
    }
    cout << endl;


    cout << "E :" << endl;
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){

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
    // échange de deux élément de jeu sur le plateau et sur E
    swap(plateau[a.x][a.y], plateau[b.x][b.y]);
    swap(E[a.x][a.y], E[b.x][b.y]);
}


bool jeu::coup_possible(Point a, Point b){
    // vérifie si un coup est possible sur un plateau de test pour ne pas modifié le plateau original
    vector<vector<int >> test_plateau = get_plateau();
    swap(test_plateau[a.x][a.y], test_plateau[b.x][b.y]);
    swap(E[a.x][a.y], E[b.x][b.y]);
    test_plateau = check_3bonbons(test_plateau);
    for (auto &l: test_plateau){
        for (auto &i: l){
            if (i==-20){  // une combinaison a été trouvée -> coup possible
                swap(E[a.x][a.y], E[b.x][b.y]);
                return true;
            }
        }
    }
    swap(E[a.x][a.y], E[b.x][b.y]);
    return false;
}

// attendre que les animations de tout les éléments de jeu de E soient terminées
// Crédit : Deroubaix Emile
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
    // vérifie si un coups est possible sur le plateau de jeu
    //ligne 
    for (int i=0; i<taille_plateau-1; i++){
        for (int j=0; j<taille_plateau; j++){
            // on ne peut pas swap les murs et les glacages 
            if (E[i][j].get()->getMyId() != 0 and E[i][j].get()->getMyId() != 20 and E[i][j].get()->getMyId() != 21
            and E[i+1][j].get()->getMyId() != 0 and E[i+1][j].get()->getMyId() != 20 and E[i+1][j].get()->getMyId() != 21)
                if (coup_possible({i,j},{i+1, j}))
                    return true;
        }
    }
    //colonne
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-1; j++){
            // on ne peut pas swap les murs et les glacages 
            if (E[i][j].get()->getMyId() != 0 and E[i][j].get()->getMyId() != 20 and E[i][j].get()->getMyId() != 21
            and E[i][j+1].get()->getMyId() != 0 and E[i][j+1].get()->getMyId() != 20 and E[i][j+1].get()->getMyId() != 21)
                if (coup_possible({i,j},{i, j+1}))
                    return true;
        }
    }

    return false;
}


void jeu::melanger(){
    // pas de coups possible, on remplace tout les bonbons normaux pas d'autres bonbons normaux aléatoirement
    for (int i =0; i<taille_plateau; i++){
        for (int j =0; j<taille_plateau; j++){
            if (E[i][j].get()->getMyId()>0 and E[i][j].get()->getMyId()<7){
                Bonbon b{{i,j}, Colors[rand()%6], 35, 35};
                E[i][j] = make_shared<Bonbon>(b);
            }
        }
    }
    init_plateau(E);    // mise a jour du plateau d'entiers
    search_combinaison();   // il peut y avoir des combinaisons dues a la génération aléatoire
}