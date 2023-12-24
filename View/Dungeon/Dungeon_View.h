#ifndef LAB3_DUNGEON_VIEW_H
#define LAB3_DUNGEON_VIEW_H

#include <SFML/Graphics.hpp>
#include <Dungeon/Dungeon.h>

class Dungeon_View : public sf::Drawable, public sf::Transformable {
protected:
    Dungeon& d;
    sf::Window& window;
public:
    Dungeon_View(Dungeon& d, sf::Window&);
    sf::Vector2f getSize() const;
    std::pair<size_t, size_t> getFieldByCoord(sf::Vector2f) const;
    void Init();
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //LAB3_DUNGEON_VIEW_H
