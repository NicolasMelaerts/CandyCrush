#include "PlateauDeJeu.hpp"

void Canvas::initialize(){
    for (int x = 0; x<9; x++){
        for (int y = 0; y<9; y++){
            int ajout = j.getelemplateau(x,y);
            if (ajout==0){
                Mur m{{x,y}, 40, 40};
                E.push_back(make_shared<Mur>(m));
            }
            if (ajout >= 1 && ajout <= 6){
                Bonbon b{{x,y}, Colors[ajout-1], 35, 35};
                E.push_back(make_shared<Bonbon>(b));
            }
            if (ajout >= -18 && ajout <= -13){
                BonbonSpecialRond bs{{x,y}, Colors[abs(ajout+1)%6], 20};
                E.push_back(make_shared<BonbonSpecialRond>(bs));
            }
        }
    }
}


void Canvas::draw(){
    for (auto &e:E)
        e.get()->draw();
}

void Canvas::mouseMove(Point mouseLoc){
    for (auto &e:E)
        e.get()->mouseMove(mouseLoc);
}

void Canvas::drag(Point mouseLoc){
    ForDrag.push_back(mouseLoc);
}

void Canvas::swapElementDeJeu(){
    Point p1, p2;
    int idx1, idx2;

    for (int i = 0; i<E.size(); i++){
        p1 = E[i].get()->getPosPlatifcontain(ForDrag[0]);
        idx1 = i;
        if (p1.x != -1){
            break;
        }
    }

    for (int i = 0; i<E.size(); i++){
        p2 = E[i].get()->getPosPlatifcontain(ForDrag[ForDrag.size()-1]);
        idx2 = i;
        if (p2.x != -1 and p2.y!=-1){
            break;
        }
    }
    if (p1.x != -1 && p2.x != -1){
        if ((p1.x == p2.x and p1.y == p2.y+1) || (p1.x == p2.x and p1.y == p2.y-1)
            || (p1.x == p2.x+1 and p1.y == p2.y) || (p1.x == p2.x-1 and p1.y == p2.y)){
            if (j.coup_possible({p1.x, p1.y}, {p2.x, p2.y})){
                E[idx1].get()->setPosPlat(p2);
                E[idx2].get()->setPosPlat(p1);
            }
            else cout << "coup impossible" << endl;
        }
    }

    ForDrag.clear();
}

void Canvas::mouseClick(Point mouseLoc){
    //for (auto &e: E)
        //e.get()->DoExplosion();
}