#include "Text.hpp"


/*--------------------------------------------------

Text class

--------------------------------------------------*/

void Text::draw() {
  fl_color(color);
  fl_font(FL_HELVETICA, fontSize);
  int width, height;
  fl_measure(s.c_str(), width, height, false);
  float x=fl_transform_x(center.x-width/2,center.y-fl_descent()+height/2);
  float y=fl_transform_y(center.x-width/2,center.y-fl_descent()+height/2);
  fl_draw(s.c_str(),x,y);
}