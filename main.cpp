#include <iostream>
#include "GameClass.hpp"


int main()
{
    Game game;


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
}
