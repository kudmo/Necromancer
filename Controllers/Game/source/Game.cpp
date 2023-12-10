#include <Game.h>
#include <memory>
#include <iostream>
#include <thread>
#include <mutex>

#include "GlobalSkillManager.h"
#include "Enemy/Enemy.h"

Game::Game(std::string file) {
    dungeon = std::make_unique<Dungeon>(file);
    dungeon->loadDungeon();
    auto &curr = dungeon->floorByNumber(dungeon->getCurrentLevel());
    curr.loadFloor();

    std::unique_ptr<SkillTable> table;
    std::vector<std::string>  _table {"curse", "desiccation","necromancy", "morphism"};

    try {
        table = GlobalSkillManager::buildSkillTableDefault(_table);
    } catch  (std::exception& e) {
        std::cerr <<e.what() <<std::endl;
    }
    auto p = std::make_shared<Player>(curr, std::pair<size_t,size_t>(2,2), std::move(table));
    curr.addEntity(p);
    player = std::weak_ptr<Player>(p);
}


void Game::Update() {
    if (ended)
        throw std::runtime_error("Game is ended");
    if (player.expired()) {
        std::cout << "End game: game over" <<std::endl;
        End();
    }
    dungeon->Update();
    auto &curr = dungeon->floorByNumber(dungeon->getCurrentLevel());
    auto entities = curr.getEntities();

//    std::mutex update_e_mutex;
    auto update_e = [&](std::weak_ptr<Entity> e) {
//        std::scoped_lock lock(update_e_mutex);
        if (!e.expired()) {
            auto e_p = e.lock();
            auto enemy = dynamic_cast<Enemy *>(e_p.get());
            if (enemy) {
                enemy->hunt();
            }
        }
    };

    for (auto &e : entities) {
        std::jthread th1(update_e, e);
//        update_e(e);
    }
    if (player.expired()) {
        std::cout << "End game" <<std::endl;
        End();
    }
}
