/*

Auteur  : Nicolas Melaerts
Date    : Janvier 2021
Cours   : Langages de programmation 2
Section : Sciences Informatiques ULB

But du programme : Jeu inspiré de Candy Crush Saga

*/

#include "Jeu.hpp"
#include "Text.hpp"
#include "Afficher.hpp"
#include "Control.hpp"

using namespace std;


class MainWindow : public Fl_Window {
    EcranAccueil e;
    int time=0;

    // Modèle 
    shared_ptr<jeu> j = make_shared<jeu>(1);
    
    // Vue
    Canvas canvas{j};
    AfficherScoreAndNb_coups sAndc{j};
    Menu m{j};

    // Contrôleur
    ControlJeu controljeu{j};

    public:
    MainWindow() : Fl_Window(000, 000, 500, 600, "Candy Crush") {
        Fl::add_timeout(1.0/60, Timer_CB, this);
        resizable(this);
    }
    void draw() override {
        Fl_Window::draw();
        if (time < 200){
            e.draw();
            ++time;
        }
        else{
            canvas.draw();
            m.draw();
            sAndc.draw();
        }    
    }
    int handle(int event) override {
        switch (event) {
            case FL_RELEASE:    // relacher clic
                if (controljeu.getForDrag().size()>1)
                    controljeu.tentativeSwap();

            case FL_MOVE:
                controljeu.mouseMove(Point{Fl::event_x(),Fl::event_y()});
                return 1;

            case FL_KEYDOWN:
                if (Fl::event_key() == 'r'){
                    controljeu.reset_meilleur_score();
                }
                
                if (Fl::event_key() == ' ' and !controljeu.get_jeu_en_cours()){
                    m.changeNiv();
                    controljeu.changeNiv(m.getniv());
                }
                if (Fl::event_key()=='q'){exit(0);}

            case FL_DRAG:   // pour tenter de swap des bonbons
                controljeu.drag(Point{Fl::event_x(),Fl::event_y()});

            case FL_PUSH:
                return 1;
        }   
        return 0;
    }
    static void Timer_CB(void *userdata) {
        MainWindow *o = (MainWindow*) userdata;
        o->redraw();
        Fl::repeat_timeout(1.0/60, Timer_CB, userdata);
    }
};

int main(int argc, char *argv[]) {
    MainWindow window;
    window.show(argc, argv);
    return Fl::run();
}