#ifndef GAME_CLASS
#define GAME_CLASS
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class Game
{
private:
    //OKNO
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;

    //Prywatne funkcje
    void initVariables();
    void initWindow();

public:
    Game(); //konstruktor
    ~Game(); //dekonstruktor   

    //AKCESORY
    const bool getWindowIsOpen() const;

    //METODY
    void pollEvent();
    void update();
    void render();
};



#endif