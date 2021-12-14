#include "PlateauDeJeu.hpp"
#include <unistd.h>

void Canvas::initialize(){
  j.afficher_plateau_de_jeu();
  bonbons.clear();
  for (int x=0; x<j.get_taille_plateau();x++){
    bonbons.push_back({});
    for (int y=0; y<j.get_taille_plateau(); y++) {
      bonbons[x].push_back({{50*y+48, 50*x+70}, 40, 40, Colors[j.getelemplateau(x,y)], {x,y}});
    }
  }
}

void Canvas::draw(){
  for (auto &v: bonbons)
    for (auto &c : v){
      c.draw();
    }
}

void Canvas::mouseMove(Point mouseLoc) {
  for (auto &v: bonbons)
    for (auto &c: v)
      c.mouseMove(mouseLoc);
}

void Canvas::attente_fin_anim(){
  bool anim_en_cours=true;
  while(anim_en_cours){
    anim_en_cours = false;
    for (int i=0, j = 0; i<9; j++){
        cout << "i = " << i << "j = " << j << "  " << endl;
        if (bonbons[i][j].isAnimate()){
          cout << "(" << bonbons[i][j].getPosPlat().x << ", " << bonbons[i][j].getPosPlat().y << ")" << endl;
          anim_en_cours = true;
          break;
        }
        if (j==8){
          i++;
          j=0;
        }
    }
    if (anim_en_cours){
      cout << "Wait";
      Fl::wait();
    }
  }
}

void Canvas::moveBonbon(Point p, int keyCode) {
  for (auto &v: bonbons){
    for (auto &c: v){
      Point posplat{c.getPosPlatifContain(p)};
      Point decalage{0,0};
      if (posplat.x != -1){
        if (keyCode == 65362){decalage.x = -1;} //up
        if (keyCode == 65361){decalage.y = -1;} //left
        if (keyCode == 65363){decalage.y = 1;} // right
        if (keyCode == 65364){decalage.x = 1;} // down

        if ((posplat.x>0 && decalage.x == -1) || (posplat.x<8 && decalage.x == 1) || (posplat.y>0 && decalage.y == -1) || (posplat.y < 8 && decalage.y == 1)){
          if (j.coup_possible({posplat.x,posplat.y}, {posplat.x+decalage.x,posplat.y+decalage.y})){
            Point psave{bonbons[posplat.x][posplat.y].getPoint()};
            bonbons[posplat.x][posplat.y].setPoint(bonbons[posplat.x+decalage.x][posplat.y+decalage.y].getPoint());
            bonbons[posplat.x+decalage.x][posplat.y+decalage.y].setPoint(psave);
            bonbons[posplat.x][posplat.y].setPosPlat({posplat.x+decalage.x, posplat.y+decalage.y});
            bonbons[posplat.x+decalage.x][posplat.y+decalage.y].setPosPlat({posplat.x, posplat.y});
            swap(bonbons[posplat.x][posplat.y], bonbons[posplat.x+decalage.x][posplat.y+decalage.y]);

            j.echange({posplat.x,posplat.y}, {posplat.x+decalage.x,posplat.y+decalage.y});

            maj_canvas();
          } else {
            cout << "COUP IMPOSSIBLE NE FORME PAS UNE COMBINAISON" << endl;
          }
        }
      }
    }
  }
}

void Canvas::mouseClick(Point mouseLoc){
  for (auto &v: bonbons)
    for (auto &c: v)
      c.mouseClick(mouseLoc);
}

void Canvas::maj_canvas(){
    vector<vector<int >> ancien_plateau;
    while (ancien_plateau != j.get_plateau()){
        ancien_plateau = j.get_plateau();
        j.set_plateau(j.check_rows(j.get_plateau()));
        j.set_plateau(j.check_lines(j.get_plateau()));
        for (int i = 0; i<9;i++){
          for (int j = 0; j<9;j++){
            if (ancien_plateau[i][j]==-1){
              bonbons[i][j].exploseBonbon();
            }
          }
        }
        fall();
    }

}

void Canvas::fall(){
  vector<vector<int> > plateau = j.get_plateau();
  j.fall();

  int to_fall=0;
  cout << "FALLLLLLLL" << endl;

  for (int i=0; i<j.get_taille_plateau(); i++){
    for (int k=0; k<9; k++){
      if (plateau[k][i] != -1){
        to_fall++;
      } else{
        for (int l=0; l<to_fall; l++){
          afficherCanvas();
          bonbons[k-l][i] = bonbons[k-l-1][i];
          afficherCanvas();
          bonbons[k-l][i].setPosPlat({k-l,i});
          afficherCanvas();
          bonbons[k-l][i].setPoint({50*i+48, 50*(k-l)+70});
          
        }
      }
      
    }
    cout << to_fall << endl;
    for (int l=0; l<(j.get_taille_plateau()-to_fall); l++){
      bonbons[l][i] = {{50*i+48, 50*l+70}, 40, 40, Colors[j.getelemplateau(l,i)], {l,i}};
    }
    to_fall = 0;
  }
  afficherCanvas();
  j.afficher_plateau_de_jeu();

}

void Canvas::afficherCanvas(){
  for (int i=0; i<9; i++){
    for (int j=0; j<9; j++){
      cout << "[" << bonbons[i][j].getPosPlat().x << ", " << bonbons[i][j].getPosPlat().y << "]";
      if (bonbons[i][j].getBonbonColor() == 88){cout << "R ,";}
      if (bonbons[i][j].getBonbonColor() == 63){cout << "G ,";}
      if (bonbons[i][j].getBonbonColor() == 95){cout << "Y ,";}
      if (bonbons[i][j].getBonbonColor() == 216){cout << "B ,";}
      if (bonbons[i][j].getBonbonColor() == 248){cout << "M ,";}
      if (bonbons[i][j].getBonbonColor() == fl_rgb_color(251, 139, 35)){cout << "O ,";}
    }
    cout << endl;
  }
  cout << endl;
}