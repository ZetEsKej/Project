#include "ants.cpp"

class Lifebar : public Object
{

public:
	Lifebar(Ant* ant) {												//konstruktor 
		rect.setFillColor(sf::Color::Red);
		rect.setSize(sf::Vector2f(0.05 * ant->hp, 5));
		rect.setPosition(ant->rect.getPosition().x + 50, ant->rect.getPosition().y + ant->rect.getSize().y + 20);		// umieszczenie paska nad mr�wk�
	}
	Lifebar(Castle* castle) {										//konstruktor 
		rect.setFillColor(sf::Color::Magenta);
		rect.setSize(sf::Vector2f(0.005 * castle->hp, 5));
		rect.setPosition(castle->rect.getPosition().x + 50, castle->rect.getPosition().y + castle->rect.getSize().y + 20);		// umieszczenie paska nad mr�wk�
	}
	~Lifebar()													//destruktor
	{}

	void updateLifebar(Ant* ant) {								//aktualzacja paska zdrowia
		rect.setSize(sf::Vector2f(0.05f * ant->hp, 5.0f));
		rect.setPosition(ant->rect.getPosition().x + 50, ant->rect.getPosition().y + ant->rect.getSize().y + 20);		// umieszczenie paska nad mr�wk�

		if (rect.getSize().x < 3) {								// gdy hp jest bardzo niskie, pasek staje si� niewidoczny. Ta funkcja sprawia, �e ma on chocia� minimaln� grubo��
			rect.setSize(sf::Vector2f(3.0f, 5.0f));
		}
	}

	void updateLifebar(Castle* castle) {							//aktualzacja paska zdrowia
		rect.setSize(sf::Vector2f(0.005f * castle->hp, 5.0f));
		rect.setPosition(castle->rect.getPosition().x + 50, castle->rect.getPosition().y + castle->rect.getSize().y + 20);		// umieszczenie paska nad mr�wk�

		if (rect.getSize().x < 3) {					// gdy hp jest bardzo niskie, pasek staje si� niewidoczny. Ta funkcja sprawia, �e ma on chocia� minimaln� grubo��
			rect.setSize(sf::Vector2f(3.0f, 5.0f));
		}
	}
};