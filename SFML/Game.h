#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000
class Game
{
private: 
	//Vars
	//Background!
	std::map<std::string, Button*> buttons;
	//Init 
	void initWindow();
	void initBackground();
	void initVars();
	void initFonts();
	void initButtons();
protected: 
	sf::Texture bgTexture;
	sf::RectangleShape background;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	sf::Event sfEvent;


public:

	//Cons/Dest

	Game();
	virtual ~Game();

	//Functions
	void update_evenets();
	void update();
	void render();
	void run();
};

