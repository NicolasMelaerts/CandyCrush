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


Bonbon::Bonbon(Point center, int w, int h, Fl_Color FrameColor, Fl_Color FillColor):
r{center,w,h,FillColor, FrameColor}{FrameColor=r.getFrameColor(); FillColor=r.getFillColor();}

void Bonbon::draw(){
  r.draw();
}

void Bonbon::mouseClick(Point mouseLoc){
  if (r.contains(mouseLoc)){
    r.setFillColor(FL_DARK_RED);
  }
}

void Bonbon::mouseMove(Point mouseLoc){
    if (r.contains(mouseLoc)){
      if (FrameColor == 88 or FrameColor == 216 or FrameColor == 248){
        r.setFrameColor(FL_WHITE);
      } else{
        r.setFrameColor(FL_BLACK);
      }
    }
    else{
      r.setFrameColor(FrameColor);
    }

}

void Bonbon::moveBonbon(Point p, int keyCode){
    if (r.contains(p)){
      if (keyCode==65362){r.setPoint({r.getPoint().x, r.getPoint().y-50});} //up
      if (keyCode==65361){r.setPoint({r.getPoint().x-50, r.getPoint().y});} //Left
      if (keyCode==65363){r.setPoint({r.getPoint().x+50, r.getPoint().y});} //Right
      if (keyCode==65364){r.setPoint({r.getPoint().x, r.getPoint().y+50});} //Down
  }
}

Mur::Mur(Point center, int w, int h):
r{center, w, h, FL_BLACK, FL_BLACK}{}


void Canvas::initialize(){
  for (int x=0; x<j.get_taille_plateau();x++){
    bonbons.push_back({});
    for (int y=0; y<j.get_taille_plateau(); y++) {
      bonbons[x].push_back({{50*x+48, 50*y+70}, 40, 40, Colors[j.getelemplateau(x,y)], Colors[j.getelemplateau(x,y)]});
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
  for (auto &v: bonbons)
    for (auto &c: v)
      c.moveBonbon(p, keyCode);
}
