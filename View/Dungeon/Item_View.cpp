#include "Item_View.h"
#include <jsoncpp/json/json.h>
#include <iostream>

Item_View::Item_View(Item &item) : current(item) {}

void Item_View::Init() {}

void Item_View::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto info = current.getInfo();
    Json::Value json_info;
    Json::Reader reader;

    sf::Font font;
    font.loadFromFile("View/Dungeon/input_files/calibri.ttf");
    sf::Color color = sf::Color(200, 200, 200);
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
    text1.setString(naming);
    target.draw(text1, states);
}


