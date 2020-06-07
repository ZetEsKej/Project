#include "ant.h"
class Lifebar;								// to jest potrzebne, ¿ebym móg³ odnieœæ siê do tej klasy w pewnej fukncji
	Ant::Ant(Player* player) {					// konstruktor podstawowy -> tworzenie mrówki	

		isAlive = true;
		isMoving = true;
		id = counter;
		walkingCounter = 0;
		rect.setFillColor(sf::Color::Green);

		if (player->isHuman) {				// mrówka nale¿y do gracza
			belongsToPlayer = true;
			sprite.setPosition(450, 985);
			rect.setPosition(sprite.getPosition());
		}

		else {
			belongsToPlayer = false;
			sprite.setPosition(7000, 800);		// 7000
			rect.setPosition(sprite.getPosition());
		}

		counter++;
		globalCounter++;
	}



	Ant::~Ant() {
		counter--;
	}

	void Ant::move() {					// poruszanie siê

		if (belongsToPlayer) {
			sprite.move(movementSpeed, 0);
			rect.move(movementSpeed, 0);
		}
		else {
			sprite.move(-movementSpeed, 0);
			rect.move(-movementSpeed, 0);
		}
		walkingCounter += 0.2;
		if (walkingCounter >= 6) {			// ostatnia klatka animacji -> zacznij od pocz¹tku
			walkingCounter = 0;
		}
	}

	void Ant::attackOpponent(Ant* opponent) {		// zaatakuj mrówkê przeciwnika

		// poni¿ej obliczanie mo¿liwych zadanych obra¿eñ
		float luck;
		luck = Player::getLuck(0.9, 1.1);		// zadawane obra¿enia s¹ mno¿one przez wartoœæ z zakresu 0.9-1.1 -> szczêœcie

		opponent->hp -= this->damage * luck;

		//if(opponent->belongsToPlayer)
		//	std::cout << "Nasz:\n HP: " << opponent->hp << "  Otrzymany dmg: " << this->damage*luck << std::endl;
		//	else
		//	std::cout << "Wrog:\n HP: " << opponent->hp << "  Otrzymany dmg: " << this->damage*luck << std::endl;
	}

	void Ant::attackCastle(Castle* castle) {		// zaatakuj zamek przeciwnika

		float luck = Player::getLuck(0.9, 1.1);
		castle->hp -= this->damage * luck;		// zadawane obra¿enia s¹ mno¿one przez wartoœæ z zakresu 0.9-1.1 -> szczêœcie
		//std::cout << castle->hp << std::endl;
		if (castle->hp < 0) {
			castle->destroyCastle();
		}
	}

	// poni¿sz¹ funkcjê mo¿na zoptymalizowaæ

	bool Ant::checkForCollision(std::vector<Ant*>& allies, std::vector<Ant*>& opponents, Castle* castle) {		// funkcja sprawdza, czy w zasiêgu znajduj¹ siê inne mrówki

		if (this->belongsToPlayer) {					// mrówka nale¿y do gracza
			for (int i = 0; i < allies.size(); i++) {
				if (allies[i]->id < id) {			// sprawdzaj mrówki przed sob¹
					if (allies[i]->rect.getPosition().x <= rect.getPosition().x + rect.getSize().x - 15) {		// mrówki s¹ bardzo blisko siebie lub wrêcz stykaj¹ siê ze sob¹
						if (allies[i]->id != id) {
							return false;
						}
					}

				}
			}
			for (int i = 0; i < opponents.size(); i++) {
				if (opponents[i]->rect.getPosition().x <= rect.getPosition().x + rect.getSize().x - 15) {		// mrówki s¹ bardzo blisko siebie lub wrêcz stykaj¹ siê ze sob¹
					return false;
				}
			}
			if (rect.getPosition().x + rect.getSize().x > castle->rect.getPosition().x) {		// czy mrówka dosz³a do zamku przeciwnika
				return false;
			}
		}
		else {			// mrówka nie nale¿y do gracza
			for (int i = 0; i < opponents.size(); i++) {
				if (opponents[i]->id < id) {			// sprawdzaj mrówki przed sob¹
					if (opponents[i]->rect.getPosition().x + opponents[i]->rect.getSize().x >= rect.getPosition().x + 15) {		// mrówki s¹ bardzo blisko siebie lub wrêcz stykaj¹ siê ze sob¹
						if (opponents[i]->id != id) {
							return false;
						}
					}

				}
			}
			for (int i = 0; i < allies.size(); i++) {
				if (allies[i]->rect.getPosition().x + allies[i]->rect.getSize().x >= rect.getPosition().x + 15) {		// mrówki s¹ bardzo blisko siebie lub wrêcz stykaj¹ siê ze sob¹
					return false;
				}
			}
			if (rect.getPosition().x < castle->rect.getPosition().x + castle->rect.getSize().x) {		// czy mrówka dosz³a do zamku przeciwnika
				return false;
			}
		}

		return true;
	}