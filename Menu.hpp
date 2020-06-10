#ifndef MENU_CLASS
#define MENU_CLASS
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>

#define MAX 4

class Game; //uprzedzenia klasy Menu ze istnieje klasa game z ktorej wezmiemy obiekt do funkcji zaprzyjaznionej

class Menu
{
public:
    int Player_amount; //liczba graczy ktora nastepnie przekazywana jest przez funkcje zaprzyjazniona do klasy Game

    friend void getpamount(Menu menu,Game &game); //deklaracja przyjazni

    Menu(float width, float height); //konstruktor pobierajacy wysokosc i szerokosc okna
    ~Menu() = default; //dekonstruktor domyslny, poniewaz nic nie usuwa w tej klasie

    void draw(sf::RenderWindow &startup); //rysowanie okna
    void MoveUP();  //funkcja ktora przesuwa wybierany element w menu w gore
    void MoveDown(); //j.w tylko w dol
private:
    int selectedItemIndex; //wybrany indeks 
    sf::Font font; //czcionka tekstu w menu
    sf::Text text[MAX]; //tablica tekstow do wyswietlania liczby graczy i napisu u gory

};

#endif