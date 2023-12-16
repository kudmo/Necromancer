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

    auto update_e = [&](std::vector<std::weak_ptr<Entity>>::iterator It1, std::vector<std::weak_ptr<Entity>>::iterator It2) {
        for (auto e = It1; e != It2; ++e) {
            auto e_p = e->lock();
            if (e_p == nullptr || e_p->isDead())
                return;

            auto enemy = dynamic_cast<Enemy *>(e_p.get());
            if (enemy) {
                enemy->hunt();
            }
        }
    };
    size_t th_count = std::thread::hardware_concurrency();
    std::jthread theads[th_count];

    auto It_b = entities.begin();
    auto ent_count = entities.size();
    for (size_t i = 0; i < th_count; ++i) {
        size_t c = ent_count / (th_count - i);
        theads[i] = std::jthread(update_e, It_b, It_b + c);
        It_b += c;
        ent_count -= c;
    }
    for (auto &t : theads) {
        t.join();
    }
    if (player.expired()) {
        std::cout << "Game over" <<std::endl;
        End();
    }
}
