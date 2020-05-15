#include "Game.h"

#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000

void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");

    std::string title = "None";
    sf::VideoMode window_bounds(SCREEN_HIGH, SCREEN_WIDTH);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    
    if (ifs.is_open()){
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();

	this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}
void Game::initStates()
{
    this->states.push(new Game(this->window());
}
Game::Game() { 
    this->initWindow();
    this->initStates();
}
Game::~Game() {
	delete this->window;

    while (this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}


//Functions

void Game::updateDt()
{
    //Update
    this->dt = this->dtClock.restart().asSeconds();
    system("clear");
    std::cout << this->dt << "\n";
}

void Game::updateEvents()
{
  
        while (this->window->pollEvent(this->sfEvent))
        { 
            if (this->sfEvent.type == sf::Event::Closed)
                this->window->close();
        }
  
}

void Game::update()
{
    this->updateEvents();

    if (!this->states.empty()) {
        this->states.top()->update(this->dt);
    }
}

void Game::render()
{
        this->window->clear();
        if (!this->states.empty()) {
            this->states.top()->render(this->window);
        }

        this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }

}