#include <SFML/Graphics.hpp>


class Object {			// klasa bazowa dla wszystkich obiekt�w typu mr�wki

public:
	sf::Sprite sprite;
	sf::RectangleShape rect;	// prostok�t otaczaj�cy obiekt, s�u�y do wyznaczania kolizji

};