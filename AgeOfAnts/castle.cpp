#include "Castle.h"

	Castle::Castle(bool isPlayer) {			// isPlayer - czy zamek nale¿y do gracza (wtedy ustawia inn¹ pozycjê startow¹)
		level = 1;
		hp = 100000;

		rect.setSize(sf::Vector2f(560, 200)); //600
		rect.setFillColor(sf::Color::Green);

		if (isPlayer) {				// zamek nale¿y do gracza
			rect.setPosition(0, 800);
		}
		else {						// zamek nale¿y do przeciwnika
			rect.setPosition(7050, 800);	// 7000
		}
	}