#include "plateau.hpp"


using namespace std;

Rectangle::Rectangle(Point center, int w, int h, Fl_Color frameColor, Fl_Color fillColor):
  center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor} {}

void Rectangle::draw() {
  fl_draw_box(FL_FLAT_BOX, center.x-w/2, center.y-h/2, w, h, fillColor);
  fl_draw_box(FL_BORDER_FRAME, center.x-w/2, center.y-h/2, w+1, h+1, frameColor);
}

void Rectangle::setFillColor(Fl_Color newFillColor) {
  fillColor = newFillColor;
}

Fl_Color Rectangle::getFillColor(){
  return fillColor;
}

void Rectangle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}

Fl_Color Rectangle::getFrameColor(){
  return frameColor;
}

bool Rectangle::contains(Point p) {
  return p.x>=center.x-w/2 &&
         p.x<center.x+w/2 &&
         p.y>=center.y-h/2 &&
         p.y<center.y+h/2;
}


Bonbon::Bonbon(Point center, int w, int h, Fl_Color BonbonColor, Point PosPlateau):
r{center,w,h,BonbonColor, BonbonColor}{this->BonbonColor=BonbonColor; this->PosPlateau=PosPlateau;}

void Bonbon::draw(){
  r.draw();
}

void Bonbon::mouseClick(Point mouseLoc){
}

void Bonbon::mouseMove(Point mouseLoc){
    if (r.contains(mouseLoc)){
      if (r.getFillColor() == 88 or r.getFillColor() == 216 or r.getFillColor() == 248){
        r.setFrameColor(FL_WHITE);
      } else{
        r.setFrameColor(FL_BLACK);
      }
    }
    else{
      r.setFrameColor(r.getFillColor());
    }

}


Mur::Mur(Point center, int w, int h):
r{center, w, h, FL_BLACK, FL_BLACK}{}


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

void Canvas::moveBonbon(Point p, int keyCode) {
  for (auto &v: bonbons){
    for (auto &c: v){
      Point posplat{c.getPosPlatContain(p)};
      Point decalage{0,0};
      if (posplat.x != -1){
        if (keyCode == 65362){decalage.x = -1;} //up
        if (keyCode == 65361){decalage.y = -1;} //left
        if (keyCode == 65363){decalage.y = 1;} // right
        if (keyCode == 65364){decalage.x = 1;} // down

        

        if ((posplat.x>0 && decalage.x == -1) || (posplat.x<8 && decalage.x == 1) || (posplat.y>0 && decalage.y == -1) || (posplat.y < 8 && decalage.y == 1)){
          //cout << "YESSSSS = " << j.coup_possible({posplat.x,posplat.y}, {posplat.x+decalage.x,posplat.y+decalage.y});
          Point psave{bonbons[posplat.x][posplat.y].getPoint()};
          bonbons[posplat.x][posplat.y].setPoint(bonbons[posplat.x+decalage.x][posplat.y+decalage.y].getPoint());
          bonbons[posplat.x+decalage.x][posplat.y+decalage.y].setPoint(psave);
          bonbons[posplat.x][posplat.y].setPosPlat({posplat.x+decalage.x, posplat.y+decalage.y});
          bonbons[posplat.x+decalage.x][posplat.y+decalage.y].setPosPlat({posplat.x, posplat.y});
          swap(bonbons[posplat.x][posplat.y], bonbons[posplat.x+decalage.x][posplat.y+decalage.y]);

          j.echange({posplat.x,posplat.y}, {posplat.x+decalage.x,posplat.y+decalage.y});

          maj_canvas();
        }
      }
    }
  }
}

void Canvas::maj_canvas(){
    vector<vector<int >> ancien_plateau;
    while (ancien_plateau != j.get_plateau()){
        ancien_plateau = j.get_plateau();
        j.check_rows();
        j.check_lines();
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
          cout << "TOUR DE BOUCLE" << endl;
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
