#ifndef LAB3_GAMEVIEW_H
#define LAB3_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <Floor_View.h>
#include <Floor/Floor.h>
#include "AdminElements.h"
#include "PlayerInfoView.h"

class GameView  : public sf::Drawable, public sf::Transformable{
private:
    Floor_View *floorView;
    PlayerInfoView *playerInfoView;
    MenuView *curr = nullptr;
    sf::RenderWindow& window;
public:
    GameView(Player& p, Floor& curr, sf::RenderWindow&);
    void Init();
    MenuView *getAdminMenu() {return curr;}
    Floor_View *getFloorView() {return floorView;}

    void setFloor(Floor& floor);
    void setLeftUpOfFloor(std::pair<size_t, size_t> left_up);
    void setRightDownOfFloor(std::pair<size_t, size_t> right_down);
    void addAdminMenu(MenuView&);
    void removeUpperAdminMenu();

    ~GameView();
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //LAB3_GAMEVIEW_H
