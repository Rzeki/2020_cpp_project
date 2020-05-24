#ifndef GAME_CLASS
#define GAME_CLASS
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <string.h>

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
    int P_amount;
    int p_sum[4];
    int p_hp[4];
    Game(); //konstruktor
    ~Game(); //dekonstruktor   

    //AKCESORY
    const bool getWindowIsOpen() const;

    //METODY
    void pollEvent();
    void update();
    void render();
    void get_pamount(int a);
    void cover(int a);
    void prepare_players(int buf);
    void draw_players_stats(int buf);

};






#endif