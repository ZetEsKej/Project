// main.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

//#include <SFML/Graphics.hpp>
#include <vector>
//#include <iostream>
#include "lifebar.cpp"
#include <math.h>
#include <string>

using namespace sf;

unsigned int Ant::counter = 0;		// licznik mrówek obecnych na mapie
unsigned int Ant::globalCounter = 0;		// licznik wszystkich mrówek, które kiedykolwiek zosta³y stworzone
int Ant::cost[] = { 20, 35, 50, 75, 95, 120 };		// koszt zakupu mrówki na poszczególnych poziomach

int main() {

	VideoMode vm(1920, 1080);   //Tworzenie objektu videomode - tworzenie ekranu
	RenderWindow window(vm, "Age Of Ants");  //Tworzenie i otwarcie okienka gry

	View view = window.getDefaultView(); //Kamera 2D
	int boundaryControl = 0;  // kontrola wyjezdzania kamery za ekran

	Texture textureBackground; //Przygotowanie tekstury tla
	textureBackground.loadFromFile("graphics/backgrounds/background_blue_B.png"); //Za³adowanie tekstury t³a
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
	Text playersMoney("100", font);				// tekst z pieniêdzmi gracza
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

	std::vector<Ant*> ants;	// tablica z wszystkimi mrówkami
	std::vector<Lifebar*> antsLifebars;

	std::vector<Ant*> opponents;	// tablica z wrogimi mrówkami
	std::vector<Lifebar*> opponentsLifebars;


	bool drawAnt = false;
	float addMoney = 0.0;			// wartoœæ do liczenia czasu (player dostaje dodatkowe jaja co jakiœ czas)

	// Pêtla gry (game loop)

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

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {		// pauzowanie gry po wciœniêciu klawisza ESC
				if (!isGamePaused)
					isGamePaused = true;
				else
					isGamePaused = false;
			}



			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {	// klikniêcie LPM

				auto mouse_pos = Mouse::getPosition(window); // pozcja myszki wzglêdem okna
				auto translated_pos = window.mapPixelToCoords(mouse_pos); // pozycja myszki w koordynatach globalnych

				if (addAntButton_1.getGlobalBounds().contains(translated_pos)) { // porównanie koordynatów myszki z koordynatami przycisku dodawania mrówek -> czy wyst¹pi³o klikniêcie na przycisk addAnt

					drawAnt = true;
					if (player->money >= Ant::cost[0]) {		// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l1(player));		// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[0]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, 147, 66));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						//std::cout << "Nasze jaja: " << player->money << std::endl;
						//std::cout << opponentPlayer->money << std::endl;

						opponents.push_back(new Ant_l1(opponentPlayer));		// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[0]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, 147, 66));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_2.getGlobalBounds().contains(translated_pos)) {	// drugi przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[1]) {		// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l2(player));		// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[1]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l2(opponentPlayer));		// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[1]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_3.getGlobalBounds().contains(translated_pos)) {	// trzeci przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[2]) {		// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l3(player));		// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[2]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l3(opponentPlayer));		// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[2]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_4.getGlobalBounds().contains(translated_pos)) {	// czwarty przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[3]) {		// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l4(player));		// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[3]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l4(opponentPlayer));		// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[3]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_5.getGlobalBounds().contains(translated_pos)) {	// piaty przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[2]) {		// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l5(player));		// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[4]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l5(opponentPlayer));		// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[4]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_6.getGlobalBounds().contains(translated_pos)) {	// szosty przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[5]) {		// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l6(player));		// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[5]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));

						/*std::cout << "Nasze jaja: " << player->money << std::endl;
						std::cout << opponentPlayer->money << std::endl;*/

						opponents.push_back(new Ant_l6(opponentPlayer));		// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[5]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}


			}

		}

		//Aktualizacja sceny - Update Scene

		if (!isGamePaused) {				// czy gra zosa³a spauzowana 

			addMoney += 0.01;
			if (addMoney > 50) {					// player dostaje dodatkowe dziesiêæ jaj co dziesiêæ sekund
				player->money += 10;
				std::cout << player->money << std::endl;
				addMoney = 0.0;
			}

			Ant::checkForDead(ants, antsLifebars, opponentsLifebars, opponents, player, opponentPlayer);		// zobacz, czy s¹ jakieœ martwe mrówki do usuniêcia z mapy

			playersMoney.setString(std::to_string(player->money));

			if (drawAnt == true) {

				for (int i = 0; i < opponents.size(); i++) {
					opponents[i]->isMoving = opponents[i]->checkForCollision(ants, opponents, ourCastle);
					if (opponents[i]->isMoving == true) {
						opponents[i]->sprite.setTextureRect(IntRect(floor(opponents[i]->walkingCounter) * opponents[i]->width, 0, opponents[i]->width, opponents[i]->height));
						opponents[i]->move();
					}
					else {	// zaatakuj przeciwnika
						if (i == 0) {			// jest to najstarsza mrówka - tylko ona mo¿e spotkaæ przeciwnika
							if (!ants.empty()) {	// sprawdzenie, czy spotka³a przeciwnika, czy jego zamek
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
						if (i == 0) {			// jest to najstarsza mrówka - tylko ona mo¿e spotkaæ przeciwnika
							if (!opponents.empty()) {	// sprawdzenie, czy spotka³a przeciwnika, czy jego zamek
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

		window.draw(addAntButton_1);		// te trzy mrówki gracz mo¿e zakupiæ od samego pocz¹tku gry
		window.draw(addAntButton_2);
		window.draw(addAntButton_3);
		window.draw(addAntButton_4);
		window.draw(addAntButton_5);
		window.draw(addAntButton_6);

		//if (ourCastle->level >= 2) {			// te dwa ify sprawdzaj¹, czy zamek gracza ma odpowiedni poziom, aby móg³ zakupiæ inne mrówki
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
				window.draw(ants[i]->sprite); //Rysowanie mrówek
				window.draw(antsLifebars[i]->rect);
				//window.draw(ants[i]->rect); //Rysowanie kolizji mrówek
			}
			for (int i = 0; i < opponents.size(); i++) {
				window.draw(opponents[i]->sprite); //Rysowanie mrówek
				window.draw(opponentsLifebars[i]->rect);
				//window.draw(opponents[i]->rect); //Rysowanie kolizji mrówek
			}
		}

		window.display(); //Pokaz wszystko, co narysowaliœmy
	}


	return 0;
}