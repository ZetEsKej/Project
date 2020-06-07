#pragma once
#include "player.h"

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

	Ant(Player* player);					// konstruktor podstawowy -> tworzenie mr�wki	
	~Ant();

	void move();

	void attackOpponent(Ant* opponent);
	void attackCastle(Castle* castle);		// zaatakuj zamek przeciwnika
	bool checkForCollision(std::vector<Ant*>& allies, std::vector<Ant*>& opponents, Castle* castle); 		// funkcja sprawdza, czy w zasi�gu znajduj� si� inne mr�wki

	static bool checkForDead(std::vector<Ant*>& allies, std::vector<Lifebar*>& antsLifebars, std::vector<Lifebar*>& opponentsLifebars, std::vector<Ant*>& opponents, Player* player, Player* opponentPlayer) {		// funkcja statyczna usuwaj�ca martwe mr�wki z mapy

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

	static int countPowerOfAnts(std::vector<Ant*> ants) {	// funkcja wylicza "si��" wszystkich jednostek po danej stronie, jest to potrzebne do AI

		unsigned int overallPower = 0;

		for (int i = 0; i < ants.size(); i++) {
			overallPower += ants[i]->level;
		}

		return overallPower;
	}

};