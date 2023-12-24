#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dungeon/Floor_View.h"
#include "Dungeon/Dungeon_View.h"

#include "Floor/Floor.h"
#include "Player/Player.h"
#include <Game.h>
#include <GameViewController.h>
#include <MenuView.h>
#include <MenuController.h>
#include "Dungeon/DungeonViewController.h"

class ApMenu : public MenuController {
private:
    GameViewController& v;
public:
    ApMenu(GameViewController& g, sf::RenderWindow& window, float menux, float menuy, int align_pos, int sizeFont = 60, int step = 80);
    void DoSelected() override {
        switch (getForm().getSelectedMenuNumber())
        {
            case 0: GameStart(window); break;
            case 1: close(); break;
        }
    }
    void GameStart(sf::RenderWindow& Play) {
        v.getView().Init();
        while (Play.isOpen())
        {
            sf::Event event_play;
            while (Play.pollEvent(event_play))
            {
                if (event_play.type == sf::Event::KeyPressed)
                {
                    if (event_play.key.code == sf::Keyboard::Escape) { return; }
                }
                try {
                    v.handleEvent(event_play);
                } catch (std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    window.close();
                }
            }
            Play.clear();
            try {
                auto &e = v.getView();
                Play.draw(e);
            } catch (end_game_signal&) {
                window.close();
            }
            Play.display();
        }
    }
};
ApMenu::ApMenu(GameViewController& g, sf::RenderWindow &window, float menux, float menuy, int align_pos, int sizeFont, int step)
        : MenuController(window, menux, menuy, align_pos, std::vector<std::string>({"Start", "Out"}), sizeFont, step), v(g){}

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode::getDesktopMode(), L"Моя игра", sf::Style::Default);

    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    Game g = Game("View/Dungeon/input_files/test_dungeon.json");


    auto gameViewController = GameViewController(window, g);
    ApMenu mymenu(gameViewController, window, width/2, height/2 -100,  100, 120);
    mymenu.setColorTextMenu(sf::Color(237, 147, 0), sf::Color::Red, sf::Color::Black);

    sf::View view = window.getDefaultView();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            try {
                mymenu.handleEvent(event);
            }catch (const close_menu_signal&) {
                window.close();
            }
        }

        window.clear();
        window.draw(mymenu.getForm());
        window.display();
    }

    return 0;
}