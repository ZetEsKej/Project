#pragma once
#include <SFML\Graphics.hpp>
#define Max_main_menu 5
class Main_menu
{
private:
	int mainMenuSelected;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];
	sf::Text text;
public:
	Main_menu(float width, float hight);

	void draw(sf::RenderWindow& window);
	void moveUP();
	void moveDOWN();

	int mainMenuPressed() {
		return mainMenuSelected;
	}
	~Main_menu();
};

