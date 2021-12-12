#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include <array>

#include "ElementsDeJeu.hpp"


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

class Animation{
public:
    enum AnimationType {explosion, Bonbon_fall};
private:
    const int animationTime = 60;
    const int descente = 100;
    Bonbon *b;
    AnimationType animationType;
    int time{0};
    Point currentBonbonFall();
    double currentExplosion();
public:
    Animation(Bonbon *BonbonToAnimate, AnimationType animationType);

};

