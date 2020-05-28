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
    this->current_p_index=0;
    this->bufor_przegranych=0;
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
    tlo.loadFromFile("game-assets/gra-tlo.png");
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
    this->drawdices(this->s_kosc1,this->s_kosc2);
    //koniec rysowania

    this->window->display();
    //wyswietlenie klatki
    
}

void Game::draw_players_stats(int buf)
{
    sf::Text text;
    sf::Text text1;
    sf::Font font;
    if(!font.loadFromFile("game-assets/arial.ttf"))
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
        if(this->event.type == sf::Event::KeyPressed)
        {
            if(this->event.key.code == sf::Keyboard::Space)
            {
                while(this->p_hp[this->current_p_index]==0)
                {
                    this->current_p_index++;
                }
                if(this->current_p_index==this->P_amount)
                {
                    this->przegrany=0;
                    this->suma_przegranego=13;
                    for(int i=0;i<this->P_amount;i++)
                    {
                        if(this->p_hp[i]!=0)
                        {
                            if(this->suma_przegranego>this->p_sum[i])
                            {
                                this->suma_przegranego=this->p_sum[i];
                                this->przegrany=i;
                            } 
                        }
                        
                    }
                    this->bufor=0;
                    for(int j=0;j<this->P_amount;j++)
                    {
                        if(this->p_hp[j]!=0)
                        {
                            if(this->p_sum[j]==this->suma_przegranego)
                            {
                                this->bufor++;
                            }
                        }
                        
                    }
                        if(this->bufor>1)
                        {
                          //remis    
                        }
                        if(this->bufor==1)
                        {
                            this->p_hp[przegrany]--;
                            this->bufor_przegranych=0;
                            for(int k=0;k<this->P_amount;k++)
                            {
                                if(p_hp[k]==0)
                                {
                                    this->bufor_przegranych++;
                                }
                            }
                            if(this->bufor_przegranych==(this->P_amount)-1)
                            {
                                for(int f=0;f<this->P_amount;f++)
                                {
                                    if(p_hp[f]!=0)
                                    {
                                        std::cout<<std::endl;
                                        std::cout<<"--------------WYGRAL GRACZ "<<f+1<<"---------------";
                                        std::cout<<std::endl;
                                        std::cout<<std::endl;
                                    }
                                }
                                this->window->close();
                            }
                        }    
                
                    for(int g=0;g<this->P_amount;g++)
                    {
                        this->p_sum[g]=0;
                    }
                    this->current_p_index=0;
                }
                if(this->p_hp[current_p_index]!=0)
                {
                    this->p_sum[current_p_index]=this->rolldices(kosc1,kosc2,this->s_kosc1,this->s_kosc2,this->t_kosc1,this->t_kosc2);
                }
                this->current_p_index++;
            }
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

int Game::rolldices(int kosc1,int kosc2, sf::Sprite & s_kosc1, sf::Sprite & s_kosc2 , sf::Texture & t_kosc1, sf::Texture & t_kosc2)
{
    s_kosc1.setPosition((rand()%101)+150,(rand()%101)+500);
    s_kosc2.setPosition((rand()%151)+350,(rand()%101)+500);
    s_kosc1.rotate((rand()%20)+1);
    s_kosc2.rotate((rand()%20)+1);
    
    kosc1=(rand()%6)+1;
    kosc2=(rand()%6)+1;
    switch(kosc1)
    {
        case 1:
        t_kosc1.loadFromFile("game-assets/1.png");
        break;
        case 2:
        t_kosc1.loadFromFile("game-assets/2.png");
        break;
        case 3:
        t_kosc1.loadFromFile("game-assets/3.png");
        break;
        case 4:
        t_kosc1.loadFromFile("game-assets/4.png");
        break;
        case 5:
        t_kosc1.loadFromFile("game-assets/5.png");
        break;
        case 6:
        t_kosc1.loadFromFile("game-assets/6.png");
        break;
    }
    switch(kosc2)
    {
        case 1:
        t_kosc2.loadFromFile("game-assets/1.png");
        break;
        case 2:
        t_kosc2.loadFromFile("game-assets/2.png");
        break;
        case 3:
        t_kosc2.loadFromFile("game-assets/3.png");
        break;
        case 4:
        t_kosc2.loadFromFile("game-assets/4.png");
        break;
        case 5:
        t_kosc2.loadFromFile("game-assets/5.png");
        break;
        case 6:
        t_kosc2.loadFromFile("game-assets/6.png");
        break;
    }
    s_kosc1.setTexture(t_kosc1);
    s_kosc2.setTexture(t_kosc2);

    return kosc2+kosc1;
    
}

void Game::drawdices(sf::Sprite k1, sf::Sprite k2)
{
    this->window->draw(k1);
    this->window->draw(k2);

}
