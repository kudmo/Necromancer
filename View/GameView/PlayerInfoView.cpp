#include "PlayerInfoView.h"

PlayerInfoView::PlayerInfoView(Player &player, sf::RenderWindow &window) : player(player), window(window) {
    font.loadFromFile("View/GameView/input_files/Zlusa_font.ttf");
}

void PlayerInfoView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    #define box_size 200

    sf::Text health_text, mana_text, essence_text, experience_text;
    health_text.setFont(font);
    health_text.setString(std::string("HP{") + std::to_string(player.getCurrentHP()) + " / " + std::to_string(player.getMaxHP()) + "} : ");
    health_text.setFillColor(sf::Color::White);
    health_text.setOutlineColor(sf::Color::White);
    health_text.setCharacterSize(32);

    mana_text.setFont(font);
    mana_text.setString(std::string("MP{") + std::to_string(player.getCurrentMP()) + " / " + std::to_string(player.getMaxMP()) + "} : ");
    mana_text.setFillColor(sf::Color::White);
    mana_text.setOutlineColor(sf::Color::White);
    mana_text.setCharacterSize(32);

    essence_text.setFont(font);
    essence_text.setString(std::string("Essence {") + std::to_string(player.getEssenceCount()) +" / 50}");
    essence_text.setFillColor(sf::Color::White);
    essence_text.setOutlineColor(sf::Color::White);
    essence_text.setCharacterSize(32);

    experience_text.setFont(font);
    experience_text.setString(std::string("Lvl - " + std::to_string(player.getLevel())) + "{" + std::to_string(player.getExperience()) +" / 100}");
    experience_text.setFillColor(sf::Color::White);
    experience_text.setOutlineColor(sf::Color::White);
    experience_text.setCharacterSize(32);

    health_text.setPosition(this->getPosition());
    mana_text.setPosition(this->getPosition() + sf::Vector2f(0, 40));
    experience_text.setPosition(this->getPosition() + sf::Vector2f(0, 2*40));
    essence_text.setPosition(this->getPosition() + sf::Vector2f(0, 3*40));


    sf::RectangleShape health_box, mana_box, experience_box,health_container, mana_container, experience_container;

    health_box.setFillColor(sf::Color::Red);
    health_box.setSize(sf::Vector2f((box_size * static_cast<float>(player.getCurrentHP())) / player.getMaxHP(), 36));
    health_box.setPosition(this->getPosition() + sf::Vector2f(200, 0));
    health_container.setPosition(this->getPosition() + sf::Vector2f(200, 0));
    health_container.setSize(sf::Vector2f(box_size, 36));
    health_container.setOutlineThickness(2.f);
    health_container.setFillColor(sf::Color::Transparent);
    health_container.setOutlineColor(sf::Color::White);

    mana_box.setFillColor(sf::Color::Blue);
    mana_box.setSize(sf::Vector2f((box_size * static_cast<float>(player.getCurrentMP()))/player.getMaxMP(), 36));
    mana_box.setPosition(this->getPosition() + sf::Vector2f(200, 40));
    mana_container.setPosition(this->getPosition() + sf::Vector2f(200, 40));
    mana_container.setSize(sf::Vector2f(box_size, 36));
    mana_container.setOutlineThickness(2.f);
    mana_container.setFillColor(sf::Color::Transparent);
    mana_container.setOutlineColor(sf::Color::White);

    experience_box.setFillColor(sf::Color::Green);
    experience_box.setSize(sf::Vector2f((box_size * static_cast<float>(player.getExperience()))/100, 36));
    experience_box.setPosition(this->getPosition() + sf::Vector2f(200, 2*40));
    experience_container.setPosition(this->getPosition() + sf::Vector2f(200, 2*40));
    experience_container.setSize(sf::Vector2f(box_size, 36));
    experience_container.setOutlineThickness(2.f);
    experience_container.setFillColor(sf::Color::Transparent);
    experience_container.setOutlineColor(sf::Color::White);

    target.draw(health_text, states);
    target.draw(mana_text, states);
    target.draw(essence_text, states);
    target.draw(experience_text, states);

    target.draw(health_box, states);
    target.draw(mana_box, states);
    target.draw(experience_box, states);

    target.draw(health_container,states);
    target.draw(mana_container,states);
    target.draw(experience_container,states);
}
