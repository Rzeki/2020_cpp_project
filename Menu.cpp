#include "Menu.hpp"

Menu::Menu(float width, float height)  //konstruktor menu
{
    if(!font.loadFromFile("Charming.otf"))
    {
        perror("Blad wczytywania czcionki");  //obsluga bledu odczytu czcionki
        exit(-1);
    }

    text[0].setFont(font); //ustawienie czcionki
    text[0].setFillColor(sf::Color::White); //ustawienie koloru
    text[0].setStyle(sf::Text::Bold); //pogrubienie tekstu
    text[0].setString("Wybierz liczbe graczy"); // ustawienie tekstu 
    text[0].setPosition(sf::Vector2f(140,360)); // w tym przypadku kazdy napis bedzie osobno

    text[1].setFont(font); //ustawienie czcionki
    text[1].setFillColor(sf::Color::Red); //ustawienie koloru
    text[1].setString("2"); // ustawienie tekstu 
    text[1].setPosition(sf::Vector2f(295,450)); // w tym przypadku kazdy napis bedzie osobno

    text[2].setFont(font); //ustawienie czcionki
    text[2].setFillColor(sf::Color::White); //ustawienie koloru
    text[2].setString("3"); // ustawienie tekstu 
    text[2].setPosition(sf::Vector2f(295,530)); // w tym przypadku kazdy napis bedzie osobno

    text[3].setFont(font); //ustawienie czcionki
    text[3].setFillColor(sf::Color::White); //ustawienie koloru
    text[3].setString("4"); // ustawienie tekstu 
    text[3].setPosition(sf::Vector2f(295,610)); // w tym przypadku kazdy napis bedzie osobno

    selectedItemIndex=1;
}

Menu::~Menu() //dekonstruktor menu
{

}

void Menu::draw(sf::RenderWindow &startup)
{
    std::vector<int> values = {0,1,2,3};
    for(int v : values)
    {
        startup.draw(text[v]);       //petla zakresowa
    }

}

void Menu::MoveUP()
{
    if(selectedItemIndex-1>0)
    {
        text[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
void Menu::MoveDown()
{
    if(selectedItemIndex+1<=MAX-1)
    {
        text[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
