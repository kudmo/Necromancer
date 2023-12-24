//
// Created by mk on 20.12.23.
//

#include <iostream>
#include "AdminElements.h"


void AdminMenu::DoSelected() {
    auto& form = getForm();
    auto selected = form.getSelectedMenuNumber();
    auto mymenu = elements[selected];
    mymenu->setColorTextMenu(sf::Color::Red, sf::Color::Yellow, sf::Color::Transparent);

    mymenu->getForm().setPosition(form.getPosition() + sf::Vector2f(form.getSize().x, form.getMenuStep()*selected));
    mymenu->getForm().AlignMenu(0);
    mymenu->getForm().positionateTexts();

    while (window.isOpen())
    {
        sf::Event event_play;
        while (window.pollEvent(event_play))
        {
            try {
                mymenu->handleEvent(event_play);
            } catch (const close_menu_signal&) {
                return;
            }
        }
        window.clear();
        window.draw(this->getForm());
        window.draw(mymenu->getForm());
        window.display();
    }
    close();
}

AdminMenu::AdminMenu(sf::RenderWindow &window, float menux, float menuy,
                     const std::vector<std::string> &menuNamings,
                     const std::vector<MenuController *> &menuControllers,
                     int sizeFont, int step) :
            MenuController(window,menux,menuy, 0, menuNamings, sizeFont, step)
{
    elements = menuControllers;

}

