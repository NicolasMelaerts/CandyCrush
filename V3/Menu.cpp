#include "Menu.hpp"

void Menu::draw(){
    Text("Selection Niveau : ", {100, 15}, 20, FL_BLACK).draw();
    Text("Meilleur Score : ", {100, 40}, 20, FL_BLACK).draw();
    Text("Score : ", {325, 15}, 20).draw();
    Text("Coups restants : ", {360, 40}, 20).draw();
    Text("Utilise la souris pour swapper des bonbons", {250, 510}, 20).draw();
    Text("Appuie sur 'Espace' pour changer de niveau", {250, 530}, 20).draw();
    Text("Appuie sur 'q' pour quitter", {250, 550}, 20).draw();

    niv.draw();
}

void Menu::changeNiv(){
    niv.setNiveau();
}