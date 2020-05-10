#include "ageofants.h"

//Funkcje statyczne

//Funkcje initalizatorskie

void ageofants::initwindow()
{
	this-> okno = new sf::RenderWindow(sf::VideoMode(720, 720), "Age of ants v.0.1");
}

//Konstruktory i Destruktory

ageofants::ageofants()
{
    this->initwindow();
}

ageofants::~ageofants()
{
	delete this->okno;
}

void ageofants::updatedt()
{
    //aktualizuje zmienn¹ deltaczs, czasem który zajmuje wyrederowanie jednej klatki
    this->deltaczas = this->deltaZegar.restart().asSeconds();

    system("cls");
    std::cout << this->deltaczas << "\n";
}

//funkcje

void ageofants::updateSFMLevents()
{
 
        while (this->okno->pollEvent(this->zdarzenie))
        {
            if (this->zdarzenie.type == sf::Event::Closed)
                this->okno->close();
        }
   
}

void ageofants::update()
{
    this->updateSFMLevents();
}

void ageofants::render()
{
    this->okno->clear();

    //Render itemy

    this->okno->display();
}

void ageofants::run()
{
    while (this->okno->isOpen())
	{
        this->updatedt();
		this->update();
		this->render();
    }
}

