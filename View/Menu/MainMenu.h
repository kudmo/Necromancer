#ifndef LAB3_MAINMENU_H
#define LAB3_MAINMENU_H
#include <SFML/Graphics.hpp>

class MainMenu {
private:
    uint mainMenuSelected;
    std::vector<sf::Text> menu_elements;
    sf::Font font;
    sf::RenderWindow& mywindow;
public:
    void draw();
    void MoveUp();
    void MoveDown();
    uint getSelectedMenuNumber() {return mainMenuSelected;}
};


#endif //LAB3_MAINMENU_H
