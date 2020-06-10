#include "GameClass.hpp"

//KONSTRUKTOR klasy Game
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

//DEKONSTRUKTOR klasy Game
Game::~Game()
{
    delete this->window;
}

//inicjalizacja zmiennych 
void Game::initVariables()
{
    this->window = nullptr;
    this->current_p_index=0;
    this->bufor_przegranych=0;
}

//inicjalizacja zmiennych okna
void Game::initWindow()
{
    this->videoMode.height=800;
    this->videoMode.width=800;
    this->window = new sf::RenderWindow(this->videoMode, "DICES",sf::Style::Titlebar | sf::Style::Close); //inicjalizowanie glownego okna gry
    this->window->setFramerateLimit(60);
}

//sprawdzanie eventow
void Game::update()
{
    this->pollEvent();
}

//renderowanie na ekranie
void Game::render()
{
    sf::Texture tlo;
    if(!tlo.loadFromFile("game-assets/gra-tlo.png"))
    {
        perror("error loading game assets (gra-tlo.png)");
        exit(-1);
    }
    sf::Sprite sprite1; //sprite odpowiadajacy za tlo gry
    sf::Vector2u size = tlo.getSize(); //dostosowanie rozmiaru do okna
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
                //Logika gry --------------------------------------------------------------------------------------------------------
                while(this->p_hp[this->current_p_index]==0) //pomijanie gracza z zerowym zyciem
                {
                    this->current_p_index++;
                }
                if(this->current_p_index==this->P_amount) //sprawdzanie czy nastapilo zakonczenie rundy
                {
                    this->przegrany=0; //zerowanie indeksu przegranego gracza
                    this->suma_przegranego=13; //ustawianie na najwieksza mozliwa liczbe do wyrzucenie z 2 kosci (+1) zeby miec pewnosc ze znajdziemy minimum
                    for(int i=0;i<this->P_amount;i++) 
                    {
                        if(this->p_hp[i]!=0) //nie zliczanie punktow graczy ktorzy odpadli
                        {
                            if(this->suma_przegranego>this->p_sum[i]) // szukanie najmniejszego wyniku
                            {
                                this->suma_przegranego=this->p_sum[i]; //ustawianie sumy przegranego
                                this->przegrany=i; //oraz indeksu
                            } 
                        }
                        
                    }
                    // nie tworzylem warunku na to gdy jest remis, bo musialbym zostawiac pustego ifa, bez dodawania niczego gdy nastapi remis runda jest powtarzana
                    this->bufor=0; //zmienna bufor sprawdza czy przypadkiem najmniejszego wyniku nie posiadal jeszcze jeden gracz czyli czy nie nastapil remis
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
                        /*if(this->bufor>1)
                        {
                          //remis    
                        }
                        */
                        if(this->bufor==1) //jezeli przegrany jest jeden
                        {
                            this->p_hp[przegrany]--; //odjecie zycia
                            this->bufor_przegranych=0; //reset bufora ktory sprawdza liczbe przegranych graczy
                            for(int k=0;k<this->P_amount;k++)
                            {
                                if(p_hp[k]==0)
                                {
                                    this->bufor_przegranych++; //petla sprawdzajaca czy przypadkiem nie zostal ostatni (wygrany) gracz 
                                }
                            }
                            if(this->bufor_przegranych==(this->P_amount)-1) //sprawdzenie czy nie nastapil koniec gry
                            {
                                for(int f=0;f<this->P_amount;f++)
                                {
                                    if(p_hp[f]!=0) //szukanie gracza z niezerowym zyciem
                                    {
                                        std::cout<<std::endl;
                                        std::cout<<"--------------WYGRAL GRACZ "<<f+1<<"---------------";
                                        std::cout<<std::endl;
                                        std::cout<<std::endl;
                                    }
                                }
                                this->window->close(); //zamkniecie gry
                            }
                        }    
                
                    for(int g=0;g<this->P_amount;g++)
                    {
                        this->p_sum[g]=0; //zerowanie sum graczy przed nowa runda
                    }
                    this->current_p_index=0; //rozpoczecie nowej rundy
                }
                if(this->p_hp[current_p_index]!=0) //rzut koscmi tylko i wylacznie jezeli gracz ma wiecej niz 0 zyc
                {
                    this->p_sum[current_p_index]=this->rolldices(kosc1,kosc2,this->s_kosc1,this->s_kosc2,this->t_kosc1,this->t_kosc2);
                }
                this->current_p_index++;
                //--------------------------------------------------------------------------------------------------------------------------
            }
        }
    }
}

const bool Game::getWindowIsOpen() const //sprawdzenie czy okno jest otwarte
{
    return this->window->isOpen();
}


void Game::cover(int a) //zakrycie pol z wynikami odpowiedniej liczby graczy np. wybrano 2 graczy wiec zakryto pola gracza 3 i 4
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

void Game::prepare_players(int buf) //przygotowanie graczy do gry
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
    //funkcja ta odpowiada za losowanie liczb oraz laduje odpowiednie obrazki wyrzuconych kosci, pobiera oryginaly wartosci ktore nastepnie ustawia
    
    kosc1=R_number<int>(6); //uzycie szablonu wlasnej funkcji 
    kosc2=R_number<int>(6);
    switch(kosc1)
    {
        case 1:
        if(!t_kosc1.loadFromFile("game-assets/1.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 2:
        if(!t_kosc1.loadFromFile("game-assets/2.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 3:
        if(!t_kosc1.loadFromFile("game-assets/3.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 4:
        if(!t_kosc1.loadFromFile("game-assets/4.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 5:
        if(!t_kosc1.loadFromFile("game-assets/5.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 6:
        if(!t_kosc1.loadFromFile("game-assets/6.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
    }
    switch(kosc2)
    {
        case 1:
        if(!t_kosc2.loadFromFile("game-assets/1.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 2:
        if(!t_kosc2.loadFromFile("game-assets/2.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 3:
        if(!t_kosc2.loadFromFile("game-assets/3.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 4:
        if(!t_kosc2.loadFromFile("game-assets/4.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 5:
        if(!t_kosc2.loadFromFile("game-assets/5.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
        case 6:
        if(!t_kosc2.loadFromFile("game-assets/6.png"))
        {
            perror("dice image error");
            exit(-1);
        }
        break;
    }
    s_kosc1.setTexture(t_kosc1);
    s_kosc2.setTexture(t_kosc2);

    return kosc2+kosc1; //funkcja zwraca sume kosci
    
}

void Game::drawdices(sf::Sprite k1, sf::Sprite k2)
{
    this->window->draw(k1);
    this->window->draw(k2);

}

template <typename S>
S R_number (S a)
{
    return (S)rand()%a + 1; //szablon funkcji ktora losuje liczby z zakresu od 1 do a;
}
