#include "Shapes.hpp"

class Animation;

class ElementDeJeu{
    private:
        Point posPlat;
        Fl_Color couleur;

    public:
        ElementDeJeu(Point posPlat, Fl_Color couleur);
    
        Point getPoint(){
            return {50*posPlat.y+48, 50*posPlat.x+70};
        }
        Point getposPlat(){
          return posPlat;
        }

        void setPosPlat(Point newPosPlat){
          posPlat = newPosPlat;
        };


        virtual void draw()=0;
        virtual void mouseClick(Point mouseLoc)=0;
        virtual void mouseMove(Point mouseLoc)=0;
        virtual Point getPosPlatifcontain(Point coord)=0;
        virtual void DoExplosion()=0;


        virtual ~ElementDeJeu(){}
};


class Bonbon: public ElementDeJeu{
    private:
        Rectangle r;
        Animation *animation;
    
    public:
        Bonbon(Point posPlat, Fl_Color couleur, int w, int h);

        void draw() override;
        void drawWithoutAnimate();
        void mouseClick(Point mouseLoc) override;
        void mouseMove(Point mouseLoc) override;
        Point getPosPlatifcontain(Point coord) override;
        void DoExplosion() override;
};

class BonbonSpecialRond: public ElementDeJeu{   // bonbon emballé Bombe
    private:
        Circle c;
        Animation *animation;

    public:
        BonbonSpecialRond(Point posPlat, Fl_Color couleur, int r);

        void draw() override;
        void drawWithoutAnimate();
        void mouseClick(Point mouseLoc) override;
        void mouseMove(Point mouseLoc) override;
        Point getPosPlatifcontain(Point coord) override;
        void DoExplosion() override;
};

class Mur: public ElementDeJeu{
    private:
        Rectangle r;
    public:
        Mur(Point posPlat, int w, int h);

        void draw() override;
        void mouseClick(Point mouseLoc) override;
        void mouseMove(Point mouseLoc) override;
        Point getPosPlatifcontain(Point coord) override;
        void DoExplosion() override;
};


struct Translation {
  Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() {
    fl_pop_matrix();
  }
};

struct Rotation {
  Rotation(Point center, double angle) {
    fl_push_matrix();
    fl_translate(center.x, center.y);
    fl_rotate(angle);
    fl_translate(-1*center.x, -1*center.y);
  }
  ~Rotation() {
    fl_pop_matrix();
  }
};


class Animation{
public:
    enum AnimationType {explosion, Bonbon_fall};
private:
    const int animationTime = 60;
    const int descente = 100;
    Bonbon *b;
    AnimationType animationType;
    int time{0};
    Point currentBonbonFall();
    double currentExplosion();
public:
    Animation(Bonbon *BonbonToAnimate, AnimationType animationType):b{BonbonToAnimate}, animationType{animationType}{}
    void draw();
    bool isComplete();
};


