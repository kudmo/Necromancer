#ifndef LAB3_GAMEVIEWCONTROLLER_H
#define LAB3_GAMEVIEWCONTROLLER_H

#include <Game.h>
#include <GameView.h>
#include <SFML/Graphics.hpp>
#include "MenuController.h"
#include "AdminElements.h"



class GameViewController {
private:
    Game& game;
    GameView view;
    sf::RenderWindow& window;
    bool isMenuActive = false;
public:
    GameViewController(sf::RenderWindow& window, Game &game);

    GameView& getView() {
        game.check();
        return view;
    }
    void handleEvent(sf::Event);
};

class TextSelectingMenu : public MenuController {
private:
    std::string sel;
    std::vector<std::string> strings;
public:
    TextSelectingMenu(sf::RenderWindow &window, float menux, float menuy, int alignPos,
                      const std::vector<std::string> &menuElements, int sizeFont, int step);

    void DoSelected() override;
    std::string getSelected() const {return sel;}
};

class TargetMenu : public MenuController {
private:
    std::vector<std::reference_wrapper<Object>> targets;
public:
    TargetMenu(std::vector<std::reference_wrapper<Object>> targets,
               sf::RenderWindow &window, float menux, float menuy, int alignPos,
                const std::vector<std::string> &menuElements, int sizeFont, int step);

    void DoSelected() override {close();}
    Object& getSelected() {return targets[getForm().getSelectedMenuNumber()];}
};

#endif //LAB3_GAMEVIEWCONTROLLER_H
