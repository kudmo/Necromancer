#include <iostream>
#include "DungeonViewController.h"
#include <MenuView.h>

DungeonViewController::DungeonViewController(sf::RenderWindow& window, Game &game) : game(game), view(game.getDungeon(), window), window(window) {
    Dungeon& d = game.getDungeon();
    view.Init();
    view.setPosition(5,5);
}

void DungeonViewController::handleEvent(sf::Event event) {
//    if (event.type == sf::Event::Resized) {
//        view.setPosition(window.mapPixelToCoords(sf::Vector2i{view.getPosition()}));
//    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Right) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

            auto mymenu = SkillMenu(window, mouse_pos.x,
                                    mouse_pos.y, 2, std::vector<sf::String>({"menu1", "menu2"}), 32, 24);
            mymenu.setColorTextMenu(sf::Color::Green, sf::Color::Yellow, sf::Color::Transparent);
            while (window.isOpen())
            {
                sf::Event event_play;
                while (window.pollEvent(event_play))
                {
                    if (event_play.type == sf::Event::KeyPressed)
                    {
                        if (event_play.key.code == sf::Keyboard::Escape) { return; }
                    }
                    try {
                        mymenu.handleEvent(event_play);
                    } catch (...) {
                        return;
                    }
                }
                window.clear();
                window.draw(this->view);
                window.draw(mymenu.getForm());
                window.display();
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        game.Update();
        auto &p = game.getPlayer();
        try {
            if (event.key.code == sf::Keyboard::Left) {
                p.rotate(DIRECTIONS::LEFT);
                p.move();
            }
            if (event.key.code == sf::Keyboard::Right) {
                p.rotate(DIRECTIONS::RIGHT);
                p.move();
            }
            if (event.key.code == sf::Keyboard::Up) {
                p.rotate(DIRECTIONS::UP);
                p.move();
            }
            if (event.key.code == sf::Keyboard::Down) {
                p.rotate(DIRECTIONS::DOWN);
                p.move();
            }
        } catch (dungeon_errors::invalid_position_error &e) {
            std::cerr << e.what() << std::endl;
        }
        if (event.key.code == sf::Keyboard::E) {
            try {
                auto current_level = game.getDungeon().getCurrentFloorNumber();
                auto &first_floor = game.getDungeon().getFloorByNumber(current_level);
                auto next_coord = first_floor.getNextByDirection(p.getCoordinates(), p.getDirection());
                auto &next = first_floor.getByCoord(next_coord);
                p.smartInteract(next);
            } catch (dungeon_errors::dungeon_exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }


    }
}


