#ifndef __TEXT_H__
#define __TEXT_H__
#include "Shapes.hpp"

/*--------------------------------------------------

Text class.

Use to display text on the screen. For example:
Text("Hello!", {250, 250}).draw();

--------------------------------------------------*/

class Text {
  Point center;
  string s;
  int fontSize;
  Fl_Color color;
 public:
  //Constructor
  Text(string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK):
    s{s}, center{center}, fontSize{fontSize}, color{color} {}

  //Draw
  void draw();

  //Setters and getters
  string getString() {
    return s;
  }
  void setString(const string &newString) {
    s = newString;
  }
  int getFontSize() {
    return fontSize;
  }
  void setFontSize(int newFontSize) {
    fontSize = newFontSize;
  }
  Point getCenter() {
    return center;
  }
  void setCenter(Point newCenter) {
    center = newCenter;
  }
};

/*--------------------------------------------------

TextRectangle class.


--------------------------------------------------*/


class TextRectangle: public Text, public Rectangle {
 public:
  TextRectangle(Point center, int w, int h, string text, int fontSize = 10)
      : Text{text, center, fontSize}, Rectangle{center, w, h} {}
  void draw(){
    Rectangle::draw();
    Text::draw();
  }
  void setNiveau(){
    int niv = stoi(Text::getString());
    if (niv<5){
      Text::setString(to_string(niv+1));
    }
    else {
      Text::setString(to_string(1));
    }
  }

};
#endif



