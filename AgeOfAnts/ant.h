#pragma once
#include "player.h"

class Lifebar;								// to jest potrzebne, ¿ebym móg³ odnieœæ siê do tej klasy w pewnej fukncji

class Ant : public Object {					// klasa od mrówek, dziedzicz¹ca po klasie Object

public:
	static unsigned int counter;			// licznik mrówek obecnych na mapie
	static unsigned int globalCounter;		// licznik wszystkich mrówek, które kiedykolwiek zosta³y stworzone
	static int cost[8];						// koszt mrówek na poszczególnych poziomach


	int level;								// poziom mrówki
	double movementSpeed;					// szybkoœæ poruszania siê mrówki
	float hp;								// punkty ¿ycia mrówki
	float damage;							// zadawane przez mrówkê obra¿enia

	unsigned int id = globalCounter;
	sf::Texture textureAnt;
	int height;								// wysokoœæ mrówki
	int width;								// d³ugoœæ mrówki

	bool isAlive;							// czy mrówka ¿yje
	bool isMoving;							// czy mrówka stoi, czy siê porusza
	bool belongsToPlayer;					// czy mrówka nale¿y do gracza
	float walkingCounter;					// licznik kroków (potrzebne do animacji)

	Ant(Player* player);					// konstruktor podstawowy -> tworzenie mrówki	
	~Ant();

	void move();

	void attackOpponent(Ant* opponent);
	void attackCastle(Castle* castle);		// zaatakuj zamek przeciwnika
	bool checkForCollision(std::vector<Ant*>& allies, std::vector<Ant*>& opponents, Castle* castle); 		// funkcja sprawdza, czy w zasiêgu znajduj¹ siê inne mrówki

	static bool checkForDead(std::vector<Ant*>& allies, std::vector<Lifebar*>& antsLifebars, std::vector<Lifebar*>& opponentsLifebars, std::vector<Ant*>& opponents, Player* player, Player* opponentPlayer) {		// funkcja statyczna usuwaj¹ca martwe mrówki z mapy

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
				opponentsLifebars.erase(opponentsLifebars.begin() + i);
				opponents.erase(opponents.begin() + i);
				AreDeads = true;
				i--;
			}
		}

		return AreDeads;
	}

	static int countPowerOfAnts(std::vector<Ant*> ants) {	// funkcja wylicza "si³ê" wszystkich jednostek po danej stronie, jest to potrzebne do AI

		unsigned int overallPower = 0;

		for (int i = 0; i < ants.size(); i++) {
			overallPower += ants[i]->level;
		}

		return overallPower;
	}

};