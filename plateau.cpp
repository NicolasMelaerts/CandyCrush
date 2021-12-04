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

void Rectangle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
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
  //afficherCanvas();
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
      Point posplat{c.getPosPlat(p)};
      if (keyCode==65362 && posplat.x != -1){ //up
        if (posplat.x != 0){
          Point psave{bonbons[posplat.x][posplat.y].getPoint()};
          bonbons[posplat.x][posplat.y].setPoint(bonbons[posplat.x-1][posplat.y].getPoint());
          bonbons[posplat.x-1][posplat.y].setPoint(psave);
          bonbons[posplat.x][posplat.y].setPosPlat({posplat.x-1, posplat.y});
          bonbons[posplat.x-1][posplat.y].setPosPlat({posplat.x, posplat.y});
          swap(bonbons[posplat.x][posplat.y], bonbons[posplat.x-1][posplat.y]);

          j.echange({posplat.x,posplat.y}, {posplat.x-1,posplat.y});
          j.search_combinaison();
          initialize();
        }
      } 
      if (keyCode==65361 && posplat.x != -1){ //Left
        if (posplat.y != 0){
          Point psave{bonbons[posplat.x][posplat.y].getPoint()};
          bonbons[posplat.x][posplat.y].setPoint(bonbons[posplat.x][posplat.y-1].getPoint());
          bonbons[posplat.x][posplat.y-1].setPoint(psave);
          bonbons[posplat.x][posplat.y].setPosPlat({posplat.x, posplat.y-1});
          bonbons[posplat.x][posplat.y-1].setPosPlat({posplat.x, posplat.y});
          swap(bonbons[posplat.x][posplat.y], bonbons[posplat.x][posplat.y-1]);

          j.echange({posplat.x,posplat.y}, {posplat.x,posplat.y-1});
          j.search_combinaison();
          initialize();
        }
      }
      if (keyCode==65363 && posplat.x != -1){ //Right 
        if (posplat.y != 8){
          Point psave{bonbons[posplat.x][posplat.y].getPoint()};
          bonbons[posplat.x][posplat.y].setPoint(bonbons[posplat.x][posplat.y+1].getPoint());
          bonbons[posplat.x][posplat.y+1].setPoint(psave);
          bonbons[posplat.x][posplat.y].setPosPlat({posplat.x, posplat.y+1});
          bonbons[posplat.x][posplat.y+1].setPosPlat({posplat.x, posplat.y});
          swap(bonbons[posplat.x][posplat.y], bonbons[posplat.x][posplat.y+1]);
          
          j.echange({posplat.x,posplat.y}, {posplat.x,posplat.y+1});
          j.search_combinaison();
          initialize();
        }
      }
      if (keyCode==65364  && posplat.x != -1){ //Down
        if (posplat.x != 8){
          Point psave{bonbons[posplat.x][posplat.y].getPoint()};
          bonbons[posplat.x][posplat.y].setPoint(bonbons[posplat.x+1][posplat.y].getPoint());
          bonbons[posplat.x+1][posplat.y].setPoint(psave);
          bonbons[posplat.x][posplat.y].setPosPlat({posplat.x+1, posplat.y});
          bonbons[posplat.x+1][posplat.y].setPosPlat({posplat.x, posplat.y});
          swap(bonbons[posplat.x][posplat.y], bonbons[posplat.x+1][posplat.y]);

          j.echange({posplat.x,posplat.y}, {posplat.x+1,posplat.y});
          j.search_combinaison();
          initialize();
        }
      } 
    }
  } 
}



/*
          Point psave{bonbons[posplat.x][posplat.y].getPoint()};
          bonbons[posplat.x][posplat.y].setPoint(bonbons[posplat.x][posplat.y-1].getPoint());
          bonbons[posplat.x][posplat.y-1].setPoint(psave);
          bonbons[posplat.x][posplat.y].setPosPlat({posplat.x, posplat.y-1});
          bonbons[posplat.x][posplat.y-1].setPosPlat({posplat.x, posplat.y});
          swap(bonbons[posplat.x][posplat.y], bonbons[posplat.x][posplat.y-1]);
          j.echange({posplat.x,posplat.y}, {posplat.x,posplat.y-1});
*/