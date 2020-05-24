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
    this->videoMode.height=800;
    this->videoMode.width=800;
    this->window = new sf::RenderWindow(this->videoMode, "DICES",sf::Style::Titlebar | sf::Style::Close); //inicjalizowanie glownego okna gry
    this->window->setFramerateLimit(60);
}

void Game::update()
{
    this->pollEvent();
    
}

void Game::render()
{
    sf::Texture tlo;
    tlo.loadFromFile("gra-tlo.png");
    sf::Sprite sprite1;
    sf::Vector2u size = tlo.getSize();
    sprite1.setTexture(tlo);
    sprite1.setOrigin(0,0);

    //odswiezanie
    this->window->clear(sf::Color::Red);

    //rysowanie
    this->window->draw(sprite1); //tlo
    this->cover(P_amount);
    this->draw_players_stats(P_amount);
    //koniec rysowania

    this->window->display();
    //wyswietlenie klatki
    
}

void Game::draw_players_stats(int buf)
{
    sf::Text text;
    sf::Text text1;
    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
    {
        perror("Blad wczytywania czcionki");  //obsluga bledu odczytu czcionki
        exit(-1);
    }
    text.setFont(font);
    text1.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(45);
    text1.setCharacterSize(45);
    text1.setStyle(sf::Text::Bold);
    text.setStyle(sf::Text::Bold);
    text1.setFillColor(sf::Color::Black);
    std::string s,f;
    for(int i=0;i<buf;i++)
    {
        s=std::to_string(p_hp[i]);
        f=std::to_string(p_sum[i]);
        text.setString(f);
        text1.setString(s);
        text.setPosition(sf::Vector2f(230+(i*160),150));
        text1.setPosition(sf::Vector2f(230+(i*160),270));
        this->window->draw(text);
        this->window->draw(text1);
    }
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

void Game::get_pamount(int a)
{
    this->P_amount = a;
}

void Game::cover(int a)
{
    sf::RectangleShape cover1;
    cover1.setFillColor(sf::Color(98,85,82));
    if(a==2)
    {
        cover1.setSize(sf::Vector2f(320.f,360.f));
        cover1.setPosition(sf::Vector2f(480.f,0.f));
        this->window->draw(cover1);
    }
    else if(a==3)
    {
        cover1.setSize(sf::Vector2f(160.f,360.f));
        cover1.setPosition(sf::Vector2f(640.f,0.f));
        this->window->draw(cover1);
    }

}

void Game::prepare_players(int buf)
{
    for(int i=0; i<buf; i++)
    {
        p_hp[i]=6;
        p_sum[i]=0;
    }
}

