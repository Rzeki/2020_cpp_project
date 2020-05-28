#include <iostream>
#include "GameClass.hpp"
#include "Menu.hpp"

int Player_amount=2;

int main()
{   
    sf::RenderWindow startup(sf::VideoMode(600,800),"DICES - Options",sf::Style::Close | sf::Style::Titlebar);
    Menu menu(startup.getSize().x,startup.getSize().y);
    sf::Texture texture;
    texture.loadFromFile("game-assets/tlo.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(0,0);
    
    while(startup.isOpen())
    {
        sf::Event event;
        while(startup.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                exit(0);   // przy wyjsciu z gry przez zamkniecie gra nie uruchomi sie dalej
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Up)
                {
                    menu.MoveUP();
                    Player_amount--;
                }
                if(event.key.code == sf::Keyboard::Down)
                {
                    menu.MoveDown();
                    Player_amount++;
                }
                if(event.key.code == sf::Keyboard::Return)
                {
                    startup.close();
                }
            }
        }
        startup.clear();
        startup.draw(sprite);
        menu.draw(startup);
        startup.display();
    }
//-----------------------GRA-------------------------------------------------------------------------
    Game game;
    srand(time(NULL));
    game.get_pamount(Player_amount);
    game.prepare_players(game.P_amount);
//PETLA GRY
    while (game.getWindowIsOpen())
    {
        //Odswiezanie obrazu
        game.update();
        //Wyswietlanie obrazu
        game.render();
    }
//KONIEC PETLI
    return 0;
//--------------------------------------------------------------------------------------------------------
}
