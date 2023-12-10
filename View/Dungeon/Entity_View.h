#ifndef LAB3_ENTITY_VIEW_H
#define LAB3_ENTITY_VIEW_H

#include <SFML/Graphics.hpp>
#include <Entity/Entity.h>

class Entity_View  : public sf::Drawable, public sf::Transformable  {
protected:
    Entity& current;
public:
    explicit Entity_View(Entity& current);
    void Init();
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //LAB3_ENTITY_VIEW_H
