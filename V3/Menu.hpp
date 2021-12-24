#ifndef __MENU_H__
#define __MENU_H__

#include "Shapes.hpp"
#include "Text.hpp"

class Menu{
    private:
        TextRectangle niv{{200, 15}, 20,20, "1", 20};
    public:
        Menu(){};

        void draw();
        void changeNiv();

        int getniv(){
            return stoi(niv.getString());
        }
        
};


#endif