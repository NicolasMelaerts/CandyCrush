#include "PlateauDeJeu.hpp"

void Canvas::initialize(){
    E.clear();
    for (int x = 0; x<9; x++){
        E.push_back({});
        for (int y = 0; y<9; y++){
            int ajout = j.getelemplateau(x,y);
            if (ajout==0){
                Mur m{{x,y}, 40, 40};
                E[x].push_back(make_shared<Mur>(m));
            }
            if (ajout >= 1 && ajout <= 6){
                Bonbon b{{x,y}, Colors[ajout-1], 35, 35};
                E[x].push_back(make_shared<Bonbon>(b));
            }
            if (ajout >= -18 && ajout <= -13){
                BonbonSpecialRond bs{{x,y}, Colors[abs(ajout+1)%6], 20};
                E[x].push_back(make_shared<BonbonSpecialRond>(bs));
            }
        }
    }
}


void Canvas::draw(){
    for (auto &l:E)
        for (auto &e:l)
            e.get()->draw();
}

void Canvas::mouseMove(Point mouseLoc){
    for (auto &l:E)
        for (auto &e:l)
            e.get()->mouseMove(mouseLoc);
}

void Canvas::drag(Point mouseLoc){
    ForDrag.push_back(mouseLoc);
}


void Canvas::swapElementDeJeu(){
    Point p1, p2;
    Point idx1, idx2;
    bool stop{false};

    for (int i =0; i<9; i++){
        for (int j =0; j<9; j++){
            p1 = E[i][j].get()->getPosPlatifcontain(ForDrag[0]);
            idx1 = {i,j};
            if (p1.x != -1){
                stop = true;
                break;
            }
        }
        if (stop){
            break;
        }
    }

    stop = false;
    for (int i =0; i<9; i++){
        for (int j =0; j<9; j++){
            p2 = E[i][j].get()->getPosPlatifcontain(ForDrag[ForDrag.size()-1]);
            idx2 = {i,j};
            if (p2.x != -1 and p2.y!=-1){
                stop = true;
                break;
            }
        }
        if (stop){
            break;
        }
    }

    cout << idx1.x << ", "<< idx1.y << endl;
    cout << idx2.x << ", "<< idx2.y << endl;
    cout << p1.x << ", "<< p1.y << endl;
    cout << p2.x << ", "<< p2.y << endl;

    if (p1.x != -1 && p2.x != -1){
        if ((p1.x == p2.x and p1.y == p2.y+1) || (p1.x == p2.x and p1.y == p2.y-1) || (p1.x == p2.x+1 and p1.y == p2.y) || (p1.x == p2.x-1 and p1.y == p2.y)){
            if (j.coup_possible({p1.x, p1.y}, {p2.x, p2.y})){
                E[idx1.x][idx1.y].get()->setPosPlat(p2);
                E[idx2.x][idx2.y].get()->setPosPlat(p1);

                j.echange({idx1.x,idx1.y},{idx2.x,idx2.y});
                swap(E[idx1.x][idx1.y],E[idx2.x][idx2.y]);

                j.set_plateau(j.check_rows(j.get_plateau()));
                j.set_plateau(j.check_lines(j.get_plateau()));

                j.afficher_plateau_de_jeu();

                for (int i = 0; i<9;i++){
                    for (int k = 0; k<9;k++){
                        if (j.getelemplateau(i,k)==-20){
                            E[i][k].get()->DoExplosion();
                        }   
                    }
                }
                wait_anim();

                maj_canvas();
            }
            else cout << "coup impossible" << endl;
        }
    }

    ForDrag.clear();
}

void Canvas::mouseClick(Point mouseLoc){
    //for (auto &e: E)
        //e.get()->DoExplosion();
}


void Canvas::maj_canvas(){
    vector<vector<int >> ancien_plateau;

    while (ancien_plateau != j.get_plateau()){
        ancien_plateau = j.get_plateau();
        j.set_plateau(j.check_rows(j.get_plateau()));
        j.set_plateau(j.check_lines(j.get_plateau()));

        j.search_combinaison();
        initialize();
        //fall();
}
}


void Canvas::fall(){
  vector<vector<int> > plateau = j.get_plateau();
  j.afficher_plateau_de_jeu();
  j.fall();
  j.afficher_plateau_de_jeu();

  int to_fall=0;
  cout << "FALLLLLLLL" << endl;

  for (int i=0; i<j.get_taille_plateau(); i++){
    for (int k=0; k<9; k++){
      if (plateau[k][i] != -20){
        to_fall++;
      } else{
        for (int l=0; l<to_fall; l++){
          E[k-l][i] = E[k-l-1][i];
        }
      }
      
    }
    cout << to_fall << endl;
    for (int l=0; l<(j.get_taille_plateau()-to_fall); l++){
        Bonbon b{{l,i}, Colors[j.getelemplateau(l,i)-1], 35, 35};
        E[l].push_back(make_shared<Bonbon>(b));
    }
    to_fall = 0;
  }
}

void Canvas::wait_anim(){
    vector <int> lol;
    bool anim_en_cours=true;
    while (anim_en_cours){
        anim_en_cours=false;
        if (lol.size()<100){
            lol.push_back(1000);
            anim_en_cours = true;
        }
        if (anim_en_cours)
            Fl::wait();
        }
}