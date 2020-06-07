#include "Main_menu.h"
#include <SFML\Graphics.hpp>
#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000
Main_menu::Main_menu(float width, float hight) {
	sf::Text text; 
	
	//sf::FloatRect textRect = text.getLocalBounds();
	if(!font.loadFromFile("arial.ttf")){}

	//play
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Red);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(40);
	mainMenu[0].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, (SCREEN_HIGH / 2)-200));

	//center text - do prawej strony, zeby zadzialalo, trzeba zakomentowac wszystkie setPosition i odkomentowac ta zawartosc + sf::FloatRect textRect 
	/*mainMenu[0].setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	mainMenu[1].setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	mainMenu[2].setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	mainMenu[3].setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	mainMenu[4].setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);*/

    //Settings
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::Red);
	mainMenu[1].setString("Settings");
	mainMenu[1].setCharacterSize(40);
	mainMenu[1].setPosition(sf::Vector2f((SCREEN_WIDTH / 2)-35, (SCREEN_HIGH /2)-125));

	//Credits
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::Red);
	mainMenu[2].setString("Credits");
	mainMenu[2].setCharacterSize(40);
	mainMenu[2].setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - 25, (SCREEN_HIGH / 2) - 50));

	//Exit
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color::Red);
	mainMenu[3].setString("Exit");
	mainMenu[3].setCharacterSize(40);
	mainMenu[3].setPosition(sf::Vector2f((SCREEN_WIDTH / 2) + 5, (SCREEN_HIGH /2)+25));


	//Anthill
	mainMenu[4].setFont(font);
	mainMenu[4].setString("ANTHILL");
	mainMenu[4].setCharacterSize(80);
	mainMenu[4].setFillColor(sf::Color::Red);
	mainMenu[4].setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - 115, (SCREEN_HIGH / 2) - 400));

	//Simulator 
	mainMenu[5].setFont(font);
	mainMenu[5].setString("SIMULATOR");
	mainMenu[5].setCharacterSize(40);
	mainMenu[5].setFillColor(sf::Color::Red);
	mainMenu[5].setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - 75, (SCREEN_HIGH / 2) - 300));

	mainMenuSelected = 0;
}
Main_menu::~Main_menu() {
	
}
void Main_menu::draw(sf::RenderWindow& window) {
	for (int i = 0; i <= 5; i++) {
		window.draw(mainMenu[i]);
	}
}

void Main_menu::moveDOWN() {
	if (mainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[mainMenuSelected].setFillColor(sf::Color::White);
		mainMenuSelected++;
		if (mainMenuSelected == 4) {
			mainMenuSelected = 0;
		}
		mainMenu[mainMenuSelected].setFillColor(sf::Color::Red);
	}
}

void Main_menu::moveUP() {
	if (mainMenuSelected - 1 >= -1) {
		mainMenu[mainMenuSelected].setFillColor(sf::Color::White);
		mainMenuSelected--;
		if (mainMenuSelected == -1) {
			mainMenuSelected = 3;
		}
		mainMenu[mainMenuSelected].setFillColor(sf::Color::Red);
	}
}