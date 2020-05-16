#include "Main_menu.h"
#include <SFML\Graphics.hpp>
Main_menu::Main_menu(float width, float hight) {
	//Font - trzeba załadować
	//if(!font.loadFromFile("arial.ttf")){}

	//Tło - trzeba załadować
	//if(!texture.loadFromFile("...")

	//play
	mainMenu[0].setFont(font);
	mainMenu[0].setColor(sf::Color::Blue);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(40);
	mainMenu[0].setPosition(sf::Vector2f(width / 2, hight / (Max_main_menu + 1)));

	//Settings
	mainMenu[1].setFont(font);
	mainMenu[1].setColor(sf::Color::White);
	mainMenu[1].setString("Settings");
	mainMenu[1].setCharacterSize(40);
	mainMenu[1].setPosition(sf::Vector2f(width / 2 -50, hight / (Max_main_menu + 1)*2));

	//Exit
	mainMenu[2].setFont(font);
	mainMenu[2].setColor(sf::Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(40);
	mainMenu[2].setPosition(sf::Vector2f(width / 2 -50, hight / (Max_main_menu + 1)*3));

	mainMenuSelected = 0;
}
Main_menu::~Main_menu() {

}

void Main_menu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < 3; i++) {
		window.draw(mainMenu[i]);
	}
}
void Main_menu::moveDOWN() {
	if (mainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[mainMenuSelected].setColor(sf::Color::White);
		mainMenuSelected++;
		if (mainMenuSelected == 3) {
			mainMenuSelected = 0;
		}
		mainMenu[mainMenuSelected].setColor(sf::Color::Blue);
	}
}
void Main_menu::moveUP() {
	if (mainMenuSelected - 1 >= -1) {
		mainMenu[mainMenuSelected].setColor(sf::Color::White);
		mainMenuSelected--;
		if (mainMenuSelected == -1) {
			mainMenuSelected = 2;
		}
		mainMenu[mainMenuSelected].setColor(sf::Color::Blue);
	}
}