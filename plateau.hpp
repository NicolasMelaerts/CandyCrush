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
  Rectangle(Point center, int w, int h, Fl_Color frameColor = FL_BLACK, Fl_Color fillColor = FL_WHITE);
  void draw();

  void setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor();

  void setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor();

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

  bool contains(Point p);
};

class Bonbon{
    Rectangle r;
    Fl_Color BonbonColor;
    Point PosPlateau;
public:
    Bonbon(Point center, int w, int h, Fl_Color BonbonColor, Point PosPlateau);
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void moveBonbon(Point p, int keyCode, jeu j, vector< vector<Bonbon> > bonbons);

    Fl_Color getBonbonColor(){
      return BonbonColor;
    }
    void setPoint(Point newP){
      r.setPoint(newP);
    }

    Point getPoint(){
      return r.getPoint();
    }

    Point getPosPlatContain(Point mouseLoc){
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
    void afficherCanvas(){
      for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
          cout << "[" << bonbons[i][j].getPosPlat().x << ", " << bonbons[i][j].getPosPlat().y << "]";
            if (bonbons[i][j].getBonbonColor() == 88){cout << "R ,";}
            if (bonbons[i][j].getBonbonColor() == 63){cout << "G ,";}
            if (bonbons[i][j].getBonbonColor() == 95){cout << "Y ,";}
            if (bonbons[i][j].getBonbonColor() == 216){cout << "B ,";}
            if (bonbons[i][j].getBonbonColor() == 248){cout << "M ,";}
            if (bonbons[i][j].getBonbonColor() == 223){cout << "C ,";}
            if (bonbons[i][j].getBonbonColor() == fl_rgb_color(251, 139, 35)){cout << "O ,";}
        }
        cout << endl;
    }
    cout << endl;
    }

    void maj_canvas();
    void fall();
};


// Pour que murs et bonbons hérite de cette classe et pouvoir 
// stocker des éléments de même type dans le vecteur plateau
class ElementDeJeu{};
