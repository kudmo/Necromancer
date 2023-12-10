#ifndef LAB3_GAME_H
#define LAB3_GAME_H

#include <memory>

#include "Dungeon/Dungeon.h"
#include "Player/Player.h"

class Game {
private:
    bool ended = false;
    std::unique_ptr<Dungeon> dungeon;
    size_t current_level = 0;
    std::weak_ptr<Player> player;
public:
    //! @todo Перемещение персонажа между уровнями (обновление текущего уровня)
    //! @todo Смерть персонажа

    Game(std::string file);
    Player &getPlayer() {
        return *player.lock();
    }
    Dungeon& getDungeon() {return *dungeon;}
    void Update();
    void End() {
        ended = true;
        throw std::runtime_error("Game is ended");
    }
};
#endif //LAB3_GAME_H
