// main.cpp : Ten plik zawiera funkcj� �main�. W nim rozpoczyna si� i ko�czy wykonywanie programu.
//

//#include <SFML/Graphics.hpp>
#include <vector>
//#include <iostream>
#include "lifebar.cpp"
#include <math.h>
#include <string>

using namespace sf;

unsigned int Ant::counter = 0;		// licznik mr�wek obecnych na mapie
unsigned int Ant::globalCounter = 0;		// licznik wszystkich mr�wek, kt�re kiedykolwiek zosta�y stworzone
int Ant::cost[] = { 20, 35, 50, 75, 95, 120 };		// koszt zakupu mr�wki na poszczeg�lnych poziomach

int main() {

	VideoMode vm(1920, 1080);   //Tworzenie objektu videomode - tworzenie ekranu
	RenderWindow window(vm, "Age Of Ants");  //Tworzenie i otwarcie okienka gry

	View view = window.getDefaultView(); //Kamera 2D
	int boundaryControl = 0;  // kontrola wyjezdzania kamery za ekran

	Texture textureBackground; //Przygotowanie tekstury tla
	textureBackground.loadFromFile("graphics/backgrounds/background_blue_B.png"); //Za�adowanie tekstury t�a
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	Texture textureEggs;
	textureEggs.loadFromFile("graphics/UI/jajco.png");
	Sprite spriteEggs;
	spriteEggs.setTexture(textureEggs);
	spriteEggs.setPosition(50, 54);

	Font font;									// czcionka
	font.loadFromFile("graphics/LEMONMILK-Medium.otf");
	Text playersMoney("100", font);				// tekst z pieni�dzmi gracza
	playersMoney.setCharacterSize(30);
	playersMoney.setStyle(sf::Text::Bold);
	playersMoney.setFillColor(sf::Color::White);
	playersMoney.setOutlineThickness(2);
	playersMoney.setOutlineColor(sf::Color::Black);
	playersMoney.setPosition(85, 50);

	Texture textureAdd_1;
	textureAdd_1.loadFromFile("graphics/UI/UI_1.png");
	Texture textureAdd_2;
	textureAdd_2.loadFromFile("graphics/UI/UI_2.png");
	Texture textureAdd_3;
	textureAdd_3.loadFromFile("graphics/UI/UI_3.png");
	Texture textureAdd_4;
	textureAdd_4.loadFromFile("graphics/UI/UI_4.png");
	Texture textureAdd_5;
	textureAdd_5.loadFromFile("graphics/UI/UI_5.png");
	Texture textureAdd_6;
	textureAdd_6.loadFromFile("graphics/UI/UI_6.png");

	Sprite addAntButton_1;
	addAntButton_1.setTexture(textureAdd_1);
	addAntButton_1.setPosition(50, 90);

	Sprite addAntButton_2;
	addAntButton_2.setTexture(textureAdd_2);
	addAntButton_2.setPosition(130, 90);

	Sprite addAntButton_3;
	addAntButton_3.setTexture(textureAdd_3);
	addAntButton_3.setPosition(210, 90);

	Sprite addAntButton_4;
	addAntButton_4.setTexture(textureAdd_4);
	addAntButton_4.setPosition(290, 90);

	Sprite addAntButton_5;
	addAntButton_5.setTexture(textureAdd_5);
	addAntButton_5.setPosition(370, 90);

	Sprite addAntButton_6;
	addAntButton_6.setTexture(textureAdd_6);
	addAntButton_6.setPosition(450, 90);

	Texture textureAnt[8]; 	//Tworzenie tekstur mrowek
	textureAnt[0].loadFromFile("graphics/animations/ant_ani_1.png");
	textureAnt[1].loadFromFile("graphics/animations/ant_ani_2.png");
	textureAnt[2].loadFromFile("graphics/animations/ant_ani_3.png");
	textureAnt[3].loadFromFile("graphics/animations/ant_ani_4.png");
	textureAnt[4].loadFromFile("graphics/animations/ant_ani_5.png");
	textureAnt[5].loadFromFile("graphics/animations/ant_ani_6.png");

	Player* player = new Player(true);
	Player* opponentPlayer = new Player(false);

	Castle* opponentsCastle = new Castle(false);
	Castle* ourCastle = new Castle(true);

	bool isGamePaused = false;

	std::vector<Ant*> ants;	// tablica z wszystkimi mr�wkami
	std::vector<Lifebar*> antsLifebars;

	std::vector<Ant*> opponents;	// tablica z wrogimi mr�wkami
	std::vector<Lifebar*> opponentsLifebars;


	bool drawAnt = false;
	float addMoney = 0.0;			// warto�� do liczenia czasu (player dostaje dodatkowe jaja co jaki� czas)

	// P�tla gry (game loop)

	while (window.isOpen()) {

		Clock clock;

		Event event;

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Left && boundaryControl > 0) || (event.type == Event::KeyPressed && event.key.code == Keyboard::A && boundaryControl > 0)) {
				view.move(-40.0f, 0.f); // predkosc przesuwania
				boundaryControl--;
				addAntButton_1.move(-40.0f, 0);
				addAntButton_2.move(-40.0f, 0);
				addAntButton_3.move(-40.0f, 0);
				addAntButton_4.move(-40.0f, 0);
				addAntButton_5.move(-40.0f, 0);
				addAntButton_6.move(-40.0f, 0);
				playersMoney.move(-40.0f, 0);
				spriteEggs.move(-40.0f, 0);
			}
			else if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Right && boundaryControl < 143) || (event.type == Event::KeyPressed && event.key.code == Keyboard::D && boundaryControl < 143)) {
				boundaryControl++;
				view.move(40.0f, 0.f); // predkosc przesuwania
				std::cout << boundaryControl << std::endl;
				addAntButton_1.move(40.0f, 0);
				addAntButton_2.move(40.0f, 0);
				addAntButton_3.move(40.0f, 0);
				addAntButton_4.move(40.0f, 0);
				addAntButton_5.move(40.0f, 0);
				addAntButton_6.move(40.0f, 0);
				playersMoney.move(40.0f, 0);
				spriteEggs.move(40.0f, 0);
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {		// pauzowanie gry po wci�ni�ciu klawisza ESC
				if (!isGamePaused)
					isGamePaused = true;
				else
					isGamePaused = false;
			}



			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {	// klikni�cie LPM

				auto mouse_pos = Mouse::getPosition(window); // pozcja myszki wzgl�dem okna
				auto translated_pos = window.mapPixelToCoords(mouse_pos); // pozycja myszki w koordynatach globalnych

				if (addAntButton_1.getGlobalBounds().contains(translated_pos)) { // por�wnanie koordynat�w myszki z koordynatami przycisku dodawania mr�wek -> czy wyst�pi�o klikni�cie na przycisk addAnt

					drawAnt = true;
					if (player->money >= Ant::cost[0]) {		// gracz ma wystarczaj�co du�o pieni�dzy, by kupi� mr�wk�
						ants.push_back(new Ant_l1(player));		// tworzenie mr�wki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[0]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, 147, 66));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						//std::cout << "Nasze jaja: " << player->money << std::endl;
						//std::cout << opponentPlayer->money << std::endl;

						opponents.push_back(new Ant_l1(opponentPlayer));		// tworzenie mr�wki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[0]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, 147, 66));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_2.getGlobalBounds().contains(translated_pos)) {	// drugi przycisk dodawania mr�wek

					drawAnt = true;
					if (player->money >= Ant::cost[1]) {		// gracz ma wystarczaj�co du�o pieni�dzy, by kupi� mr�wk�
						ants.push_back(new Ant_l2(player));		// tworzenie mr�wki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[1]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l2(opponentPlayer));		// tworzenie mr�wki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[1]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_3.getGlobalBounds().contains(translated_pos)) {	// trzeci przycisk dodawania mr�wek

					drawAnt = true;
					if (player->money >= Ant::cost[2]) {		// gracz ma wystarczaj�co du�o pieni�dzy, by kupi� mr�wk�
						ants.push_back(new Ant_l3(player));		// tworzenie mr�wki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[2]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l3(opponentPlayer));		// tworzenie mr�wki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[2]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_4.getGlobalBounds().contains(translated_pos)) {	// czwarty przycisk dodawania mr�wek

					drawAnt = true;
					if (player->money >= Ant::cost[3]) {		// gracz ma wystarczaj�co du�o pieni�dzy, by kupi� mr�wk�
						ants.push_back(new Ant_l4(player));		// tworzenie mr�wki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[3]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l4(opponentPlayer));		// tworzenie mr�wki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[3]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_5.getGlobalBounds().contains(translated_pos)) {	// piaty przycisk dodawania mr�wek

					drawAnt = true;
					if (player->money >= Ant::cost[2]) {		// gracz ma wystarczaj�co du�o pieni�dzy, by kupi� mr�wk�
						ants.push_back(new Ant_l5(player));		// tworzenie mr�wki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[4]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l5(opponentPlayer));		// tworzenie mr�wki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[4]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_6.getGlobalBounds().contains(translated_pos)) {	// szosty przycisk dodawania mr�wek

					drawAnt = true;
					if (player->money >= Ant::cost[5]) {		// gracz ma wystarczaj�co du�o pieni�dzy, by kupi� mr�wk�
						ants.push_back(new Ant_l6(player));		// tworzenie mr�wki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[5]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l6(opponentPlayer));		// tworzenie mr�wki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[5]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}


			}

		}

		//Aktualizacja sceny - Update Scene

		if (!isGamePaused) {				// czy gra zosa�a spauzowana 

			addMoney += 0.01;
			if (addMoney > 50) {					// player dostaje dodatkowe dziesi�� jaj co dziesi�� sekund
				player->money += 10;
				std::cout << player->money << std::endl;
				addMoney = 0.0;
			}

			Ant::checkForDead(ants, antsLifebars, opponentsLifebars, opponents, player, opponentPlayer);		// zobacz, czy s� jakie� martwe mr�wki do usuni�cia z mapy

			playersMoney.setString(std::to_string(player->money));

			if (drawAnt == true) {

				for (int i = 0; i < opponents.size(); i++) {
					opponents[i]->isMoving = opponents[i]->checkForCollision(ants, opponents, ourCastle);
					if (opponents[i]->isMoving == true) {
						opponents[i]->sprite.setTextureRect(IntRect(floor(opponents[i]->walkingCounter) * opponents[i]->width, 0, opponents[i]->width, opponents[i]->height));
						opponents[i]->move();
					}
					else {	// zaatakuj przeciwnika
						if (i == 0) {			// jest to najstarsza mr�wka - tylko ona mo�e spotka� przeciwnika
							if (!ants.empty()) {	// sprawdzenie, czy spotka�a przeciwnika, czy jego zamek
								opponents[i]->attackOpponent(ants[0]);
							}
						}
					}
					opponentsLifebars[i]->updateLifebar(opponents[i]);
				}
				for (int i = 0; i < ants.size(); i++) {
					ants[i]->isMoving = ants[i]->checkForCollision(ants, opponents, opponentsCastle);
					if (ants[i]->isMoving == true) {
						ants[i]->sprite.setTextureRect(IntRect(floor(ants[i]->walkingCounter) * ants[i]->width, 0, ants[i]->width, ants[i]->height));
						ants[i]->move();
					}
					else {	// zaatakuj przeciwnika
						if (i == 0) {			// jest to najstarsza mr�wka - tylko ona mo�e spotka� przeciwnika
							if (!opponents.empty()) {	// sprawdzenie, czy spotka�a przeciwnika, czy jego zamek
								ants[i]->attackOpponent(opponents[0]);
							}
							else {
								ants[i]->attackCastle(opponentsCastle);
							}
						}
					}
					antsLifebars[i]->updateLifebar(ants[i]);
				}

			}

		}

		window.setView(view);

		//Rysowanie sceny - Draw Scene

		window.clear(); //Usuniecie wszystkiego z ostatniego frame'a - czyszczenie sceny

		window.draw(spriteBackground);  //Rysowanie sceny gry

		window.draw(spriteEggs);		 // rysowanie UI
		window.draw(playersMoney);

		window.draw(addAntButton_1);		// te trzy mr�wki gracz mo�e zakupi� od samego pocz�tku gry
		window.draw(addAntButton_2);
		window.draw(addAntButton_3);
		window.draw(addAntButton_4);
		window.draw(addAntButton_5);
		window.draw(addAntButton_6);

		//if (ourCastle->level >= 2) {			// te dwa ify sprawdzaj�, czy zamek gracza ma odpowiedni poziom, aby m�g� zakupi� inne mr�wki
		//	window.draw(addAntButton_4);
		//	window.draw(addAntButton_5);
		//	window.draw(addAntButton_6);
		//}
		//if (ourCastle->level >= 3) {
		//	window.draw(addAntButton_7);
		//	window.draw(addAntButton_8);
		//}


		//window.draw(ourCastle->rect);
		//window.draw(opponentsCastle->rect);

		if (drawAnt == true) {
			for (int i = 0; i < ants.size(); i++) {
				window.draw(ants[i]->sprite); //Rysowanie mr�wek
				window.draw(antsLifebars[i]->rect);
				//window.draw(ants[i]->rect); //Rysowanie kolizji mr�wek
			}
			for (int i = 0; i < opponents.size(); i++) {
				window.draw(opponents[i]->sprite); //Rysowanie mr�wek
				window.draw(opponentsLifebars[i]->rect);
				//window.draw(opponents[i]->rect); //Rysowanie kolizji mr�wek
			}
		}

		window.display(); //Pokaz wszystko, co narysowali�my
	}


	return 0;
}