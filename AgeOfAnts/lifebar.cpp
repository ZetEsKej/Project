#include "ants.cpp"

class Lifebar : public Object
{

public:
	sf::RectangleShape lifeBar_ant;
	sf::RectangleShape lifeBar_castle;
	Lifebar(Ant* ant)											//konstruktor 
	{
		rect.setFillColor(sf::Color::Red);
		rect.setSize(sf::Vector2f(0.05 * ant->hp, 5));
		rect.setPosition(ant->rect.getPosition().x + 50, ant->rect.getPosition().y + ant->rect.getSize().y + 20);		// umieszczenie paska nad mrówk¹

	}
	Lifebar(Castle* castle)										//konstruktor 
	{
		lifeBar_castle.setFillColor(sf::Color::Magenta);
		lifeBar_castle.setSize(sf::Vector2f(0.005 * castle->hp, 5));
		lifeBar_castle.setPosition(castle->rect.getPosition().x + 50, castle->rect.getPosition().y + castle->rect.getSize().y + 20);		// umieszczenie paska nad mrówk¹

	}
	~Lifebar()													//destruktor
	{}

	void updateLifebar(Ant* ant)								//aktualzacja paska zdrowia
	{
		rect.setSize(sf::Vector2f(0.05f * ant->hp, 5.0f));
		rect.setPosition(ant->rect.getPosition().x + 50, ant->rect.getPosition().y + ant->rect.getSize().y + 20);		// umieszczenie paska nad mrówk¹

		if (rect.getSize().x < 3) {								// gdy hp jest bardzo niskie, pasek staje siê niewidoczny. Ta funkcja sprawia, ¿e ma on chocia¿ minimaln¹ gruboœæ
			rect.setSize(sf::Vector2f(3.0f, 5.0f));
		}
	}
	void updateLifebar(Castle* castle)							//aktualzacja paska zdrowia
	{
		lifeBar_castle.setSize(sf::Vector2f(0.005f * castle->hp, 5.0f));
		lifeBar_castle.setPosition(castle->rect.getPosition().x + 50, castle->rect.getPosition().y + castle->rect.getSize().y + 20);		// umieszczenie paska nad mrówk¹

		if (lifeBar_castle.getSize().x < 3) {					// gdy hp jest bardzo niskie, pasek staje siê niewidoczny. Ta funkcja sprawia, ¿e ma on chocia¿ minimaln¹ gruboœæ
			lifeBar_castle.setSize(sf::Vector2f(3.0f, 5.0f));
		}
	}
};