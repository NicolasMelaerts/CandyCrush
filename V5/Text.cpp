#include "Text.hpp"


/*--------------------------------------------------

Class Text reprise des TPs

--------------------------------------------------*/

Text::Text(string s, Point center, int fontSize, Fl_Color color):
    s{s}, center{center}, fontSize{fontSize}, color{color} {}

void Text::draw() {
  fl_color(color);
  fl_font(FL_HELVETICA, fontSize);
  int width, height;
  fl_measure(s.c_str(), width, height, false);
  float x=fl_transform_x(center.x-width/2,center.y-fl_descent()+height/2);
  float y=fl_transform_y(center.x-width/2,center.y-fl_descent()+height/2);
  fl_draw(s.c_str(),x,y);
}

/*--------------------------------------------------

Class TextRectangle reprise des TPs

--------------------------------------------------*/

TextRectangle::TextRectangle(Point center, int w, int h, string text, int fontSize)
      : Text{text, center, fontSize}, Rectangle{center, w, h} {}


void TextRectangle::draw(){
    Rectangle::draw();
    Text::draw();
  }

// pour afficher le niv et le changer
void TextRectangle::setNiveau(){
  int niv = stoi(Text::getString());
  if (niv<5){
    Text::setString(to_string(niv+1));
  }
  else {
    Text::setString(to_string(1));
  }
}