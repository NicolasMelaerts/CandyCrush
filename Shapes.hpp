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


// class cercle pour bonbons spéciaux