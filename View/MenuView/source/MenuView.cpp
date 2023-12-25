#include <MenuView.h>
#include <iostream>

// метод настройки текстовых объектов пунктов игрового меню
void MenuView::setInitText(sf::Text& text, sf::String str, float xpos, float ypos) {
    text.setFont(font);                 // шрифт
    text.setFillColor(menu_text_color); // цвет
    text.setString(str);                // текст
    text.setCharacterSize(size_font);   // размер шрифта
    text.setPosition(xpos, ypos);       // координаты текстового объекта
    text.setOutlineThickness(3);        // толщина контура обводки текста
    text.setOutlineColor(border_color); // цвет контура обводки текста
}
// Выравнивание пунктов меню по левому по правому по центру
void MenuView::AlignMenu(int posx)
{
    float nullx = 0;
    for (int i = 0; i < max_menu; i++) {
        switch (posx)
        {
            case 0:
                nullx = 0; // выравнивание по правому краю от установленных координат
                break;
            case 1:
                nullx = mainMenu[i].getLocalBounds().width;  // по левому краю
                break;
            case 2:
                nullx = mainMenu[i].getLocalBounds().width / 2;  // по центру
                break;
        }
        mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
    }

}
// Конструктор
MenuView::MenuView(float menux, float menuy, std::vector<sf::String> menu_elements, int sizeFont, int step)
        : size_font(sizeFont), menu_Step(step)
{
    this->setPosition(menux,menuy);
    // Загрузка шрифта
    if (!font.loadFromFile("View/MenuView/font/Zlusa_font.ttf")) exit(32);
    max_menu = menu_elements.size();
    mainMenu.resize(max_menu);
    for (int i = 0, ypos = getPosition().y; i < max_menu; i++, ypos += menu_Step) {
        setInitText(mainMenu[i], menu_elements[i],getPosition().x, ypos);
        size_x = std::max(size_x, mainMenu[i].getGlobalBounds().width);
    }
    size_y = menu_Step * menu_elements.size();

    selectedMenuNumber = 0;
    mainMenu[selectedMenuNumber].setFillColor(chose_text_color);


}


void MenuView::positionateTexts() {
    for (int i = 0, ypos = getPosition().y; i < max_menu; i++, ypos += menu_Step) {
        mainMenu[i].setPosition(getPosition() + sf::Vector2f(0,ypos));
    }
}







void MenuView::setSelectedMenuNumber(int mainMenuSelected) {
    if (mainMenuSelected > max_menu || mainMenuSelected < 0)
        throw std::invalid_argument("Wrong number of menu");
    if (this->selectedMenuNumber == mainMenuSelected)
        return;

    mainMenu[mainMenuSelected].setFillColor(chose_text_color);
    mainMenu[this->selectedMenuNumber].setFillColor(menu_text_color);
    this->selectedMenuNumber = mainMenuSelected;
}

int MenuView::getSelectedMenuNumber() const {
    return selectedMenuNumber;
}

int MenuView::getMaxMenu() const {
    return max_menu;
}

sf::Vector2f MenuView::getSize() const {
    return {size_x,size_y};
}

// рисуем элементы меню в графическом окне
void MenuView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto p = parent;
    while (p) {
        target.draw(*p,states);
        p = p->parent;
    }
    for (int i = 0; i < max_menu; i++) {
        target.draw(mainMenu[i],states);
    }

}
// назначение цвета элементам пунктов меню
void MenuView::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
    menu_text_color = menColor;   // цвет пунктов меню
    chose_text_color = ChoColor; // цвет выбраного пункта меню
    border_color = BordColor;    // цвет контура пунктов меню

    for (int i = 0; i < max_menu; i++) {
        mainMenu[i].setFillColor(menu_text_color);
        mainMenu[i].setOutlineColor(border_color);
    }

    mainMenu[selectedMenuNumber].setFillColor(chose_text_color);
}

MenuView *MenuView::getParent() const {
    return parent;
}

void MenuView::setParent(MenuView &parent) {
    MenuView::parent = &parent;
}
