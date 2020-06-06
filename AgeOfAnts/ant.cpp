#pragma once
#include "player.cpp"

class Lifebar;								// to jest potrzebne, �ebym m�g� odnie�� si� do tej klasy w pewnej fukncji

class Ant : public Object {					// klasa od mr�wek, dziedzicz�ca po klasie Object

public:
	static unsigned int counter;			// licznik mr�wek obecnych na mapie
	static unsigned int globalCounter;		// licznik wszystkich mr�wek, kt�re kiedykolwiek zosta�y stworzone
	static int cost[8];						// koszt mr�wek na poszczeg�lnych poziomach


	int level;								// poziom mr�wki
	double movementSpeed;					// szybko�� poruszania si� mr�wki
	float hp;								// punkty �ycia mr�wki
	float damage;							// zadawane przez mr�wk� obra�enia

	unsigned int id = globalCounter;
	sf::Texture textureAnt;
	int height;								// wysoko�� mr�wki
	int width;								// d�ugo�� mr�wki

	bool isAlive;							// czy mr�wka �yje
	bool isMoving;							// czy mr�wka stoi, czy si� porusza
	bool belongsToPlayer;					// czy mr�wka nale�y do gracza
	float walkingCounter;					// licznik krok�w (potrzebne do animacji)

	Ant(Player* player) {					// konstruktor podstawowy -> tworzenie mr�wki	

		isAlive = true;
		isMoving = true;
		id = counter;
		walkingCounter = 0;
		rect.setFillColor(sf::Color::Green);

		if (player->isHuman) {				// mr�wka nale�y do gracza
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



	~Ant() {
		counter--;
	}

	void move() {					// poruszanie si�

		if (belongsToPlayer) {
			sprite.move(movementSpeed, 0);
			rect.move(movementSpeed, 0);
		}
		else {
			sprite.move(-movementSpeed, 0);
			rect.move(-movementSpeed, 0);
		}
		walkingCounter += 0.2;
		if (walkingCounter >= 6) {			// ostatnia klatka animacji -> zacznij od pocz�tku
			walkingCounter = 0;
		}
	}

	void attackOpponent(Ant* opponent) {		// zaatakuj mr�wk� przeciwnika

		// poni�ej obliczanie mo�liwych zadanych obra�e�
		float luck;
		luck = Player::getLuck(0.9, 1.1);		// zadawane obra�enia s� mno�one przez warto�� z zakresu 0.9-1.1 -> szcz�cie

		opponent->hp -= this->damage * luck;

		//if(opponent->belongsToPlayer)
		//	std::cout << "Nasz:\n HP: " << opponent->hp << "  Otrzymany dmg: " << this->damage*luck << std::endl;
		//	else
		//	std::cout << "Wrog:\n HP: " << opponent->hp << "  Otrzymany dmg: " << this->damage*luck << std::endl;
	}

	void attackCastle(Castle* castle) {		// zaatakuj zamek przeciwnika

		float luck = Player::getLuck(0.9, 1.1);
		castle->hp -= this->damage * luck;		// zadawane obra�enia s� mno�one przez warto�� z zakresu 0.9-1.1 -> szcz�cie
		//std::cout << castle->hp << std::endl;
		if (castle->hp < 0) {
			castle->destroyCastle();
		}
	}

	// poni�sz� funkcj� mo�na zoptymalizowa�

	bool checkForCollision(std::vector<Ant*>& allies, std::vector<Ant*>& opponents, Castle* castle) {		// funkcja sprawdza, czy w zasi�gu znajduj� si� inne mr�wki

		if (this->belongsToPlayer) {					// mr�wka nale�y do gracza
			for (int i = 0; i < allies.size(); i++) {
				if (allies[i]->id < id) {			// sprawdzaj mr�wki przed sob�
					if (allies[i]->rect.getPosition().x <= rect.getPosition().x + rect.getSize().x - 15) {		// mr�wki s� bardzo blisko siebie lub wr�cz stykaj� si� ze sob�
						if (allies[i]->id != id) {
							return false;
						}
					}

				}
			}
			for (int i = 0; i < opponents.size(); i++) {
				if (opponents[i]->rect.getPosition().x <= rect.getPosition().x + rect.getSize().x - 15) {		// mr�wki s� bardzo blisko siebie lub wr�cz stykaj� si� ze sob�
					return false;
				}
			}
			if (rect.getPosition().x + rect.getSize().x > castle->rect.getPosition().x) {		// czy mr�wka dosz�a do zamku przeciwnika
				return false;
			}
		}
		else {			// mr�wka nie nale�y do gracza
			for (int i = 0; i < opponents.size(); i++) {
				if (opponents[i]->id < id) {			// sprawdzaj mr�wki przed sob�
					if (opponents[i]->rect.getPosition().x + opponents[i]->rect.getSize().x >= rect.getPosition().x + 15) {		// mr�wki s� bardzo blisko siebie lub wr�cz stykaj� si� ze sob�
						if (opponents[i]->id != id) {
							return false;
						}
					}

				}
			}
			for (int i = 0; i < allies.size(); i++) {
				if (allies[i]->rect.getPosition().x + allies[i]->rect.getSize().x >= rect.getPosition().x + 15) {		// mr�wki s� bardzo blisko siebie lub wr�cz stykaj� si� ze sob�
					return false;
				}
			}
			if (rect.getPosition().x < castle->rect.getPosition().x + castle->rect.getSize().x) {		// czy mr�wka dosz�a do zamku przeciwnika
				return false;
			}
		}

		return true;
	}

	static bool checkForDead(std::vector<Ant*>& allies, std::vector<Lifebar*>& antsLifebars, std::vector<Lifebar*> &opponentsLifebars, std::vector<Ant*>& opponents, Player* player, Player* opponentPlayer) {		// funkcja statyczna usuwaj�ca martwe mr�wki z mapy

		bool AreDeads = false;
		if (!allies.empty()) {
			if (allies[0]->hp <= 0) {
				opponentPlayer->money += Ant::cost[allies[0]->level] + double(0.6 * Ant::cost[allies[0]->level]);
				antsLifebars.erase(antsLifebars.begin());
				allies.erase(allies.begin());
				AreDeads = true;
			}	
		}
		
		//if (!opponents.empty()) {
		//	if (opponents[0]->hp <= 0) {
		//		player->money += Ant::cost[opponents[0]->level] + double(0.6 * Ant::cost[opponents[0]->level]);
		//		opponentsLifebars.erase(opponentsLifebars.begin());
		//		opponents.erase(opponents.begin());
		//		AreDeads = true;
		//	}
		//	}
		
		for (int i = 0; i < opponents.size(); i++) {
			if (opponents[i]->hp <= 0) {
				player->money += Ant::cost[opponents[i]->level] + double(0.6 * Ant::cost[opponents[i]->level]);
				opponentsLifebars.erase(opponentsLifebars.begin()+i);
				opponents.erase(opponents.begin()+i);
				AreDeads = true;
				i--;
			}
		}

		return AreDeads;
	}

	static int countPowerOfAnts(std::vector<Ant*> ants) {	// funkcja wylicza "si��" wszystkich jednostek po danej stronie, jest to potrzebne do AI

		unsigned int overallPower = 0;

		for (int i = 0; i < ants.size(); i++) {
			overallPower += ants[i]->level;
		}

		return overallPower;
	}

};
