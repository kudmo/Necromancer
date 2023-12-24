#ifndef LAB3_PLAYERINFOVIEW_H
#define LAB3_PLAYERINFOVIEW_H

#include <SFML/Graphics.hpp>
#include "Player/Player.h"

class PlayerInfoView : public sf::Drawable, public sf::Transformable{
private:
    Player& player;
    sf::RenderWindow& window;
    sf::Font font;
public:
    PlayerInfoView(Player &player, sf::RenderWindow &window);

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //LAB3_PLAYERINFOVIEW_H
