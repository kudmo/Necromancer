#include <iostream>
#include "GameView.h"

GameView::GameView(Player&p, Floor &curr, sf::RenderWindow &window): window(window) {
    floorView = new Floor_View(curr,window);
    playerInfoView = new PlayerInfoView(p, window);
}

void GameView::Init() {
    floorView->Init();
    floorView->setRightDown(std::make_pair<size_t,size_t>(10,10));
}

GameView::~GameView() {
    delete floorView;
    delete playerInfoView;
}

void GameView::setFloor(Floor &floor) {
    if (&floorView->getFloor() == &floor)
        return;
    delete floorView;
    floorView = new Floor_View(floor,window);
    floorView->Init();
    floorView->setRightDown(std::make_pair<size_t,size_t>(10,10));
}

void GameView::setLeftUpOfFloor(std::pair<size_t, size_t> left_up) {
    floorView->setLeftUp(left_up);
}

void GameView::setRightDownOfFloor(std::pair<size_t, size_t> right_down) {
    floorView->setRightDown(right_down);
}

void GameView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    floorView->setPosition(this->getPosition() + sf::Vector2f(5,5));
    playerInfoView->setPosition(this->getPosition() + sf::Vector2f(FIELD_SIZE*10,0) + sf::Vector2f(50,5));
    target.draw(*floorView, states);
    target.draw(*playerInfoView, states);
    if (curr) {
        curr->setPosition(this->getPosition() + sf::Vector2f(FIELD_SIZE*10,0) + sf::Vector2f(50, 100));
        curr->positionateTexts();
        target.draw(*curr, states);
    }
}

void GameView::addAdminMenu(MenuView &mv) {
    removeUpperAdminMenu();
    curr = &mv;

}

void GameView::removeUpperAdminMenu() {
    curr = nullptr;
}

