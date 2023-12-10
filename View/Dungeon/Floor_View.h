#ifndef LAB3_FLOOR_VIEW_H
#define LAB3_FLOOR_VIEW_H
#include <SFML/Graphics.hpp>
#include <Floor/Floor.h>

#define FIELD_SIZE 100.0

class Floor_View : public sf::Drawable, public sf::Transformable {
protected:
    Floor& current;
    sf::Window& window;
public:
    Floor_View(Floor& current, sf::Window&);
    void Init();
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //LAB3_FLOOR_VIEW_H
