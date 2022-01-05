#include "Animation.hpp"

/*--------------------------------------------------

Animation class.

--------------------------------------------------*/


void Animation::draw() {
  for (int k=0; k<5; k++)
    ++time;
  Translation t3{MoveElementDeJeu()};
  Rotation r{b->getPoint(), ExploseElementDeJeu()};
  b->drawWithoutAnimate();
}

Point Animation::MoveElementDeJeu() {
  if (animationType==move){
    if (sens==0){     // vers le bas
      return {0, static_cast<int>(1*descente*sin(3.1415*time/animationTime/6))};
    }
    else if (sens==1){    // vers le haut
      return {0, static_cast<int>(-1*descente*sin(3.1415*time/animationTime/6))};
    }
    else if (sens==2){    // vers la droite
      return {static_cast<int>(1*descente*sin(3.1415*time/animationTime/6)), 0};
    }
    else if (sens==3){    // vers la gauche
      return {static_cast<int>(-1*descente*sin(3.1415*time/animationTime/6)), 0};
    }
    else if (sens==4){    // en diagonale vers le bas a gauche 
      return {static_cast<int>(-1*descente*sin(3.1415*time/animationTime/6)), static_cast<int>(1*descente*sin(3.1415*time/animationTime/6))};
    }
    else if (sens==5){    // en diagonale vers le bas a droite
      return {static_cast<int>(1*descente*sin(3.1415*time/animationTime/6)), static_cast<int>(1*descente*sin(3.1415*time/animationTime/6))};
    }
    
    else return {0, 0};
  }
  else return {0,0};
}

double Animation::ExploseElementDeJeu() {
  if (animationType==explosion)
    return time*360.0/animationTime;
  else
    return 0;
}

bool Animation::isComplete() {
  return time>60;
}