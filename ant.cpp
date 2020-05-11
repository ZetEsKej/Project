#include "object.cpp"

class Ant : public Object {		// klasa od mr�wek, dziedzicz�ca po klasie Object

	double movementSpeed = 0.2;
	//int hp;
	//int damage;
	//int range;
	//int attackSpeed;

public:
	sf::Texture textureAnt;
	static int counter;
	bool isActive;

	void move() {					// poruszanie si�
		if (isActive == false) {
			// usuwanie obiektu, je�li nie jest on ju� aktywny
		}
		else {
			/*spriteAnt.setPosition(
				spriteAnt.getPosition().x + (antSpeed * dt.asSeconds()),
				spriteAnt.getPosition().y);*/
			sprite.move(movementSpeed, 0);
			rect.move(movementSpeed, 0);
			if (sprite.getPosition().x > 1920) {
				isActive = false;
			}
		}
	}


	Ant() {			// konstruktor -> tworzenie mr�wki
		isActive = true;
		rect.setSize(sf::Vector2f(200, 50));
		rect.setFillColor(sf::Color::Green);
		textureAnt.loadFromFile("graphics/ant.png");
		sprite.setTexture(textureAnt);
		sprite.setPosition(0, 800);
		rect.setPosition(0, 800);
		counter++;
	}
};
