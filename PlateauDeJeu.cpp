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

                if (p1.x == p2.x && p1.y == p2.y+1){
                    E[idx1.x][idx1.y].get()->ElementMove(3);
                    E[idx2.x][idx2.y].get()->ElementMove(2);
                }

                if (p1.x == p2.x && p1.y == p2.y+1){
                    E[idx1.x][idx1.y].get()->ElementMove(2);
                    E[idx2.x][idx2.y].get()->ElementMove(3);
                }
                if (p1.x == p2.x+1 && p1.y == p2.y){
                    E[idx1.x][idx1.y].get()->ElementMove(1);
                    E[idx2.x][idx2.y].get()->ElementMove(0);
                }
                if (p1.x == p2.x-1 && p1.y == p2.y){
                    E[idx1.x][idx1.y].get()->ElementMove(0);
                    E[idx2.x][idx2.y].get()->ElementMove(1);
                }
                
                wait_anim();

                E[idx1.x][idx1.y].get()->setPosPlat(p2);
                E[idx2.x][idx2.y].get()->setPosPlat(p1);

                j.echange({idx1.x,idx1.y},{idx2.x,idx2.y});
                swap(E[idx1.x][idx1.y],E[idx2.x][idx2.y]);

                j.set_plateau(j.check_rows(j.get_plateau()));
                j.set_plateau(j.check_lines(j.get_plateau()));


                maj_canvas();

            }
            else cout << "coup impossible" << endl;
        }
    }

    ForDrag.clear();
}

void Canvas::mouseClick(Point mouseLoc){
}


void Canvas::maj_canvas(){
    vector<vector<int >> ancien_plateau;

    while (ancien_plateau != j.get_plateau()){
        cout << "MAJ_CANVAS" << endl;
        ancien_plateau = j.get_plateau();
        j.set_plateau(j.check_rows(j.get_plateau()));
        j.set_plateau(j.check_lines(j.get_plateau()));

        for (int i = 0; i<9;i++){
            for (int k = 0; k<9;k++){
                if (j.getelemplateau(i,k)==-20){
                    E[i][k].get()->DoExplosion();
                }   
            }
        }

        wait_anim();
        //j.search_combinaison();
        fall();
}
}


void Canvas::fall(){
  vector<vector<int> > plateau = j.get_plateau();
  j.afficher_plateau_de_jeu();
  j.fall();
  j.afficher_plateau_de_jeu();

  cout << "FALLLLLLLL" << endl;

  vector <Point> col;
  Point bonbonExplose;


  for (int i=0; i<j.get_taille_plateau(); i++){
      for (int k=0; k<j.get_taille_plateau(); k++){
          if (plateau[k][i] != -20 ){
              col.push_back({k,i});
          }
          if (plateau[k][i]==-20 && col.size()!=0){
              bonbonExplose = col[0];
              E[k][i].get()->setPosPlat({-1,-1});
              
              for (int l=col.size()-1; l>=0; l--){
                  plateau[col[l].x+1][col[l].y] = plateau[col[l].x][col[l].y];
                  E[col[l].x][col[l].y].get()->ElementMove(0);
                  wait_anim();
                  E[col[l].x][col[l].y].get()->setPosPlat({col[l].x+1, col[l].y});
                  E[col[l].x+1][col[l].y] =  E[col[l].x][col[l].y];
                  col[l]={col[l].x+1, col[l].y};
              }
              plateau[bonbonExplose.x][bonbonExplose.y] = -20;
              
          }
      }
      col.clear();
  }
    for (int i=0; i<j.get_taille_plateau(); i++){
      for (int k=0; k<j.get_taille_plateau(); k++){
          if (plateau[k][i]==-20){
            Bonbon b{{k,i}, Colors[j.getelemplateau(k,i)-1], 35,35};
            E[k][i] = make_shared<Bonbon>(b);
          }
      }
    }
}

void Canvas::wait_anim(){
    vector <int> lol;
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