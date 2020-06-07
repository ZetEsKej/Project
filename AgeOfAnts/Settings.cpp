/*#include "Settings.h"
#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000
Settings::Settings(float width, float hight) {
	if(!font.loadFromFile("arial.ttf")){}

	mainSett[0].setFont(font);
	mainSett[0].setFillColor(sf::Color::Red);
	mainSett[0].setString("Zmien tlo");
	mainSett[0].setCharacterSize(40);
	mainSett[0].setPosition(sf::Vector2f(SCREEN_WIDTH / 2, (SCREEN_HIGH / 2) - 200));
	
	int mainSettSelected = 0;
}
Settings::~Settings() {

}

void Settings::drawSett(sf::RenderWindow& window) {
	for (int i = 0; i < 3; i++) {
		window.draw(mainSett[i]);
	}
}
void Settings::movedownSett() {
	if (mainSettSelected + 1 <= Max_Sett) {
		mainSett[mainSettSelected].setFillColor(sf::Color::White);
		mainSettSelected++;
		if (mainSettSelected == 4) {
			mainSettSelected = 0;
		}
		mainSett[mainSettSelected].setFillColor(sf::Color::Red);
	}
}
void Settings::moveupSett() {
	if (mainSettSelected - 1 >= -1) {
		mainSett[mainSettSelected].setFillColor(sf::Color::White);
		mainSettSelected--;
		if (mainSettSelected == -1) {
			mainSettSelected = 3;
		}
		mainSett[mainSettSelected].setFillColor(sf::Color::Red);
	}
}
*/