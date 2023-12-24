#include "Dungeon_View.h"
#include "Floor_View.h"

Dungeon_View::Dungeon_View(Dungeon &d,  sf::Window& window) : d(d), window(window) {}

void Dungeon_View::Init() {
}

void Dungeon_View::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto &current = d.getFloorByNumber(d.getCurrentFloorNumber());
    auto current_view = Floor_View(current, window);
    current_view.setPosition(this->getPosition());
    current_view.draw(target, states);
}

std::pair<size_t, size_t> Dungeon_View::getFieldByCoord(sf::Vector2f pos) const {
    pos = pos - this->getPosition();
    return std::make_pair<size_t>(static_cast<size_t>(pos.x/FIELD_SIZE), static_cast<size_t>(pos.y/FIELD_SIZE));
}

sf::Vector2f Dungeon_View::getSize() const {
    return sf::Vector2f();
}
