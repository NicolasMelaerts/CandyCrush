#include "ElementDeJeu.hpp"

ElementDeJeu::ElementDeJeu(Point posPlat, Fl_Color couleur):posPlat{posPlat}, couleur{couleur}, animation{nullptr}{}

/*--------------------------------------------------

Bonbon class.

--------------------------------------------------*/


Bonbon::Bonbon(Point posPlat, Fl_Color couleur, int w, int h):ElementDeJeu{posPlat, couleur}, r{{50*posPlat.y+48, 50*posPlat.x+70},w,h,couleur, couleur}{}

int Bonbon::getMyId(){
  int c = r.getFillColor();
  if (c==FL_RED){return 1;}
  if (c==FL_BLUE){return 2;}
  if (c==FL_YELLOW){return 3;}
  if (c==FL_GREEN){return 4;}
  if (c==FL_MAGENTA){return 5;}
  else {return 6;} // (c==fl_rgb_color(251, 139, 35))
};

Fl_Color Bonbon::getcouleur(){
  return r.getFillColor();
}

void Bonbon::draw(){
  if (animation && animation->isComplete()){
    delete animation;
    animation = nullptr;
  }
  if (animation)
    animation->draw();
  else
    drawWithoutAnimate();
}

void Bonbon::drawWithoutAnimate(){
    r.setPoint({50*getposPlat().y+48, 50*getposPlat().x+70});
    r.draw();
}

void Bonbon::mouseClick(Point mouseLoc){
    if (r.contains(mouseLoc)){
        cout << "Je suis un bonbon" << endl;
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

Point Bonbon::getPosPlatifcontain(Point coord){
  if (r.contains(coord)){
    return getposPlat();
  }
  return {-1, -1};
}

void Bonbon::DoExplosion(){
  if (!animation){
    animation = new Animation(this, static_cast<Animation::AnimationType>(0), 0);
  }
}

void Bonbon::ElementMove(int sens){
  if (!animation){
    animation = new Animation(this, static_cast<Animation::AnimationType>(1), sens);
  }
}

bool Bonbon::animation_is_complete(){
  return animation;
}


/*--------------------------------------------------

BonbonSpecialRond class.

--------------------------------------------------*/

BonbonSpecialRond::BonbonSpecialRond(Point posPlat, Fl_Color couleur, int r):ElementDeJeu{posPlat, couleur}, c{{50*posPlat.y+48, 50*posPlat.x+70}, r, couleur, couleur}{}

int BonbonSpecialRond::getMyId(){
  int couleur = c.getFillColor();
  if (couleur==FL_RED){return -13;}
  if (couleur==FL_BLUE){return -14;}
  if (couleur==FL_YELLOW){return -15;}
  if (couleur==FL_GREEN){return -16;}
  if (couleur==FL_MAGENTA){return -17;}
  else {return -18;} //(couleur==fl_rgb_color(251, 139, 35))
};

Fl_Color BonbonSpecialRond::getcouleur(){
  return c.getFillColor();
}

void BonbonSpecialRond::draw(){
  if (animation && animation->isComplete()){
    delete animation;
    animation = nullptr;
  }
  if (animation)
    animation->draw();
  else
    drawWithoutAnimate();
}

void BonbonSpecialRond::drawWithoutAnimate(){
    c.setCenter({50*getposPlat().y+48, 50*getposPlat().x+70});
    c.draw();
}

void BonbonSpecialRond::mouseClick(Point mouseLoc){
    if (c.contains(mouseLoc)){
        cout << "Je suis un bonbon spécial rond" << endl;
    }
}

void BonbonSpecialRond::mouseMove(Point mouseLoc){
    if (c.contains(mouseLoc)){
      if (c.getFillColor() == 88 or c.getFillColor() == 216 or c.getFillColor() == 248 or c.getFillColor()==FL_BLACK){
        c.setFrameColor(FL_WHITE);
      } else{
        c.setFrameColor(FL_BLACK);
      }
    }
    else{
      c.setFrameColor(c.getFillColor());
    }
}

void BonbonSpecialRond::ElementMove(int sens){
  if (!animation){
    animation = new Animation(this, static_cast<Animation::AnimationType>(1), sens);
  }
}

Point BonbonSpecialRond::getPosPlatifcontain(Point coord){
  if (c.contains(coord)){
    return getposPlat();
  }
  return {-1, -1};
}

void BonbonSpecialRond::DoExplosion(){}

bool BonbonSpecialRond::animation_is_complete(){
  return animation;
}


/*--------------------------------------------------

Mur class.

--------------------------------------------------*/


Mur::Mur(Point posPlat, int w, int h):ElementDeJeu{posPlat, FL_BLACK}, r{{50*posPlat.y+48, 50*posPlat.x+70}, w, h, FL_BLACK, FL_BLACK}{}

int Mur::getMyId(){
    return 0;
};

Fl_Color Mur::getcouleur(){
  return r.getFillColor();
}

void Mur::draw(){
    r.draw();
}


void Mur::mouseClick(Point mousLoc){
}

void Mur::mouseMove(Point mouseLoc){
}


Point Mur::getPosPlatifcontain(Point coord){
  return {-1, -1};
}

void Mur::DoExplosion(){}

bool Mur::animation_is_complete(){
  return EXIT_SUCCESS;
}


/*--------------------------------------------------

Glacage class. Heritage ElementDeJeu

--------------------------------------------------*/

Glacage::Glacage(Point posPlat, int w, int h):ElementDeJeu{posPlat, FL_WHITE}, r{{50*posPlat.y+48, 50*posPlat.x+70}, w, h, FL_WHITE, FL_WHITE}, vie{2}{}

void Glacage::draw(){
    r.setPoint({50*getposPlat().y+48, 50*getposPlat().x+70});
    r.draw();
}

int Glacage::getMyId(){
  if (getVie()==2)
    return 20;
  else
    return 21;
}

Fl_Color Glacage::getcouleur(){
  return r.getFillColor();
}

void Glacage::DoExplosion(){
  if (getVie()==2){
    r.setFillColor(fl_rgb_color(96,96,96));
    r.setFrameColor(fl_rgb_color(96,96,96));
  }
  perdVie();
}

/*--------------------------------------------------

Ingredient class. Heritage ElementDeJeu

--------------------------------------------------*/


void Ingredient::draw(){
  if (animation && animation->isComplete()){
    delete animation;
    animation = nullptr;
  }
  if (animation)
    animation->draw();
  else
    drawWithoutAnimate();
}

void Ingredient::drawWithoutAnimate(){
    r.setPoint({50*getposPlat().y+48, 50*getposPlat().x+70});
    r.setCenter({50*getposPlat().y+48, 50*getposPlat().x+70});
    r.draw();
}

void Ingredient::mouseClick(Point mouseLoc){
    if (r.contains(mouseLoc)){
        cout << "Je suis un ingrédient" << endl;
    }
}

void Ingredient::mouseMove(Point mouseLoc){
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

Point Ingredient::getPosPlatifcontain(Point coord){
  if (r.contains(coord)){
    return getposPlat();
  }
  return {-1, -1};
}


void Ingredient::ElementMove(int sens){
  if (!animation){
    animation = new Animation(this, static_cast<Animation::AnimationType>(1), sens);
  }
}

bool Ingredient::animation_is_complete(){
  return animation;
}