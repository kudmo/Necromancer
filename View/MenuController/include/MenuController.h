#ifndef LAB3_MENUCONTROLLER_H
#define LAB3_MENUCONTROLLER_H

#include <SFML/Graphics.hpp>
#include <MenuView.h>
#include <vector>

class close_menu_signal : public std::exception {
public:
    close_menu_signal() = default;
};

class MenuController {
private:
    MenuView *form;
    MenuController* parent;
protected:
    sf::RenderWindow& window;
public:
    MenuController(sf::RenderWindow& window, float menux, float menuy, int align_pos, std::vector<std::string> menu_elements, int sizeFont = 60, int step = 80);

    MenuController *getParent() const;
    void setParent(MenuController &parent);

    MenuView& getForm() {return *form;}
    void MoveUp();
    void MoveDown();
    virtual void DoSelected() = 0;
    virtual void handleEvent(sf::Event);
    void close() {throw close_menu_signal();}
    void setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor);
    void alignMenu(int align_pos);
    virtual ~MenuController();
};


#endif //LAB3_MENUCONTROLLER_H
