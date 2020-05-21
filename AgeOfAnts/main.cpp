// main.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

//#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
//#include <iostream>
#include "lifebar.cpp"
#include <math.h>
#include <string>

using namespace sf;

unsigned int Ant::counter = 0;						// licznik mrówek obecnych na mapie
unsigned int Ant::globalCounter = 0;				// licznik wszystkich mrówek, które kiedykolwiek zosta³y stworzone
int Ant::cost[] = { 20, 35, 50, 75, 95, 120 };		// koszt zakupu mrówki na poszczególnych poziomach

int main() {

	/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- SEKCJA GRAFIKI -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

	VideoMode vm(1920, 1080);									//Tworzenie objektu videomode - tworzenie ekranu
	RenderWindow window(vm, "Age Of Ants");						//Tworzenie i otwarcie okienka gry

	window.setFramerateLimit(60);

	View view = window.getDefaultView();						//Kamera 2D
	int boundaryControl = 0;									// kontrola wyjezdzania kamery za ekran

	Texture textureBackground;									//Przygotowanie tekstury tla
	textureBackground.loadFromFile("graphics/backgrounds/background_blue_B.png"); //Za³adowanie tekstury t³a
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	Texture textureEggs;										// jajeczko przy walucie
	textureEggs.loadFromFile("graphics/UI/jajco.png");
	Sprite spriteEggs;
	spriteEggs.setTexture(textureEggs);
	spriteEggs.setPosition(50, 44);

	Font font;													// czcionka
	font.loadFromFile("graphics/LEMONMILK-Medium.otf");
	Text playersMoney("100", font);								// tekst z pieniêdzmi gracza
	playersMoney.setCharacterSize(30);
	playersMoney.setStyle(sf::Text::Bold);
	playersMoney.setFillColor(sf::Color::White);
	playersMoney.setOutlineThickness(2);
	playersMoney.setOutlineColor(sf::Color::Black);
	playersMoney.setPosition(85, 40);

	Text castleLevel("Castle level: 1", font);					// Tekst o poziomie zamku
	castleLevel.setCharacterSize(20);
	castleLevel.setStyle(sf::Text::Bold);
	castleLevel.setFillColor(sf::Color::White);
	castleLevel.setOutlineThickness(2);
	castleLevel.setOutlineColor(sf::Color::Black);
	castleLevel.setPosition(50, 180);

	Text textUpgrade("Upgrade castle", font);					// Tekst UPGRADE zamku
	textUpgrade.setCharacterSize(20);
	textUpgrade.setStyle(sf::Text::Bold);
	textUpgrade.setFillColor(sf::Color::White);
	textUpgrade.setOutlineThickness(2);
	textUpgrade.setOutlineColor(sf::Color::Black);
	textUpgrade.setPosition(904, 20);

	Text textMute("Mute", font);								// Tekst Mute
	textMute.setCharacterSize(20);
	textMute.setStyle(sf::Text::Bold);
	textMute.setFillColor(sf::Color::White);
	textMute.setOutlineThickness(2);
	textMute.setOutlineColor(sf::Color::Black);
	textMute.setPosition(1823, 105);

	Texture textureUpgrade1;									// Przyciski UPGRADE
	Texture textureUpgrade2;
	Texture textureUpgradeDis;
	textureUpgrade1.loadFromFile("graphics/UI/UI_zamek_1.png");
	textureUpgrade2.loadFromFile("graphics/UI/UI_zamek_2.png");
	textureUpgradeDis.loadFromFile("graphics/UI/UI_zamek_2_dis.png");
	Sprite spriteUpgrade;
	spriteUpgrade.setTexture(textureUpgrade1);
	spriteUpgrade.setPosition(960, 50);

	Texture textureMute;
	Texture textureUnmute;
	textureMute.loadFromFile("graphics/UI/UI_sound_on.png");
	textureUnmute.loadFromFile("graphics/UI/UI_sound_off.png");
	Sprite spriteMute;
	spriteMute.setTexture(textureMute);
	spriteMute.setPosition(1820, 50);

	Texture textureAdd_1;										// Enabled Przyciski
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
	Texture textureAdd_3_dis;									// Disabled przyciski
	textureAdd_3_dis.loadFromFile("graphics/UI/UI_3_dis.png");
	Texture textureAdd_4_dis;
	textureAdd_4_dis.loadFromFile("graphics/UI/UI_4_dis.png");
	Texture textureAdd_5_dis;
	textureAdd_5_dis.loadFromFile("graphics/UI/UI_5_dis.png");
	Texture textureAdd_6_dis;
	textureAdd_6_dis.loadFromFile("graphics/UI/UI_6_dis.png");

	Sprite addAntButton_1;
	addAntButton_1.setTexture(textureAdd_1);
	addAntButton_1.setPosition(50, 90);

	Sprite addAntButton_2;
	addAntButton_2.setTexture(textureAdd_2);
	addAntButton_2.setPosition(130, 90);

	Sprite addAntButton_3;
	addAntButton_3.setTexture(textureAdd_3_dis);
	addAntButton_3.setPosition(210, 90);

	Sprite addAntButton_4;
	addAntButton_4.setTexture(textureAdd_4_dis);
	addAntButton_4.setPosition(290, 90);

	Sprite addAntButton_5;
	addAntButton_5.setTexture(textureAdd_5_dis);
	addAntButton_5.setPosition(370, 90);

	Sprite addAntButton_6;
	addAntButton_6.setTexture(textureAdd_6_dis);
	addAntButton_6.setPosition(450, 90);

	Texture textureAnt[12]; 			//Tworzenie tekstur mrowek
	textureAnt[0].loadFromFile("graphics/animations/ant_ani_1.png");
	textureAnt[1].loadFromFile("graphics/animations/ant_ani_2.png");
	textureAnt[2].loadFromFile("graphics/animations/ant_ani_3.png");
	textureAnt[3].loadFromFile("graphics/animations/ant_ani_4.png");
	textureAnt[4].loadFromFile("graphics/animations/ant_ani_5.png");
	textureAnt[5].loadFromFile("graphics/animations/ant_ani_6.png");
	textureAnt[6].loadFromFile("graphics/enemy_animations/enemy_ani_1.png");
	textureAnt[7].loadFromFile("graphics/enemy_animations/enemy_ani_2.png");
	textureAnt[8].loadFromFile("graphics/enemy_animations/enemy_ani_3.png");
	textureAnt[9].loadFromFile("graphics/enemy_animations/enemy_ani_4.png");
	textureAnt[10].loadFromFile("graphics/enemy_animations/enemy_ani_5.png");
	textureAnt[11].loadFromFile("graphics/enemy_animations/enemy_ani_6.png");

	/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- SEKCJA AUDIO -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

	Music backgroundMusic;
	backgroundMusic.openFromFile("audio/backgroundMusic.wav");
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(30.f);

	//SoundBuffer hitBuffer;
	//hitBuffer.loadFromFile("audio/hitSound.wav");
	//Sound hitSound;
	//hitSound.setBuffer(hitBuffer);
	//hitSound.setLoop(true);
	//hitSound.setVolume(120.f);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("audio/deathSound.wav");
	Sound deathSound;
	deathSound.setBuffer(deathBuffer);
	deathSound.setVolume(120.f);
	Sound deathSound2;
	deathSound2.setBuffer(deathBuffer);
	deathSound2.setVolume(120.f);

	/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- SEKCJA ZMIENNYCH / TABLIC -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

	Clock clock;

	Castle* opponentsCastle = new Castle(false);
	Castle* ourCastle = new Castle(true);

	Player* player = new Player(true, ourCastle);
	Player* opponentPlayer = new Player(false, opponentsCastle);

	bool isGamePaused = false;
	bool isMuted = false;

	std::vector<Ant*> ants;			// tablica z wszystkimi mrówkami
	std::vector<Lifebar*> antsLifebars;

	std::vector<Ant*> opponents;	// tablica z wrogimi mrówkami
	std::vector<Lifebar*> opponentsLifebars;

	Lifebar* lifeBarCastle = new Lifebar(ourCastle);	//pasek zdrowia zamku gracza
	Lifebar* lifeBarOpponentCastle = new Lifebar(opponentsCastle);

	bool drawAnt = false;
	float addMoney = 0.0;			// wartoœæ do liczenia czasu (player dostaje dodatkowe jaja co jakiœ czas)

	/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- GAME LOOP -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

	backgroundMusic.play();

	while (window.isOpen()) {

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
				spriteUpgrade.move(-40.0f, 0);
				playersMoney.move(-40.0f, 0);
				textUpgrade.move(-40.0f, 0);
				castleLevel.move(-40.0f, 0);
				spriteMute.move(-40.0f, 0);
				spriteEggs.move(-40.0f, 0);
				textMute.move(-40.0f, 0);
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
				spriteUpgrade.move(40.0f, 0);
				playersMoney.move(40.0f, 0);
				textUpgrade.move(40.0f, 0);
				castleLevel.move(40.0f, 0);
				spriteMute.move(40.0f, 0);
				spriteEggs.move(40.0f, 0);
				textMute.move(40.0f, 0);
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {		// pauzowanie gry po wciœniêciu klawisza ESC
				if (!isGamePaused) {
					isGamePaused = true;
					backgroundMusic.pause();
				}
				else {
					isGamePaused = false;
					backgroundMusic.play();
				}
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {	// klikniêcie LPM

				auto mouse_pos = Mouse::getPosition(window);							// pozcja myszki wzglêdem okna
				auto translated_pos = window.mapPixelToCoords(mouse_pos);				// pozycja myszki w koordynatach globalnych

				if (addAntButton_1.getGlobalBounds().contains(translated_pos)) {		// porównanie koordynatów myszki z koordynatami przycisku dodawania mrówek -> czy wyst¹pi³o klikniêcie na przycisk addAnt

					drawAnt = true;
					if (player->money >= Ant::cost[0]) {								// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l1(player));								// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[0]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, 147, 66));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));


						opponents.push_back(new Ant_l1(opponentPlayer));				// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[6]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, 147, 66));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_2.getGlobalBounds().contains(translated_pos)) {	// drugi przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[1]) {								// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l2(player));								// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[1]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));


						opponents.push_back(new Ant_l2(opponentPlayer));				// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[7]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_3.getGlobalBounds().contains(translated_pos) && ourCastle->level >= 2) {	// trzeci przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[2]) {								// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l3(player));								// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[2]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));


						opponents.push_back(new Ant_l3(opponentPlayer));				// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[8]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_4.getGlobalBounds().contains(translated_pos) && ourCastle->level >= 2) {	// czwarty przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[3]) {								// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l4(player));								// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[3]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));


						opponents.push_back(new Ant_l4(opponentPlayer));				// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[9]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_5.getGlobalBounds().contains(translated_pos) && ourCastle->level == 3) {	// piaty przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[4]) {								// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l5(player));								// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[4]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));


						opponents.push_back(new Ant_l5(opponentPlayer));				// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[10]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (addAntButton_6.getGlobalBounds().contains(translated_pos) && ourCastle->level == 3) {	// szosty przycisk dodawania mrówek

					drawAnt = true;
					if (player->money >= Ant::cost[5]) {								// gracz ma wystarczaj¹co du¿o pieniêdzy, by kupiæ mrówkê
						ants.push_back(new Ant_l6(player));								// tworzenie mrówki
						ants[ants.size() - 1]->sprite.setTexture(textureAnt[5]);
						ants[ants.size() - 1]->sprite.setTextureRect(IntRect(0, 0, ants[ants.size() - 1]->width, ants[ants.size() - 1]->height));
						antsLifebars.push_back(new Lifebar(ants[ants.size() - 1]));


						opponents.push_back(new Ant_l6(opponentPlayer));				// tworzenie mrówki przeciwnika
						opponents[opponents.size() - 1]->sprite.setTexture(textureAnt[11]);
						opponents[opponents.size() - 1]->sprite.setTextureRect(IntRect(0, 0, opponents[opponents.size() - 1]->width, opponents[opponents.size() - 1]->height));
						opponentsLifebars.push_back(new Lifebar(opponents[opponents.size() - 1]));

					}
				}
				else if (spriteUpgrade.getGlobalBounds().contains(translated_pos) && ourCastle->level == 1 && player->money >= 1000) {	// przycisk Upgrade lvl 2
					ourCastle->level += 1;
					player->money -= 1000;
				}
				else if (spriteUpgrade.getGlobalBounds().contains(translated_pos) && ourCastle->level == 2 && player->money >= 2000) {	// przycisk Upgrade lvl 3
					ourCastle->level += 1;
					player->money -= 2000;
				}
				else if (spriteMute.getGlobalBounds().contains(translated_pos) && isMuted == false) {	// przycisk Mute
					backgroundMusic.setVolume(0.f);
					isMuted = true;
					textMute.move(-15, 0);
				}
				else if (spriteMute.getGlobalBounds().contains(translated_pos) && isMuted == true) {	// przycisk Mute
					backgroundMusic.setVolume(30.f);
					isMuted = false;
					textMute.move(15, 0);
				}

			}
			if (isMuted == true) {
				spriteMute.setTexture(textureUnmute);
				textMute.setString("Unmute");
			}
			if (isMuted == false) {
				spriteMute.setTexture(textureMute);
				textMute.setString("Mute");
			}

		}

		/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- SCENE UPDATE -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

		if (!isGamePaused) {						// czy gra zosa³a spauzowana 

			addMoney += 0.50;
			if (addMoney > 50) {					// player dostaje dodatkowe dziesiêæ jaj co dziesiêæ sekund
				player->money += 10;
				std::cout << player->money << std::endl;
				addMoney = 0.0;
			}

			bool PlayDeathSound = Ant::checkForDead(ants, antsLifebars, opponentsLifebars, opponents, player, opponentPlayer);		// zobacz, czy s¹ jakieœ martwe mrówki do usuniêcia z mapy
			if (PlayDeathSound == true) {
				deathSound.play();
			}

			playersMoney.setString(std::to_string(player->money));												// przypisanie do UI wartosci money z klasy player
			castleLevel.setString("Castle level: " + std::to_string(ourCastle->level));							// przypisanie do UI wartosci level z klasy Castle

			if (drawAnt == true) {

				for (int i = 0; i < opponents.size(); i++) {
					opponents[i]->isMoving = opponents[i]->checkForCollision(ants, opponents, ourCastle);
					if (opponents[i]->isMoving == true) {
						opponents[i]->sprite.setTextureRect(IntRect(floor(opponents[i]->walkingCounter) * opponents[i]->width, 0, opponents[i]->width, opponents[i]->height));
						opponents[i]->move();
					}
					else {							// zaatakuj przeciwnika
						//deathSound.play();
						if (i == 0) {				// jest to najstarsza mrówka - tylko ona mo¿e spotkaæ przeciwnika
							if (!ants.empty()) {	// sprawdzenie, czy spotka³a przeciwnika, czy jego zamek
								opponents[i]->attackOpponent(ants[0]);
							}
							else {
								opponents[i]->attackCastle(ourCastle);
							}
						}
					}
					opponentsLifebars[i]->updateLifebar(opponents[i]);
					lifeBarCastle->updateLifebar(ourCastle);
				}

				for (int i = 0; i < ants.size(); i++) {
					ants[i]->isMoving = ants[i]->checkForCollision(ants, opponents, opponentsCastle);
					if (ants[i]->isMoving == true) {
						ants[i]->sprite.setTextureRect(IntRect(floor(ants[i]->walkingCounter) * ants[i]->width, 0, ants[i]->width, ants[i]->height));
						ants[i]->move();
					}
					else {								// zaatakuj przeciwnika
						if (i == 0) {					// jest to najstarsza mrówka - tylko ona mo¿e spotkaæ przeciwnika
							if (!opponents.empty()) {	// sprawdzenie, czy spotka³a przeciwnika, czy jego zamek
								ants[i]->attackOpponent(opponents[0]);
							}
							else {
								ants[i]->attackCastle(opponentsCastle);
							}
						}
					}
					antsLifebars[i]->updateLifebar(ants[i]);
					lifeBarOpponentCastle->updateLifebar(opponentsCastle);
				}

			}

		}

		/* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- DRAW SCENE -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

		window.setView(view);

		Time time = clock.getElapsedTime();
		clock.restart().asSeconds();

		window.clear();						// Usuniecie wszystkiego z ostatniego frame'a - czyszczenie sceny

		window.draw(spriteBackground);		// Rysowanie sceny gry

		window.draw(spriteEggs);			// rysowanie UI
		window.draw(playersMoney);
		window.draw(castleLevel);
		window.draw(spriteMute);
		window.draw(textUpgrade);
		window.draw(textMute);

		window.draw(addAntButton_1);		// te dwie mrówki gracz mo¿e zakupiæ od samego pocz¹tku gry
		window.draw(addAntButton_2);
		window.draw(addAntButton_3);
		window.draw(addAntButton_4);
		window.draw(addAntButton_5);
		window.draw(addAntButton_6);

		window.draw(lifeBarCastle->lifeBar_castle);
		window.draw(lifeBarOpponentCastle->lifeBar_castle);

		if (ourCastle->level >= 2) {		// Poziom oblokowuje 2 kolejne mrowki
			addAntButton_3.setTexture(textureAdd_3);
			addAntButton_4.setTexture(textureAdd_4);
		}
		if (ourCastle->level >= 3) {		// Poziom oblokowuje 2 kolejne mrowki
			addAntButton_5.setTexture(textureAdd_5);
			addAntButton_6.setTexture(textureAdd_6);
		}
		if (ourCastle->level == 2) {		// Zmiana tekstury przycisku Upgrade po pierwszym ulepszeniu
			spriteUpgrade.setTexture(textureUpgrade2);
		}
		if (ourCastle->level == 3) {		// Zmiana tekstury przycisku Upgrade po pierwszym ulepszeniu
			spriteUpgrade.setTexture(textureUpgradeDis);
		}
		window.draw(spriteUpgrade);			// UPGRADE BUTTON

		//window.draw(ourCastle->rect);
		//window.draw(opponentsCastle->rect);

		if (drawAnt == true) {
			for (int i = 0; i < ants.size(); i++) {
				window.draw(ants[i]->sprite);				//Rysowanie mrówek
				window.draw(antsLifebars[i]->rect);
				//window.draw(ants[i]->rect);				//Rysowanie kolizji mrówek
			}
			for (int i = 0; i < opponents.size(); i++) {
				window.draw(opponents[i]->sprite);			//Rysowanie mrówek
				window.draw(opponentsLifebars[i]->rect);
				//window.draw(opponents[i]->rect);			//Rysowanie kolizji mrówek
			}
		}

		window.display();									//Pokaz wszystko, co narysowaliœmy
	}


	return 0;
}