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
            if (ajout >= -18 && ajout <= -13){
                BonbonSpecialRond bs{{i,j}, Colors[abs(ajout+1)%6], 20};
                E[i].push_back(make_shared<BonbonSpecialRond>(bs));
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

void jeu::ouvertureGlacage(int niv){
    plateau_glacage.clear();
    ifstream Glac("NiveauDeJeu/Glacage"+to_string(niv));
    if(Glac){
        string Case;
        int i= 0, j=0;
        while(Glac >> Case){
            if (j==9){
                i++;
                j=0;
                plateau_glacage.push_back({});
            }
            int k = stoi(Case);
            plateau_glacage[i].push_back(k);
            j++;
            
        }
        Glac.close();
    }
    else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}




bool jeu::again_fall(vector< vector<shared_ptr<ElementDeJeu>> > E){
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau; j++){
            if (E[i][j].get()->getEnlever() == 1)
                return 1;
        }
    }
    return 0;
}

vector<Point> jeu::setToExplose(){
    vector <Point> to_explose;
    for (int i = 0; i<9;i++){
        for (int k = 0; k<9;k++){
            if (getelemplateau(i,k)==-20){
                to_explose.push_back({i,k});
                c.augmente_score(niv);
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

vector<vector<int> > jeu::check_lines(vector<vector<int> > plat){
    cout << "check_lines" << endl;
    afficher_plateau_de_jeu();
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plat[i][j] == plat[i][j+1] && plat[i][j] == plat[i][j+2]&&plat[i][j+1] == plat[i][j+2]){ // si a = b et a = c alors b = c
                if (plat[i][j] != 0){ // MURs
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
    cout << "check rows"<< endl;
    for (int i=0; i<taille_plateau; i++){
        for (int j=0; j<taille_plateau-2; j++){
            if (plat[j][i] == plat[j+1][i] && plat[j][i] == plat[j+2][i]){
                if (plat[j][i]!=0){ //MURs
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


void jeu::search_combinaison(){
    vector<vector<int >> ancien_plateau;
    c.do_coup();

    while (ancien_plateau != get_plateau()){
        cout << "MAJ_CANVAS" << endl;
        ancien_plateau = get_plateau();
        set_plateau(check_rows(get_plateau()));
        set_plateau(check_lines(get_plateau()));
        afficher_plateau_de_jeu();
        DoExplose(setToExplose());
        fall();
}
}

void jeu::fall_plat(){
    vector<int> col;
    for (int i=0; i<taille_plateau; i++){
        for (int j=taille_plateau-1; j>=0; j--){
            if (plateau[j][i]!=-20){
                col.push_back(plateau[j][i]);
            }
        }
        while (col.size()!=taille_plateau){
            int new_bb;
            new_bb = rand()%nb_couleurs_bonbon+1;
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

void jeu::fall(){
  vector<vector<int> > plat = get_plateau();

  fall_plat();

  cout << "FALLLLLLLL" << endl;

  vector <Point> col;
  Point bonbonExplose;


  for (int i=0; i<get_taille_plateau(); i++){
      for (int k=0; k<get_taille_plateau(); k++){
          if (plat[k][i] != -20 ){
              col.push_back({k,i});
          }
          if (plat[k][i]==-20 && col.size()!=0){
              bonbonExplose = col[0];
              
              
              for (int l=col.size()-1; l>=0; l--){
                  plat[col[l].x+1][col[l].y] = plat[col[l].x][col[l].y];
                  E[col[l].x][col[l].y].get()->ElementMove(0);
                  wait_anim();
                  E[col[l].x][col[l].y].get()->setPosPlat({col[l].x+1, col[l].y});
                  E[col[l].x+1][col[l].y] =  E[col[l].x][col[l].y];
                  col[l]={col[l].x+1, col[l].y};
              }
              plat[bonbonExplose.x][bonbonExplose.y] = -20;
              
          }
      }
      col.clear();
  }
    for (int i=0; i<get_taille_plateau(); i++){
      for (int k=0; k<get_taille_plateau(); k++){
          if (plat[k][i]==-20){
            Bonbon b{{k,i}, Colors[getelemplateau(k,i)-1], 35,35};
            E[k][i] = make_shared<Bonbon>(b);
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