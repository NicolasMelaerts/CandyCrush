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

#include "plateau.hpp"

using namespace std;

Rectangle::Rectangle(Point center, int w, int h, Fl_Color frameColor, Fl_Color fillColor):
  center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor} {}

void Rectangle::draw() {
  fl_draw_box(FL_FLAT_BOX, center.x-w/2, center.y-h/2, w, h, fillColor);
  fl_draw_box(FL_BORDER_FRAME, center.x-w/2, center.y-h/2, w, h, frameColor);
}

void Rectangle::setFillColor(Fl_Color newFillColor) {
  fillColor = newFillColor;
}

void Rectangle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}

bool Rectangle::contains(Point p) {
  return p.x>=center.x-w/2 &&
         p.x<center.x+w/2 &&
         p.y>=center.y-h/2 &&
         p.y<center.y+h/2;
}


Bonbon::Bonbon(Point center, int w, int h):
r(center,w,h,FL_BLACK, FL_WHITE){}

void Bonbon::draw(){
  r.draw();
}

void Bonbon::mouseClick(Point mouseLoc){
  if (r.contains(mouseLoc)){
    r.setFillColor(FL_DARK_RED);
  }
}

void Bonbon::mouseMove(Point mouseLoc){
    if (r.contains(mouseLoc)){
    r.setFrameColor(FL_YELLOW);
  }
}


void Canvas::initialize(){
  for (int x=0; x<9;x++){
    bonbons.push_back({});
    for (int y=0; y<9; y++) bonbons[x].push_back({{50*x+25, 50*y+25}, 40, 40});
  }
}

void Canvas::draw(){
  for (auto &v: bonbons)
    for (auto &c : v){
      c.draw();
    }
}

void Canvas::mouseMove(Point mouseLoc) {
  for (auto &v: bonbons)
    for (auto &c: v)
      c.mouseMove(mouseLoc);
}