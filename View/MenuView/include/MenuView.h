#ifndef LAB3_MENUVIEW_H
#define LAB3_MENUVIEW_H

#include <SFML/Graphics.hpp>
#include <vector>


class MenuView : public sf::Drawable, public sf::Transformable  {
private:
    MenuView *parent = nullptr;
    float size_x;
    float size_y;
    int menu_Step;
    int max_menu;
    int size_font;
    int selectedMenuNumber;

    sf::Font font;

    std::vector<sf::Text> mainMenu;

    sf::Color menu_text_color = sf::Color::White;
    sf::Color chose_text_color = sf::Color::Yellow;
    sf::Color border_color = sf::Color::Black;

    void setInitText(sf::Text& text, sf::String str, float xpos, float ypos);

//    sf::RenderWindow& mywindow;
public:
//    sf::RenderWindow& getWindow() {return mywindow;}
    MenuView(float menux, float menuy, std::vector<sf::String> menu_elements, int sizeFont = 60, int step = 80);

    MenuView *getParent() const;

    void setParent(MenuView &parent);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
                          sf::Color BordColor);
    sf::Vector2f getSize() const;
    int getMenuStep() const {return menu_Step;}
    void positionateTexts();
    void AlignMenu(int posx);
    void setSelectedMenuNumber(int selectedMenuNumber);
    int getSelectedMenuNumber() const;

    int getMaxMenu() const;

};


#endif //LAB3_MENUVIEW_H
