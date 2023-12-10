#ifndef LAB3_ITEM_VIEW_H
#define LAB3_ITEM_VIEW_H

#include <SFML/Graphics.hpp>
#include <Item/Item.h>

class Item_View : public sf::Drawable, public sf::Transformable{
protected:
    Item& current;
public:
    explicit Item_View(Item& item);
    void Init();
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //LAB3_ITEM_VIEW_H
