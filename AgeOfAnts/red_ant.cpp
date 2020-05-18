//#include "ant.cpp"
//
//class RedAnt : public Ant {
//
//public:
//
//	RedAnt() {			// konstruktor -> tworzenie mrówki (prze³adowanie)
//		isAlive = true;
//		isMoving = true;
//		belongsToPlayer = false;
//		id = counter;
//		rect.setSize(sf::Vector2f(200, 50));
//		rect.setFillColor(sf::Color::Green);
//		textureAnt.loadFromFile("graphics/ant.png");
//		sprite.setTexture(textureAnt);
//		sprite.setPosition(1700, 800);
//		rect.setPosition(1700, 800);
//		counter++;
//	}
//
//	void move() {					// poruszanie siê - nadpisanie funkcji (mrowka idzie w przeciwnym kierunku)
//
//		if (isMoving == true) {
//			sprite.move(-1, 0);
//			rect.move(-1, 0);
//			/*	if (sprite.getPosition().x > 1920) {
//					isActive = false;
//				}*/
//		}
//
//	}
//};