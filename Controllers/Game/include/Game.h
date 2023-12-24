#ifndef LAB3_GAME_H
#define LAB3_GAME_H

#include <memory>

#include "Dungeon/Dungeon.h"
#include "Player/Player.h"

class end_game_signal : public std::exception {
public:
    end_game_signal() = default;
};

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
    void check();
    void Update();
    void End() {
        ended = true;
        throw end_game_signal();
    }
};
#endif //LAB3_GAME_H
