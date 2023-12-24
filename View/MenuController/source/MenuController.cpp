#include <MenuController.h>
#include <iostream>

MenuController::~MenuController() {
    delete form;
}

void MenuController::MoveUp() {
    auto curr = form->getSelectedMenuNumber();
    auto max = form->getMaxMenu();
    curr = (curr - 1 + max ) % max;
    form->setSelectedMenuNumber(curr);
}

void MenuController::MoveDown() {
    auto curr = form->getSelectedMenuNumber();
    auto max = form->getMaxMenu();
    curr = (curr + 1) % max;
    form->setSelectedMenuNumber(curr);
}

void MenuController::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor) {
    form->setColorTextMenu(menColor, ChoColor, BordColor);
}

void MenuController::alignMenu(int align_pos) {
    form->AlignMenu(align_pos);
}

MenuController::MenuController(sf::RenderWindow &window, float menux, float menuy, int align_pos,
                               std::vector<std::string> menu_elements, int sizeFont, int step): window(window) {
    std::vector<sf::String> m;
    m.reserve(menu_elements.size());
    for (auto &i : menu_elements) {
        m.emplace_back(i);
    }
    form = new MenuView(/*sf::RenderWindow& window,*/  menux, menuy, m, sizeFont , step);
    form->AlignMenu(align_pos);
}

void MenuController::handleEvent(sf::Event event) {
//    if (event.type == sf::Event::Resized) {
//        form->setPosition(window.mapPixelToCoords(sf::Vector2i{form->getPosition()}));
//    }

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Escape) { close(); }
        if (event.key.code == sf::Keyboard::Up) { MoveUp(); }
        if (event.key.code == sf::Keyboard::Down) { MoveDown(); }
        if (event.key.code == sf::Keyboard::Return) { DoSelected(); }
    }
}

MenuController *MenuController::getParent() const {
    return parent;
}

void MenuController::setParent(MenuController &parent) {
    MenuController::parent = &parent;
}
