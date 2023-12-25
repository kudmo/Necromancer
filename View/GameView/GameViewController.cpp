#include <iostream>
#include "GameViewController.h"
#include "Item/Item.h"
#include "GlobalEnemyManager.h"

GameViewController::GameViewController(sf::RenderWindow &window, Game &game): game(game),
    view(game.getPlayer(), game.getDungeon().getCurrentFloor(), window),
    window(window) {}

void TextSelectingMenu::DoSelected() {
    sel = strings[getForm().getSelectedMenuNumber()];
    close();
}

TextSelectingMenu::TextSelectingMenu(sf::RenderWindow &window, float menux, float menuy, int alignPos,
                                     const std::vector<std::string> &menuElements, int sizeFont, int step) :
                     MenuController(window, menux, menuy, alignPos, menuElements, sizeFont, step) {
    strings = menuElements;
}

TargetMenu::TargetMenu(std::vector<std::reference_wrapper<Object>> targets,
                       sf::RenderWindow &window, float menux, float menuy, int alignPos,
                       const std::vector<std::string> &menuElements, int sizeFont, int step) :
        MenuController(window, menux, menuy, alignPos, menuElements, sizeFont, step) {
    this->targets = targets;
}


void GameViewController::handleEvent(sf::Event event) {
    game.check();
    auto &p = game.getPlayer();
    // skill
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
    // selected field
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        auto f_coord = view.getFloorView()->getFieldByCoord(sf::Vector2f(mouse_pos));

    // target selecting
        auto &floor = view.getFloorView()->getFloor();
        auto entities = floor.getEntities();
        auto items = floor.getByCoord(f_coord).getItems();

        std::vector<std::reference_wrapper<Object>> targets;
        for (auto &i: entities) {
            auto e = i.lock();
            if (e == nullptr || e->isDead())
                continue;
            if (e->getCoordinates() == f_coord) {
                try {
                    targets.emplace_back(*e);
                } catch (skill_errors::invalid_skill_target&) {

                }
            }
        }
        for (auto &i: items) {
            try {
                Item& it = i.get();
                targets.emplace_back(i);
            } catch (skill_errors::invalid_skill_target&) {

            }
        }

        std::vector<std::string> target_names;
        target_names.reserve(targets.size());
        for (auto &i : targets) {
            target_names.push_back(i.get().getNaming());
        }

        auto targ_menu = new TargetMenu(targets, window, 0, 0, 0, target_names, 48, 32);
        view.addAdminMenu(targ_menu->getForm());
        while (window.isOpen()) {
            sf::Event subevent;
            try {
                while (window.pollEvent(subevent)) {
                    targ_menu->handleEvent(subevent);
                }
            } catch (const close_menu_signal &) {
                break;
            }
            window.clear();
            window.draw(view);
            window.display();
        }

        Object& target = targ_menu->getSelected();
        view.removeUpperAdminMenu();
        delete targ_menu;

    // skill selecting
        std::string selected_skill;
        auto skills_ = p.getAllSubSkills();
        std::vector<std::string> skills;
        for (auto &i : skills_) {
            auto main_skill = i.substr(0, i.find("_"));
            try {
                p.checkSkillTarget(main_skill, i, target);
            } catch (skill_errors::invalid_skill_target&) {
                continue;
            }
            skills.push_back(i);
        }

        auto skill_menu = new TextSelectingMenu(window, 0, 0, 0, skills, 48, 32);
        view.addAdminMenu(skill_menu->getForm());

        while (window.isOpen()) {
            sf::Event subevent;
            try {
                while (window.pollEvent(subevent)) {
                    skill_menu->handleEvent(subevent);
                }
            } catch (const close_menu_signal &) {
                break;
            }
            window.clear();
            window.draw(view);
            window.display();
        }
        selected_skill = skill_menu->getSelected();
        auto main_skill= selected_skill.substr(0, selected_skill.find("_"));

        view.removeUpperAdminMenu();
        delete skill_menu;

    // using skill
        try {
            p.useSkill(main_skill, selected_skill, target);
            game.Update();
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        // upgrading
        game.Update();
        if (event.key.code == sf::Keyboard::U) {
            std::vector<std::string> can_be_upgraded;
            if (p.getEssenceCount() >= 100)
                can_be_upgraded.push_back("explore new undead type");
            if (p.getSkillPoints() > 0)
                can_be_upgraded.push_back("upgrade skills");

            if (can_be_upgraded.empty()) {
                std::cerr << "Nothing to upgrade" << std::endl;
                return;
            }
            auto upgr_menu =  new TextSelectingMenu(window, 0, 0, 0, can_be_upgraded, 48, 32);
            view.addAdminMenu(upgr_menu->getForm());
            while (window.isOpen()) {
                sf::Event subevent;
                try {
                    while (window.pollEvent(subevent)) {
                        upgr_menu->handleEvent(subevent);
                    }
                } catch (const close_menu_signal &) {
                    break;
                }
                window.clear();
                window.draw(view);
                window.display();
            }
            std::string selected_upgrading = upgr_menu->getSelected();
            view.removeUpperAdminMenu();
            delete upgr_menu;

            if (selected_upgrading == "upgrade skills") {
                auto skills = p.getAllSkills();
                if (skills.empty()) {
                    std::cerr << "Nothing to upgrade" << std::endl;
                    return;
                }

                auto skill_menu =  new TextSelectingMenu(window, 0, 0, 0, skills, 48, 32);
                view.addAdminMenu(skill_menu->getForm());
                while (window.isOpen()) {
                    sf::Event subevent;
                    try {
                        while (window.pollEvent(subevent)) {
                            skill_menu->handleEvent(subevent);
                        }
                    } catch (const close_menu_signal &) {
                        break;
                    }
                    window.clear();
                    window.draw(view);
                    window.display();
                }
                std::string selected_skill = skill_menu->getSelected();
                view.removeUpperAdminMenu();
                delete skill_menu;

                p.upgradeSkill(selected_skill);
            } else if (selected_upgrading == "explore new undead type") {
                std::vector<std::string> undead_types;
                for (auto &i : GlobalEnemyManager::getAllTypesInEnemyClass("undead")) {
                    bool f = true;
                    for (auto &j : undead_types) {
                        if (i == j) {
                            f = false;
                            break;
                        }
                    }
                    if (f)
                        undead_types.push_back(i);
                }

                if (undead_types.empty()) {
                    std::cerr << "Nothing to upgrade" << std::endl;
                    return;
                }
                auto undead_type_menu =  new TextSelectingMenu(window, 0, 0, 0, undead_types, 48, 32);
                view.addAdminMenu(undead_type_menu->getForm());
                while (window.isOpen()) {
                    sf::Event subevent;
                    try {
                        while (window.pollEvent(subevent)) {
                            undead_type_menu->handleEvent(subevent);
                        }
                    } catch (const close_menu_signal &) {
                        break;
                    }
                    window.clear();
                    window.draw(view);
                    window.display();
                }
                std::string selected_undead_type = undead_type_menu->getSelected();
                view.removeUpperAdminMenu();
                delete undead_type_menu;

                p.exploreNewUndeadType(selected_undead_type);
            }

        }
        // move
        try {
            if (event.key.code == sf::Keyboard::Left) {
                p.rotate(DIRECTIONS::LEFT);
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    p.move();
            }
            if (event.key.code == sf::Keyboard::Right) {
                p.rotate(DIRECTIONS::RIGHT);
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    p.move();
            }
            if (event.key.code == sf::Keyboard::Up) {
                p.rotate(DIRECTIONS::UP);
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    p.move();
            }
            if (event.key.code == sf::Keyboard::Down) {
                p.rotate(DIRECTIONS::DOWN);
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    p.move();
            }
        } catch (dungeon_errors::invalid_position_error &e) {
            std::cerr << e.what() << std::endl;
        }

        // attack
        if (event.key.code == sf::Keyboard::A) {
            try {
                auto current_level = game.getDungeon().getCurrentFloorNumber();
                auto &first_floor = game.getDungeon().getFloorByNumber(current_level);

                auto next_coord = first_floor.getNextByDirection(p.getCoordinates(), p.getDirection());

                auto entities = first_floor.getEntities();
                for (auto &i: entities) {
                    auto e = i.lock();
                    if (e == nullptr || e->isDead())
                        continue;
                    if (e->getCoordinates() == next_coord) {
                        p.attack(*e);
                    }
                }

            } catch (dungeon_errors::dungeon_exception &e) {
                std::cerr << e.what() << std::endl;
            } catch (entity_errors::entity_exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }



        // interact
        if (event.key.code == sf::Keyboard::E) {
            try {
                auto current_level = game.getDungeon().getCurrentFloorNumber();
                auto &first_floor = game.getDungeon().getFloorByNumber(current_level);
                auto next_coord = first_floor.getNextByDirection(p.getCoordinates(), p.getDirection());
                auto &next = first_floor.getByCoord(next_coord);
                p.smartInteract(next);
                view.setFloor(game.getDungeon().getCurrentFloor());
            } catch (dungeon_errors::invalid_floor_error&) {
                return;
            } catch (dungeon_errors::dungeon_exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

    }
}
