#ifndef LAB3_GAME_H
#define LAB3_GAME_H

#include <memory>

#include "Dungeon/Dungeon.h"
#include "Player/Player.h"

class Game {
private:
    Dungeon& dungeon;
    size_t current_level = 0;
    std::weak_ptr<Player> player;
public:
    //! @todo Перемещение персонажа между уровнями (обновление текущего уровня)
    //! @todo Смерть персонажа

    Game();
    void loadGameConfigs();

    void Start();
    void Update();
    void End();
};
#endif //LAB3_GAME_H
