#include "ants.cpp"

class Lifebar : public Object
{

public:
	sf::RectangleShape lifeBar_ant;
	Lifebar(Ant* ant)	//konstruktor 
	{
		rect.setFillColor(sf::Color::Red);
		rect.setSize(sf::Vector2f(0.05 * ant->hp, 5));
		rect.setPosition(ant->rect.getPosition().x + 50, ant->rect.getPosition().y + ant->rect.getSize().y + 20);		// umieszczenie paska nad mrówk¹

	}
	Lifebar(Castle* castle) //konstruktor dla zamku
	{
		rect.setFillColor(sf::Color::Magenta);
		rect.setSize(sf::Vector2f(0.001 * castle->hp, 5));
		rect.setPosition(castle->rect.getPosition().x + 50, castle->rect.getPosition().y + castle->rect.getSize().y + 20);	//testowe wartoœci skopiowane z paska dla mrówek
	}
	~Lifebar()	//destruktor
	{}

	void updateLifebar(Ant* ant)	//aktualzacja paska zdrowia
	{
		rect.setSize(sf::Vector2f(0.05f * ant->hp, 5.0f));
		rect.setPosition(ant->rect.getPosition().x + 50, ant->rect.getPosition().y + ant->rect.getSize().y +  20);		// umieszczenie paska nad mrówk¹
		
		if (rect.getSize().x < 3) {						// gdy hp jest bardzo niskie, pasek staje siê niewidoczny. Ta funkcja sprawia, ¿e ma on chocia¿ minimaln¹ gruboœæ
			rect.setSize(sf::Vector2f(3.0f, 5.0f));
		}
	}
	void updateLifebar(Castle* castle)
	{
		rect.setSize(sf::Vector2f(0.001f * castle->hp, 5.0f));
		rect.setPosition(castle->rect.getPosition().x + 50, castle->rect.getPosition().y + castle->rect.getSize().y + 20);		// umieszczenie paska nad mrówk¹

		if (rect.getSize().x < 3) {						// gdy hp jest bardzo niskie, pasek staje siê niewidoczny. Ta funkcja sprawia, ¿e ma on chocia¿ minimaln¹ gruboœæ
			rect.setSize(sf::Vector2f(3.0f, 5.0f));
		}
	}
};