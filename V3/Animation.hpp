#ifndef __ANIMATION_H__
#define  __ANIMATION_H__

#include "ElementDeJeu.hpp"
#include "Text.hpp"

class ElementDeJeu;

/*--------------------------------------------------

Translation et Rotation structure

--------------------------------------------------*/

struct Translation {
  Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() {
    fl_pop_matrix();
  }
};

struct Rotation {
  Rotation(Point center, double angle) {
    fl_push_matrix();
    fl_translate(center.x, center.y);
    fl_rotate(angle);
    fl_translate(-1*center.x, -1*center.y);
  }
  ~Rotation() {
    fl_pop_matrix();
  }
};


/*--------------------------------------------------

Animation class.

--------------------------------------------------*/

class Animation{
public:
    enum AnimationType {explosion, Bonbon_move};
private:
    const int animationTime = 60;
    const int descente = 100;
    int sens;
    ElementDeJeu *b;
    AnimationType animationType;
    int time{0};
    Point MoveElementDeJeu();
    double ExploseElementDeJeu();
public:
    Animation(ElementDeJeu *BonbonToAnimate, AnimationType animationType, int sens):b{BonbonToAnimate}, animationType{animationType}, sens{sens}{}
    void draw();
    bool isComplete();
};


#endif