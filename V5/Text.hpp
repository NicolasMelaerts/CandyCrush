#ifndef __TEXT_H__
#define __TEXT_H__
#include "Shapes.hpp"

/*--------------------------------------------------

Class Text reprise des TPs

--------------------------------------------------*/

class Text {
  Point center;
  string s;
  int fontSize;
  Fl_Color color;
 public:
  //Constructor
  Text(string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK);

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
  TextRectangle(Point center, int w, int h, string text, int fontSize = 10);

  void draw();
  void setNiveau();

};

#endif
