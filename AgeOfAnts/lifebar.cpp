#include "ants.cpp"

class Lifebar : public Object
{

public:
	int maxHp;														// maksymalne hp mrówki (potrzebne do obliczania d³ugoœci lifebarów)
	Ant* ant;
	Lifebar(Ant* ant) {												//konstruktor 
		rect.setFillColor(sf::Color::Red);
		rect.setSize(sf::Vector2f(ant->rect.getSize().x - 80, 5.0f));
		rect.setPosition(ant->rect.getPosition().x + 40, 1020);		// umieszczenie paska pod mrówk¹
		maxHp = ant->hp;
		this->ant = ant;
	}
	Lifebar(Castle* castle) {										//konstruktor 
		rect.setFillColor(sf::Color::Magenta);
		rect.setSize(sf::Vector2f(0.005f * castle->hp, 5.0f));
		rect.setPosition(castle->rect.getPosition().x + 50, castle->rect.getPosition().y + castle->rect.getSize().y + 20);		// umieszczenie paska pod zamkiem
	}
	~Lifebar()													//destruktor
	{}

	void updateLifebar() {								//aktualzacja paska zdrowia
		rect.setSize(sf::Vector2f(float((ant->rect.getSize().x - 80) * (ant->hp/maxHp)), 5.0f));
		rect.setPosition(ant->rect.getPosition().x + 40, 1020);		// umieszczenie paska pod mrówk¹

		if (rect.getSize().x < 3) {								// gdy hp jest bardzo niskie, pasek staje siê niewidoczny. Ten if sprawia, ¿e ma on chocia¿ minimaln¹ gruboœæ
			rect.setSize(sf::Vector2f(3.0f, 5.0f));
		}
	}

	void updateLifebar(Castle* castle) {							//aktualzacja paska zdrowia
		rect.setSize(sf::Vector2f(0.005f * castle->hp, 5.0f));
		rect.setPosition(castle->rect.getPosition().x + 50, castle->rect.getPosition().y + castle->rect.getSize().y + 20);		// umieszczenie paska pod zamkiem

		if (rect.getSize().x < 3) {					// gdy hp jest bardzo niskie, pasek staje siê niewidoczny. Ten if sprawia, ¿e ma on chocia¿ minimaln¹ gruboœæ
			rect.setSize(sf::Vector2f(3.0f, 5.0f));
		}
	}
};