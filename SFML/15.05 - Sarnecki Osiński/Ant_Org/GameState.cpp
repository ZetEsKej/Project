#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) 
	: State(window)
{
	//
}

GameState::~GameState() {
	//
}

void GamesState::endState()
{
}

void GamesState::update(const float& dt)
{
	std::cout << "Hello!" << "\n";
}

void GamesState::render(sf::RenderTarget* target)
{
}
