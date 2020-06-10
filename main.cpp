#include <iostream>
#include "GameClass.hpp"
#include "Menu.hpp"

void getpamount(Menu menu,Game &game)
{
    game.P_amount=menu.Player_amount;  //funkcja zaprzyjazniona przekazujaca liczbe graczy z jednej klasy do drugiej (pobiera obiekty klas)
}

int main()
{   
    //---------------------------------------------MENU----------------------------------------------------(nie tworzylem wskaznika na okno menu, poniewaz szybko sie zamyka, a plynnosci potrzeba grze)
    sf::RenderWindow startup(sf::VideoMode(600,800),"DICES - Options",sf::Style::Close | sf::Style::Titlebar);
    Menu menu(startup.getSize().x,startup.getSize().y);
    sf::Texture texture;
    if(!texture.loadFromFile("game-assets/tlo.png"))
    {
        perror("Blad wczytywania tla");  //obsluga bledu odczytu tla
        exit(-1);
    }
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
                    menu.MoveUP(); //poruszanie strzalka w gore w menu
                    menu.Player_amount--;
                }
                if(event.key.code == sf::Keyboard::Down)
                {
                    menu.MoveDown(); //poruszanie strzalka w dol w menu
                    menu.Player_amount++;
                }
                if(event.key.code == sf::Keyboard::Return)
                {
                    startup.close();  //wcisniecie enter
                }
            }
        }
        startup.clear(); //odswiezanie klatki
        startup.draw(sprite); //rysowanie tla
        menu.draw(startup); //rysowanie tekstu
        startup.display(); // wyswietlenie
    }
//--------------------------------------------------------------------------------------------------
//-----------------------GRA-------------------------------------------------------------------------
    Game game;
    srand(time(NULL));
    getpamount(menu,game);
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
