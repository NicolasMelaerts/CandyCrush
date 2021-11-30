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

struct Point {
    int x,y;
};

class Rectangle {
  Point center;
  int w, h;
  Fl_Color fillColor, frameColor;
 public:
  Rectangle(Point center, int w, int h,
            Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE);
  void draw();
  void setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor() {
    return fillColor;
  }
  void setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() {
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
  bool contains(Point p);
  Point getCenter() {
    return center;
  }
  void setPoint(Point newC){
    center = newC;
  }
  Point getPoint(){
    return center;
  }
};

class Bonbon{
    Rectangle r;
    Fl_Color FrameColor= r.getFrameColor();
    Fl_Color FillColor= r.getFillColor();
    bool is_Selectionned = false;
public:
    Bonbon(Point center, int w, int h, Fl_Color FrameColor, Fl_Color FillColor);
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void moveBonbon(Point p, int keyCode);
};

class Mur{
  Rectangle r;
public:
  Mur(Point center, int w, int h);
};


class Canvas{
    vector< vector<Bonbon> > bonbons;
    vector<Fl_Color > Colors{FL_BLUE, FL_GREEN, FL_RED, FL_MAGENTA,FL_YELLOW, fl_rgb_color(251, 139, 35)};
    void initialize();
    jeu j;
public:
    Canvas(){
        initialize();
    };
    void draw();
    void mouseMove(Point mouseLoc);
    void moveBonbon(Point p, int keyCode);
};


// Pour que murs et bonbons hérite de cette classe et pouvoir 
// stocker des éléments de même type dans le vecteur plateau
class ElementDeJeu{};
