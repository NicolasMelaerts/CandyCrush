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

#include "jeu.hpp"

using namespace std;

struct Point{
    int x,y;
};

class Rectangle {
  Point center;
  int w, h;
  Fl_Color fillColor, frameColor;
 public:
  // constructeur 
  Rectangle(Point center, int w, int h, Fl_Color frameColor = FL_BLACK, Fl_Color fillColor = FL_WHITE);

  // getteur / setteur
  void setFillColor(Fl_Color newFillColor) {
    fillColor = newFillColor;
  }

  Fl_Color getFillColor(){
    return fillColor;
  }

  void setFrameColor(Fl_Color newFrameColor) {
    frameColor = newFrameColor;
  }

  Fl_Color getFrameColor(){
    return frameColor;
  }

  void setWidth(int neww) {
    w = neww;
  }
  void setHeight(int newh) {
    h = newh;
  }
  int getWidth() {
    return w;
  }
  int getHeight() {
    return h;
  }

  Point getCenter() {
    return center;
  }
  void setPoint(Point newC){
    center = newC;
  }
  Point getPoint(){
    return center;
  }

  // méthodes
  bool contains(Point p);
  void draw();
};

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


class Canvas{
    vector< vector<Bonbon> > bonbons;
    vector<Fl_Color > Colors{FL_BLUE, FL_GREEN, FL_RED, FL_MAGENTA,FL_YELLOW, fl_rgb_color(251, 139, 35)};
    void initialize();
    jeu j;
public:
    //constructeur
    Canvas(){
        initialize();
    };

    // méthodes
    void draw();
    void mouseMove(Point mouseLoc);
    void moveBonbon(Point p, int keyCode);
    void maj_canvas();
    void fall();
    void afficherCanvas();
};


// Pour que murs et bonbons hérite de cette classe et pouvoir 
// stocker des éléments de même type dans le vecteur plateau
class ElementDeJeu{};
