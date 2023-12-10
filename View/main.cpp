#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dungeon/Floor_View.h"
#include "Dungeon/Dungeon_View.h"

#include "Floor/Floor.h"
#include "Player/Player.h"
#include <Game.h>

int main() {
    Game g = Game("View/Dungeon/input_files/test_dungeon.json");
    Player& p = g.getPlayer();
    Dungeon& d = g.getDungeon();



    sf::RenderWindow window(
            sf::VideoMode(d.floorByNumber(d.getCurrentLevel()).getSize().first*FIELD_SIZE+10,
                          d.floorByNumber(d.getCurrentLevel()).getSize().second*FIELD_SIZE+10),
                          "Test game");
    window.setFramerateLimit(60);
    auto dungeonView = Dungeon_View(d, window);
    dungeonView.Init();
    dungeonView.setPosition(5,5);
try {
    std::cout << "ASDASDASDASASDASD" <<std::endl;
    while (window.isOpen()) {
        sf::Event event;
        auto current_level = d.getCurrentLevel();
        auto &first_floor = d.floorByNumber(current_level);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();
                g.Update();
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
                try {
                    if (event.key.code == sf::Keyboard::E) {
                        auto next_coord = first_floor.getNextByDirection(p.getCoordinates(), p.getDirection());
                        auto &next = first_floor.getByCoord(next_coord);
                        p.smartInteract(next);
                    }
                } catch (dungeon_errors::dungeon_exception &e) {
                    std::cerr << e.what() << std::endl;
                }

            }
        }
        window.clear();
        window.draw(dungeonView);
        window.display();
    }
} catch (std::runtime_error& e) {
    std::cerr << e.what() <<std::endl;
}
    return 0;
}