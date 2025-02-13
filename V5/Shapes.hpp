#ifndef __SHAPES_H__
#define __SHAPES_H__

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

struct DoublePoint{
    Point point1,point2;
};

/*--------------------------------------------------

Classe Rectangle reprise des TPs

--------------------------------------------------*/


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


/*--------------------------------------------------

Classe Circle reprise des TPs

--------------------------------------------------*/

class Circle {
  Point center;
  int r;
  Fl_Color fillColor, frameColor;
  const double pi=3.141592653589793238462643383279502884L;
 public:
  Circle(Point center, int r,
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
  bool contains(Point p);
  Point getCenter() {
    return center;
  }
  void setCenter(Point newCenter){
    center = newCenter;
  }
};

#endif