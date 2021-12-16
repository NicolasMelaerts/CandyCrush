#include "ElementDeJeu.hpp"

ElementDeJeu::ElementDeJeu(Point posPlat, Fl_Color couleur):posPlat{posPlat}, couleur{couleur}{}

Bonbon::Bonbon(Point posPlat, Fl_Color couleur, int w, int h):ElementDeJeu{posPlat, couleur}, r{{50*posPlat.y+48, 50*posPlat.x+70},w,h,couleur, couleur},animation{nullptr}{}

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
    animation = new Animation(this, static_cast<Animation::AnimationType>(0));
  }
}


BonbonSpecialRond::BonbonSpecialRond(Point posPlat, Fl_Color couleur, int r):ElementDeJeu{posPlat, couleur}, c{{50*posPlat.y+48, 50*posPlat.x+70}, r, couleur, couleur},animation{nullptr}{}

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
      if (c.getFillColor() == 88 or c.getFillColor() == 216 or c.getFillColor() == 248){
        c.setFrameColor(FL_WHITE);
      } else{
        c.setFrameColor(FL_BLACK);
      }
    }
    else{
      c.setFrameColor(c.getFillColor());
    }
}

Point BonbonSpecialRond::getPosPlatifcontain(Point coord){
  if (c.contains(coord)){
    return getposPlat();
  }
  return {-1, -1};
}

void BonbonSpecialRond::DoExplosion(){}


Mur::Mur(Point posPlat, int w, int h):ElementDeJeu{posPlat, FL_BLACK}, r{{50*posPlat.y+48, 50*posPlat.x+70}, w, h, FL_BLACK, FL_BLACK}{}

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


void Animation::draw() {
  ++time;
  Translation t3{currentBonbonFall()};
  Rotation r{b->getPoint(), currentExplosion()};
  b->drawWithoutAnimate();
}

Point Animation::currentBonbonFall() {
  if (animationType==Bonbon_fall)
    return {0, static_cast<int>(1*descente*sin(3.1415*time/animationTime/6))};
  else
    return {0, 0};
}

double Animation::currentExplosion() {
  if (animationType==explosion)
    return time*360.0/animationTime;
  else
    return 0;
}

bool Animation::isComplete() {
  return time>60;
}