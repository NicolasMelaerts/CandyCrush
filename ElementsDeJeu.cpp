#include "ElementsDeJeu.hpp"

Bonbon::Bonbon(Point center, int w, int h, Fl_Color BonbonColor, Point PosPlateau):
r{center,w,h,BonbonColor, BonbonColor}{this->BonbonColor=BonbonColor; this->PosPlateau=PosPlateau;}

void Bonbon::draw(){
  r.draw();
}

void Bonbon::mouseClick(Point mouseLoc){
  if (r.contains(mouseLoc)){

  }
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