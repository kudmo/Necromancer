#include "Dungeon_View.h"
#include "Floor_View.h"

Dungeon_View::Dungeon_View(Dungeon &d,  sf::Window& window) : d(d), window(window) {}

void Dungeon_View::Init() {
}

void Dungeon_View::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto &current = d.floorByNumber(d.getCurrentLevel());
    auto current_view = Floor_View(current, window);
    current_view.setPosition(this->getPosition());
    current_view.draw(target, states);
}
