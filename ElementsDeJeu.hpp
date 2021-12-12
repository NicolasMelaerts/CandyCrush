#include "Shapes.hpp"
#include "Jeu.hpp"


class Bonbon{
    Rectangle r;
    Fl_Color BonbonColor;
    Point PosPlateau;
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