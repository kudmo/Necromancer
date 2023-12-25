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
    auto &curr = dungeon->getFloorByNumber(dungeon->getCurrentFloorNumber());
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


void Game::check() {
    if (ended)
        throw end_game_signal();
    if (player.lock() == nullptr)
        throw end_game_signal();
}

void Game::Update() {
    if (ended)
        throw end_game_signal();

    auto p = player.lock();
    if (p == nullptr) {
        End();
    }
    if (p->getCurrentMP() < p->getMaxMP()) p->restoreMP(1);
    if (p->getCurrentHP() < p->getMaxHP()) p->restoreHP(5);
    dungeon->Update();
    auto &curr = dungeon->getFloorByNumber(dungeon->getCurrentFloorNumber());
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
#ifndef ONE_THREAD
    for (auto &i : entities) {
        auto e = i.lock();
        if (e) e->resetState();
    }
    auto It_b = entities.begin();
    auto ent_count = entities.size();
    size_t th_count = std::thread::hardware_concurrency();
    std::jthread theads[th_count];
    for (size_t i = 0; i < th_count; ++i) {
        size_t c = ent_count / (th_count - i);
        theads[i] = std::jthread(update_e, It_b, It_b + c);
        It_b += c;
        ent_count -= c;
    }
    for (auto &t : theads) {
        t.join();
    }
#else
    update_e(entities.begin(), entities.end());
#endif
}
