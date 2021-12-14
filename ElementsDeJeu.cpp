#include "ElementsDeJeu.hpp"

Bonbon::Bonbon(Point center, int w, int h, Fl_Color BonbonColor, Point PosPlateau):
r{center,w,h,BonbonColor, BonbonColor}, animation{nullptr} {this->BonbonColor=BonbonColor; this->PosPlateau=PosPlateau;}


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

bool Bonbon::isAnimate(){
  return animation!=nullptr;
}


void Bonbon::drawWithoutAnimate(){
  r.draw();
}

void Bonbon::mouseClick(Point mouseLoc){
}

void Bonbon::exploseBonbon(){
  if (!animation) {
    animation = new Animation(this, static_cast<Animation::AnimationType>(0)); //random()%3
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