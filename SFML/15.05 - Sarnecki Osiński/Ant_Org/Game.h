#pragma once
/*#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Game.cpp"*/
#include "GameState.h"
#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000
class Game
{
private:
	//V
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock; 
	float dt; //Delta time

	std::stack<State*> states;
	//Init
	void initWindow();
	void initStates();
public:
	Game();
	virtual ~Game();

	//Functions
	void updateDt();
	void updateEvents();
	void update();
	void render();
	void run();
};

