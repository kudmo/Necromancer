#ifndef LAB3_FLOOR_VIEW_H
#define LAB3_FLOOR_VIEW_H
#include <SFML/Graphics.hpp>
#include <Floor/Floor.h>

#define FIELD_SIZE 100.0

class Floor_View : public sf::Drawable, public sf::Transformable {
protected:
    Floor& current;
    sf::Window& window;
    sf::Font font;
    std::pair<size_t, size_t> left_up_drawing;
    std::pair<size_t, size_t> right_down_drawing;
public:
    Floor_View(Floor& current, sf::Window&);
    Floor& getFloor() {return current;}
    void setLeftUp(std::pair<size_t, size_t> left_up);
    void setRightDown(std::pair<size_t, size_t> right_down);
    std::pair<size_t, size_t> getFieldByCoord(sf::Vector2f) const;
    void Init();
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //LAB3_FLOOR_VIEW_H
