#ifndef LAB3_DUNGEONVIEWCONTROLLER_H
#define LAB3_DUNGEONVIEWCONTROLLER_H

#include "Dungeon_View.h"
#include <Game.h>
#include <MenuController.h>
#include <SFML/Graphics.hpp>

class DungeonViewController {
private:
    Game& game;
    Dungeon_View view;
    sf::RenderWindow& window;
public:
    DungeonViewController(sf::RenderWindow& window, Game &game);
    Dungeon_View& getView() {return view;}
    void handleEvent(sf::Event);
};


#endif //LAB3_DUNGEONVIEWCONTROLLER_H
