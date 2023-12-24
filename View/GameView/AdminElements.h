#ifndef LAB3_ADMINELEMENTS_H
#define LAB3_ADMINELEMENTS_H

#include <SFML/Graphics.hpp>
#include "MenuController.h"

class AdminMenu : public MenuController {
private:
    std::vector<MenuController*> elements;
public:
    AdminMenu(sf::RenderWindow &window,
              float menux, float menuy,
              const std::vector<std::string> &menuNamings,
              const std::vector<MenuController*> &menuControllers,
              int sizeFont, int step);

    void DoSelected() override;
    ~AdminMenu() {
        for (auto &i : elements)
            delete i;
    }
};


#endif //LAB3_ADMINELEMENTS_H
