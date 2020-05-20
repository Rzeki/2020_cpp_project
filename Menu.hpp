#ifndef MENU_CLASS
#define MENU_CLASS
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#define MAX 4

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &startup);
    void MoveUP();
    void MoveDown();
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text text[MAX];

};



#endif