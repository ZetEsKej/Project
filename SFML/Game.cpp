#include "Game.h"
#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000

//Static


//Init
void Game::initButtons() {
    this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50
        & this->font, "New Game",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_HIGH, SCREEN_WIDTH), "Age of Ants");

}

void Game::initBackground()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
    if (!this->bgTexture.loadFromFile("tlo.jpg")) {
        throw"ERROR::MAIN_MENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }
    this->background.setTexture(&this->bgTexture);
}


void Game::initVars()
{
}

void Game::initFonts()
{
}

void Game::initButtons()
{
}

//Const/Dest
Game::Game() {
    this->initWindow();
}

Game::~Game() {
	delete this->window;
}


//Functions


void Game::update_evenets()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}
void Game::update()
{
    this->update_evenets();
}

void Game::render()
{
    this->window->clear();
    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}



