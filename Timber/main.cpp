// main.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;

class Object {			// klasa bazowa dla wszystkich obiektów typu mrówki

public:
	Sprite sprite;
	RectangleShape rect;	// prostokąt, służy do wyznaczania kolizji
	
};

class Ant: public Object {		// klasa od mrówek, dziedzicząca po klasie Object

	double movementSpeed = 0.2;
	//int hp;
	//int damage;
	//int range;
	//int attackSpeed;

public:
	Texture textureAnt;
	static int counter;
	bool isActive;

	void move() {					// poruszanie się
		if (!isActive) {
			sprite.setPosition(0, 800);
			isActive = true;
		}
		else {
			/*spriteAnt.setPosition(
				spriteAnt.getPosition().x + (antSpeed * dt.asSeconds()),
				spriteAnt.getPosition().y);*/
			sprite.move(0.2, 0);
			if (sprite.getPosition().x > 1920) {
				isActive = false;
			}
		}
	}

	Ant() {			// konstruktor -> tworzenie mrówki
		textureAnt.loadFromFile("graphics/ant.png");
		sprite.setTexture(textureAnt);
		sprite.setPosition(0, 800);
		counter++;
	}
};

int Ant::counter = 0;


int main()
{

	VideoMode vm(1920, 1080);   //Tworzenie objektu videomode - tworzenie ekranu
	RenderWindow window(vm, "Age Of Ants");  //Tworzenie i otwarcie okienka gry

	Texture textureBackground; //Przygotowanie tekstury tla
	textureBackground.loadFromFile("graphics/background.jpg"); //Załadowanie pliku do tekstury
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


	std::vector<Ant> ants;	// tablica z wszystkimi mrówkami


	bool isAntActive = false; //Czy mrowka jest aktywna
	double antSpeed = 10; //Prędkość mrowki
	Clock clock; //Wartość do kontrolowania czasu


	// Pętla gry (game loop)

	bool drawAnt = false;

	int antCounter = 0;

	while(window.isOpen()) {

		Event event;

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type ==  Event::KeyPressed && event.key.code == Keyboard::Escape) {		// zamykanie okna po wciśnięciu klawisza ESC
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {	// kliknięcie LPM
				auto mouse_pos = Mouse::getPosition(window); // pozcja myszki względem okna
				auto translated_pos = window.mapPixelToCoords(mouse_pos); // pozycja myszki w koordynatach globalnych
				if (addAntButton.getGlobalBounds().contains(translated_pos)) { // porównanie koordynatów myszki z koordynatami przycisku dodawania mrówek -> czy wystąpiło kliknięcie na przycisk addAnt

					drawAnt = true;

					Ant ant;
					ants.push_back(ant);
					ants[Ant::counter-1].sprite.setTexture(textureAnt);
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
				window.draw(ants[i].sprite); //Rysowanie mrówek
			}
		}

		window.display(); //Pokaz wszystko, co narysowaliśmy
	}


	return 0;
}