#include "ElementDeJeu.hpp"
#include "Jeu.hpp"

class Canvas{
    private:
        vector< vector<shared_ptr<ElementDeJeu>> > E;
        
        vector<Fl_Color > Colors{FL_RED, FL_BLUE,FL_YELLOW, FL_GREEN, FL_MAGENTA, fl_rgb_color(251, 139, 35)};
        void initialize();
        jeu j;

    public:

        vector<Point> ForDrag;

        Canvas(){
            initialize();
            
        }

        void draw();
        void mouseMove(Point mouseLoc);

        void drag(Point mouseLoc);
        void swapElementDeJeu();

        void mouseClick(Point mouseLoc);

        void maj_canvas();
        void fall();
        void wait_anim();
};