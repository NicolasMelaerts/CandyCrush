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

#include "ElementsDeJeu.hpp"

class Canvas{
    vector< vector<Bonbon> > bonbons;
    vector<Fl_Color > Colors{FL_BLUE, FL_GREEN, FL_RED, FL_MAGENTA,FL_YELLOW, fl_rgb_color(251, 139, 35)};
    void initialize();
    jeu j;
public:
    //constructeur
    Canvas(){
        initialize();
    };

    // méthodes
    void draw();
    void mouseMove(Point mouseLoc);
    void moveBonbon(Point p, int keyCode);
    void mouseClick(Point mouseLoc);
    void maj_canvas();
    void fall();
    void afficherCanvas();
};


