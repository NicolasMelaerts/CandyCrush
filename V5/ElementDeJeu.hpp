#ifndef __ELEMENTDEJEU_H__
#define __ELEMENTDEJEU_H__

#include "Shapes.hpp"
#include "Animation.hpp"
#include "Text.hpp"

class Animation;

/*--------------------------------------------------

Classe abstraite ElementDeJeu

--------------------------------------------------*/

class ElementDeJeu{
    private:
        Point posPlat;
        Fl_Color couleur;

    public:
        Animation *animation;

        // constructeur
        ElementDeJeu(Point posPlat, Fl_Color couleur);

        // getter and setter
        Point getPoint();
        Point getposPlat();
        void setPosPlat(Point newPosPlat);
        void setCouleur(Fl_Color newc);

        // méthode
        virtual void draw()=0;
        virtual void drawWithoutAnimate()=0;
        virtual int getMyId()=0;
        virtual Fl_Color getcouleur()=0;
        virtual void mouseClick(Point mouseLoc)=0;
        virtual void mouseMove(Point mouseLoc)=0;
        virtual Point getPosPlatifcontain(Point coord)=0;
        virtual void DoExplosion()=0;
        virtual void ElementMove(int sens)=0;
        virtual bool animation_is_complete()=0;
        
};


/*--------------------------------------------------

Bonbon class. Heritage ElementDeJeu

--------------------------------------------------*/

class Bonbon: public ElementDeJeu{
    private:
        Rectangle r;
    
    public:
        Bonbon(Point posPlat, Fl_Color couleur, int w, int h);

        Rectangle getR();

        int getMyId() override;
        void draw() override;
        Fl_Color getcouleur()override;
        void drawWithoutAnimate() override;
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

    public:
        BonbonSpecialRond(Point posPlat, Fl_Color couleur, int r);

        int getMyId() override;
        void draw() override;
        Fl_Color getcouleur()override;
        void drawWithoutAnimate() override;
        void mouseClick(Point mouseLoc) override;
        void mouseMove(Point mouseLoc) override;
        Point getPosPlatifcontain(Point coord) override;
        void DoExplosion() override;
        void ElementMove(int sens) override;
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

        int getMyId() override;
        void draw() override;
        void drawWithoutAnimate() override;
        Fl_Color getcouleur()override;
        void mouseClick(Point mouseLoc) override;
        void mouseMove(Point mouseLoc) override;
        Point getPosPlatifcontain(Point coord) override;
        void DoExplosion() override;
        void ElementMove(int sens) override{};
        bool animation_is_complete()override;

};

/*--------------------------------------------------

Glacage class. Heritage ElementDeJeu

--------------------------------------------------*/


class Glacage: public ElementDeJeu{
    private:
        Rectangle r;
        int vie;        // Glacage de Niv 1 ou Niv 2 
    public:
        Glacage(Point posPlat, int w, int h);

        int getMyId() override;
        void draw() override;
        void drawWithoutAnimate() override{};
        Fl_Color getcouleur()override;
        void mouseClick(Point mouseLoc) override{};
        void mouseMove(Point mouseLoc) override{};
        Point getPosPlatifcontain(Point coord) override{return {-1,-1};};
        void DoExplosion() override;
        void ElementMove(int sens) override{};
        bool animation_is_complete()override{return EXIT_SUCCESS;};

        int getVie(){
            return vie;
        }
        void perdVie(){
            vie--;
        }

};

/*--------------------------------------------------

Bonbon spécial horizontaux

--------------------------------------------------*/


class BonbonSpecialHorizontal: public Bonbon{
    private:

    public:
    BonbonSpecialHorizontal(Point posPlat, Fl_Color couleur, int w, int h):Bonbon(posPlat, couleur, w, h){}

    int getMyId() override{
        int c = getR().getFillColor();
        if (c==FL_RED){return -1;}
        if (c==FL_BLUE){return -2;}
        if (c==FL_YELLOW){return -3;}
        if (c==FL_GREEN){return -4;}
        if (c==FL_MAGENTA){return -5;}
        else {return -6;} // (c==fl_rgb_color(251, 139, 35))
    }
};

/*--------------------------------------------------

Bonbon spécial vertical

--------------------------------------------------*/

class BonbonSpecialVertical: public Bonbon{
    private:

    public:
    BonbonSpecialVertical(Point posPlat, Fl_Color couleur, int w, int h):Bonbon(posPlat, couleur, w, h){}

    int getMyId() override{
        int c = getR().getFillColor();
        if (c==FL_RED){return -7;}
        if (c==FL_BLUE){return -8;}
        if (c==FL_YELLOW){return -9;}
        if (c==FL_GREEN){return -10;}
        if (c==FL_MAGENTA){return -11;}
        else {return -12;} // (c==fl_rgb_color(251, 139, 35))
    }
};

/*--------------------------------------------------

Coockies

--------------------------------------------------*/


class BonbonSpecialRondCookies: public BonbonSpecialRond{
    private:

    public:
    BonbonSpecialRondCookies(Point posPlat, Fl_Color couleur, int r):BonbonSpecialRond(posPlat, couleur, r){}

    int getMyId() override{
        return -19;
    }
};


/*--------------------------------------------------

Ingrédients

--------------------------------------------------*/

class Ingredient: public ElementDeJeu{
    private:
    TextRectangle r;

    public:
    Ingredient(Point posPlat, string s, int w, int h):ElementDeJeu(posPlat, FL_WHITE), r{{50*posPlat.y+48, 50*posPlat.x+70}, w, h, s, 20}{}

    int getMyId() override;
    void draw() override;
    void drawWithoutAnimate() override;
    Fl_Color getcouleur()override{return FL_WHITE;};
    void mouseClick(Point mouseLoc) override;
    void mouseMove(Point mouseLoc) override;
    Point getPosPlatifcontain(Point coord) override;
    void DoExplosion() override{};
    void ElementMove(int sens) override;
    bool animation_is_complete()override;

};

#endif