#include "GameClass.hpp"

//KONSTRUKTOR
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

//DEKONSTRUKTOR
Game::~Game()
{
    delete this->window;
}

void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height=720;
    this->videoMode.width=720;
    this->window = new sf::RenderWindow(this->videoMode, "DICES",sf::Style::Titlebar | sf::Style::Close); //inicjalizowanie glownego okna gry
}

void Game::update()
{
    this->pollEvent();
    
}
void Game::render()
{
    this->window->clear();

    //rysowanie obiektow gry
    
}

void Game::pollEvent()
{
    //petla eventow
    while(this->window->pollEvent(this->event))
    {
        if(this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}