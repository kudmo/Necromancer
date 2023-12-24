#include "Entity_View.h"
#include <jsoncpp/json/json.h>
#include <iostream>

Entity_View::Entity_View(Entity &current): current(current) {
}

void Entity_View::Init() {

}

void Entity_View::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//    states.transform *= getTransform();
    if (current.isDead())
        return;
    auto info = current.getInfo();
    Json::Value json_info;
    Json::Reader reader;

    sf::Font font;
    font.loadFromFile("View/Dungeon/input_files/calibri.ttf");
    sf::Color color = sf::Color(100, 100, 200);
    sf::Text text1("", font, 12);

    bool parsingSuccessful = reader.parse(info, json_info );
    if ( !parsingSuccessful )
        std::cout << "Error parsing the string: " << info << std::endl;

    auto type = json_info["type"].asString();
    auto naming = json_info["naming"].asString();

    text1.setFillColor(color);
    text1.setFillColor(color);
    sf::Vector2f position(10.0f, 25.0f);

    text1.setPosition(this->getPosition()+position);
    if (current.isAttacking()) {
        naming += "\n[attack]";
    } else if (current.isMoving()) {
        naming += "\n[move]";
    }
    if  (current.isDammaged()) {
        naming+= "\n[damaged]";
    }
    text1.setString(naming);
    target.draw(text1, states);

/*
        sf::Image image;
        image.loadFromFile(std::string("View/Dungeon/sprites/") + type + "/" + naming + ".jpg");
        sf::Texture texture;
        texture.loadFromImage(image);

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(FIELD_SIZE/sprite.getLocalBounds().width, FIELD_SIZE/sprite.getLocalBounds().height);
        sprite.setPosition(FIELD_SIZE * e->getCoordinates().first, FIELD_SIZE * e->getCoordinates().second);
        target.draw(sprite);*/
}
