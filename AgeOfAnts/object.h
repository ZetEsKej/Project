#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Object {					// klasa bazowa dla wszystkich obiektów typu mrówki

public:
	sf::Sprite sprite;
	sf::RectangleShape rect;	// prostok¹t otaczaj¹cy obiekt, s³u¿y do wyznaczania kolizji

};
