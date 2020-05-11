// main.cpp : Ten plik zawiera funkcj� �main�. W nim rozpoczyna si� i ko�czy wykonywanie programu.
//

//#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "ant.cpp"

using namespace sf;

int Ant::counter = 0;

int main()
{

	VideoMode vm(1920, 1080);   //Tworzenie objektu videomode - tworzenie ekranu
	RenderWindow window(vm, "Age Of Ants");  //Tworzenie i otwarcie okienka gry

	View fixed = window.getView(); //Kamera 2D
	View scroll = fixed;

	Texture textureBackground; //Przygotowanie tekstury tla
	textureBackground.loadFromFile("graphics/background.jpg"); //Za�adowanie pliku do tekstury
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	Texture textureAdd;
	textureAdd.loadFromFile("graphics/add.png");
	Sprite addAntButton;
	addAntButton.setTexture(textureAdd);
	addAntButton.setPosition(100, 200);

	Texture textureAnt; 	//Tworzenie tekstury mrowki
	textureAnt.loadFromFile("graphics/ant.png");

	std::vector<Ant> ants;	// tablica z wszystkimi mr�wkami

	double antSpeed = 10; //Pr�dko�� mrowki
	Clock clock; //Warto�� do kontrolowania czasu


	// P�tla gry (game loop)

	bool drawAnt = false;

	int antCounter = 0;

	while (window.isOpen()) {

		Event event;

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {		// zamykanie okna po wci�ni�ciu klawisza ESC
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {	// klikni�cie LPM
				auto mouse_pos = Mouse::getPosition(window); // pozcja myszki wzgl�dem okna
				auto translated_pos = window.mapPixelToCoords(mouse_pos); // pozycja myszki w koordynatach globalnych
				if (addAntButton.getGlobalBounds().contains(translated_pos)) { // por�wnanie koordynat�w myszki z koordynatami przycisku dodawania mr�wek -> czy wyst�pi�o klikni�cie na przycisk addAnt

					drawAnt = true;

					Ant ant;
					ants.push_back(ant);
					ants[Ant::counter - 1].sprite.setTexture(textureAnt);
				}

			}

		}


		//Aktualizacja sceny - Update Scene

		if (drawAnt == true) {

			Time dt = clock.restart();

			for (int i = 0; i < Ant::counter; i++) {
				ants[i].move();
			}
		}


		//Rysowanie sceny - Draw Scene

		window.clear(); //Usuniecie wszystkiego z ostatniego frame'a - czyszczenie sceny

		window.draw(spriteBackground);  //Rysowanie sceny gry

		window.draw(addAntButton);

		if (drawAnt == true) {
			for (int i = 0; i < Ant::counter; i++) {
				window.draw(ants[i].sprite); //Rysowanie mr�wek
				//window.draw(ants[i].rect); //Rysowanie kolizji mr�wek
			}
		}

		window.display(); //Pokaz wszystko, co narysowali�my
	}


	return 0;
}