#include "object.cpp"

class Castle : public Object {

public:
	int level;						// poziom rozbudowy zamku
	float hp;						// wytrzyma�o�� zamku

	Castle(bool isPlayer) {			// isPlayer - czy zamek nale�y do gracza (wtedy ustawia inn� pozycj� startow�)
		level = 1;
		hp = 100000;

		rect.setSize(sf::Vector2f(600, 200));
		rect.setFillColor(sf::Color::Green);

		if (isPlayer) {				// zamek nale�y do gracza
			rect.setPosition(0, 800);
		}
		else {						// zamek nale�y do przeciwnika
			rect.setPosition(7000, 800);
		}
	}

	void updateCastle() {			// podniesienie poziomu zamku
		level += 1;
	}

	void destroyCastle() {			// zniszczenie zamku - koniec gry
		std::cout << "Koniec gry!" << std::endl;
		// tutaj trzeba b�dzie ogarn�� co�, co si� stanie na koniec gry
	}
};