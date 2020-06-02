#include "Menu.hpp"

Menu::Menu(float width, float height)  //konstruktor menu
{
    Player_amount=2;
    if(!font.loadFromFile("game-assets/Charming.otf"))
    {
        perror("Blad wczytywania czcionki");  //obsluga bledu odczytu czcionki
        exit(-1);
    }
//-----------------------------------------------Inicjalizacja tekstu---------------------------------------------------
    text[0].setFont(font); //ustawienie czcionki
    text[0].setFillColor(sf::Color::White); //ustawienie koloru
    text[0].setStyle(sf::Text::Bold); //pogrubienie tekstu
    text[0].setString("Wybierz liczbe graczy"); // ustawienie tekstu 
    text[0].setPosition(sf::Vector2f(140,360)); // w tym przypadku kazdy napis bedzie osobno

    text[1].setFont(font); //ustawienie czcionki
    text[1].setFillColor(sf::Color::Red); //ustawienie koloru
    text[1].setString("2"); // ustawienie tekstu 
    text[1].setPosition(sf::Vector2f(295,450)); 

    text[2].setFont(font); //ustawienie czcionki
    text[2].setFillColor(sf::Color::White); //ustawienie koloru
    text[2].setString("3"); // ustawienie tekstu 
    text[2].setPosition(sf::Vector2f(295,530));

    text[3].setFont(font); //ustawienie czcionki
    text[3].setFillColor(sf::Color::White); //ustawienie koloru
    text[3].setString("4"); // ustawienie tekstu 
    text[3].setPosition(sf::Vector2f(295,610));     //nie uzaleznialem tego od szerokosci okna, poniewaz wymiary sa stale

    selectedItemIndex=1;
}


void Menu::draw(sf::RenderWindow &startup)
{
    std::array<int,4> values = {0,1,2,3}; //STL array szablon klasy do ktorego wstawiam int zeby przechowywal wartosci indeksow ktore bede wyswietlal
    for(int v : values)                   //w petli zakresowej for
    {
        startup.draw(text[v]);       //petla zakresowa wyswietlajaca tekst w menu
    }

}

void Menu::MoveUP()
{
    if(selectedItemIndex-1>0)
    {
        text[selectedItemIndex].setFillColor(sf::Color::White);// zmiana obecnego koloru tekstu na bialy
        selectedItemIndex--; //zmniejszenie indeksu
        text[selectedItemIndex].setFillColor(sf::Color::Red); //ustawienie wybranego elementu na czerwony
    }
}
void Menu::MoveDown()
{
    if(selectedItemIndex+1<=MAX-1)
    {
        text[selectedItemIndex].setFillColor(sf::Color::White); //j.w
        selectedItemIndex++;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
