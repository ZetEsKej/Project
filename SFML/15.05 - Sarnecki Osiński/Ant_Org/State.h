#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include "Game.cpp"
#include <vector>

class state
{
private:
	sf::RenderWindow* window; 
	std::vector<sf::Texture> textures; 
public:
	state(sf::RenderWindow* window);
	virtual ~state();
	virtual void endState() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif 