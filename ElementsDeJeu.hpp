#include "Shapes.hpp"
#include "Jeu.hpp"

class Animation;

class Bonbon{
    Rectangle r;
    Fl_Color BonbonColor;
    Point PosPlateau;
    Animation *animation;
public:
    // constructeur
    Bonbon(Point center, int w, int h, Fl_Color BonbonColor, Point PosPlateau);

    // getteur / setteur
    Fl_Color getBonbonColor(){
      return BonbonColor;
    }
    void setPoint(Point newP){
      r.setPoint(newP);
    }

    Point getPoint(){
      return r.getPoint();
    }

    Point getPosPlatifContain(Point mouseLoc){
      if (r.contains(mouseLoc)){
        return PosPlateau;
      }
      return {-1, -1};
    }

    Point getPosPlat(){
      return PosPlateau;
    }

    void setPosPlat(Point newP){
      PosPlateau = newP;
    }

    // méthodes
    void draw();
    void drawWithoutAnimate();
    void mouseClick(Point mouseLoc);
    void mouseMove(Point mouseLoc);
    void moveBonbon(Point p, int keyCode, jeu j, vector< vector<Bonbon> > bonbons);

};

class Mur{
  Rectangle r;
public:
  // constructeur
  Mur(Point center, int w, int h);
};

class ElementDeJeu{
};

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
    Animation(Bonbon *BonbonToAnimate, AnimationType animationType):b{BonbonToAnimate}, animationType{animationType}{}
    void draw();
    bool isComplete();
};
