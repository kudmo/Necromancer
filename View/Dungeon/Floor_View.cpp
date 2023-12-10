#include "Floor_View.h"
#include <Floor/Floor.h>
#include <jsoncpp/json/json.h>
#include <iostream>

#include "Entity_View.h"
#include "Item_View.h"

Floor_View::Floor_View(Floor &current , sf::Window& window)  : current(current), window(window) {}

void Floor_View::Init() {
}

void Floor_View::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto size = current.getSize();

    sf::Font font;
    font.loadFromFile("View/Dungeon/input_files/calibri.ttf");

    // Рисуем рамку игрового поля
    states.transform *= getTransform();
    sf::Color color = sf::Color(200, 100, 200);

    sf::RectangleShape shape(sf::Vector2f(size.first * FIELD_SIZE + 2, size.second * FIELD_SIZE + 2));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(sf::Color::Transparent);
    target.draw(shape, states);

    // Подготавливаем рамку для отрисовки всех плашек
    shape.setSize(sf::Vector2f(FIELD_SIZE * 0.9f, FIELD_SIZE * 0.9f));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(sf::Color::Transparent);
    sf::Text text("", font, 22);

    Json::Reader reader;
    for (size_t y = 0; y < size.second; ++y) {
        for (size_t x = 0; x < size.first; ++x) {
            color = sf::Color(200, 100, 200);


            auto &field = current.getByCoord(x,y);
            auto info = field.getInfo();

            Json::Value json_info;
            bool parsingSuccessful = reader.parse(info, json_info );
            if ( !parsingSuccessful )
                std::cout << "Error parsing the string: " << info << std::endl;

//            sf::Image image;
            auto spec = json_info["specialization"]["type"].asString();
            auto cov = json_info["coverage"]["type"].asString();

            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

            sf::Vector2f position(x * FIELD_SIZE, y * FIELD_SIZE);
            if (this->getPosition().x + position.x <= mouse_pos.x && mouse_pos.x <= this->getPosition().x + position.x + FIELD_SIZE * 0.9f &&
                    this->getPosition().y +position.y <= mouse_pos.y && mouse_pos.y <= this->getPosition().y +position.y + FIELD_SIZE * 0.9f) {
                color = sf::Color(200, 100, 100);
            }
            shape.setPosition(this->getPosition() + position);

            shape.setOutlineColor(color);
            text.setFillColor(color);




            if (spec != "no") {
                text.setString(spec);
            } else if (cov != "no") {
                text.setString(cov);
            } else {
                text.setString("");
            }

/*            sf::Texture texture;
            texture.loadFromImage(image);

            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(FIELD_SIZE/sprite.getLocalBounds().width, FIELD_SIZE/sprite.getLocalBounds().height);
            sprite.setPosition(FIELD_SIZE * x, FIELD_SIZE * y);
            target.draw(sprite);*/
            auto items = field.getItems();
            for (auto &i : items) {
                auto curr = Item_View(i);
                curr.setPosition(position);
                target.draw(curr, states);
            }
            text.setPosition(position.x + 20.0f, position.y  + FIELD_SIZE/2-10.f);
            target.draw(shape, states);
            target.draw(text, states);
        }
    }



    auto &entities = current.getEntities();
    for (auto &entity : entities) {
        auto e = entity.lock();
        auto e_view = Entity_View(*e);
        sf::Vector2f position(FIELD_SIZE * e->getCoordinates().first, FIELD_SIZE * e->getCoordinates().second);
        e_view.setPosition(this->getPosition() + position);
        target.draw(e_view);

    }
}

