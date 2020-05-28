#ifndef GAME_CLASS
#define GAME_CLASS
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <string.h>
#include <iostream>

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
    int p_sum[5];
    int p_hp[5];
    int kosc1;
    int kosc2;
    int current_p_index;
    int bufor_przegranych;
    sf::Sprite s_kosc1;
    sf::Sprite s_kosc2;
    sf::Texture t_kosc1;
    sf::Texture t_kosc2;
    int przegrany;
    int suma_przegranego;
    int bufor;
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
    int rolldices(int kosc1, int kosc2,sf::Sprite & s_kosc1,sf::Sprite & s_kosc2, sf::Texture & t_kosc1, sf::Texture & t_kosc2);
    void drawdices(sf::Sprite k1, sf::Sprite k2);

};






#endif