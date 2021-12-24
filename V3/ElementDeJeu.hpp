#ifndef __ELEMENTDEJEU_H__
#define __ELEMENTDEJEU_H__

#include "Shapes.hpp"
#include "Animation.hpp"

class Animation;

/*--------------------------------------------------

ElementDeJeu class.

--------------------------------------------------*/

class ElementDeJeu{
    private:
        Point posPlat;
        Fl_Color couleur;
        int enlenver = 0; 

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

        void setEnlever(){
                enlenver = 1;
        }

        bool getEnlever(){
            return enlenver;
        }


        virtual void draw()=0;
        virtual int getMyId()=0;
        virtual void mouseClick(Point mouseLoc)=0;
        virtual void mouseMove(Point mouseLoc)=0;
        virtual Point getPosPlatifcontain(Point coord)=0;
        virtual void DoExplosion()=0;
        virtual void ElementMove(int sens)=0;
        virtual bool animation_is_complete()=0;
        


        virtual ~ElementDeJeu(){}
};


/*--------------------------------------------------

Bonbon class. Heritage ElementDeJeu

--------------------------------------------------*/

class Bonbon: public ElementDeJeu{
    private:
        Rectangle r;
        Animation *animation;
    
    public:
        Bonbon(Point posPlat, Fl_Color couleur, int w, int h);

        void draw() override;
        int getMyId() override;
        void drawWithoutAnimate();
        void mouseClick(Point mouseLoc) override;
        void mouseMove(Point mouseLoc) override;
        Point getPosPlatifcontain(Point coord) override;
        void DoExplosion() override;
        void ElementMove(int sens) override;
        bool animation_is_complete()override;
};

/*--------------------------------------------------

BonbonSpecialRond class. Heritage ElementDeJeu

--------------------------------------------------*/

class BonbonSpecialRond: public ElementDeJeu{   // bonbon emballé Bombe
    private:
        Circle c;
        Animation *animation;

    public:
        BonbonSpecialRond(Point posPlat, Fl_Color couleur, int r);

        void draw() override;
        int getMyId() override;
        void drawWithoutAnimate();
        void mouseClick(Point mouseLoc) override;
        void mouseMove(Point mouseLoc) override;
        Point getPosPlatifcontain(Point coord) override;
        void DoExplosion() override;
        void ElementMove(int sens) override{};
        bool animation_is_complete() override;

};

/*--------------------------------------------------

Mur class. Heritage ElementDeJeu

--------------------------------------------------*/

class Mur: public ElementDeJeu{
    private:
        Rectangle r;
    public:
        Mur(Point posPlat, int w, int h);

        void draw() override;
        int getMyId() override;
        void mouseClick(Point mouseLoc) override;
        void mouseMove(Point mouseLoc) override;
        Point getPosPlatifcontain(Point coord) override;
        void DoExplosion() override;
        void ElementMove(int sens) override{};
        bool animation_is_complete()override;

};

class Glacage: public ElementDeJeu{
  private: 
    Rectangle r;
    int vie;
  public:
    Glacage(Point posPlat, int w, int h);

    void draw() override{};
    int getMyId() override{return 100;};
    void mouseClick(Point mouseLoc) override{};
    void mouseMove(Point mouseLoc) override{};
    Point getPosPlatifcontain(Point coord) override{return {-1,-1};};
    void DoExplosion() override{};
    void ElementMove(int sens) override{};
    bool animation_is_complete()override{return EXIT_SUCCESS;};
};

#endif