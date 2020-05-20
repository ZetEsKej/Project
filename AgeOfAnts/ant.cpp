#include "castle.cpp"
#include "player.cpp"
#include "audio.cpp"

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

	Ant(Player* player) {					// konstruktor podstawowy -> tworzenie mrówki	

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
			sprite.setPosition(7000, 800);
			rect.setPosition(sprite.getPosition());
		}

		counter++;
		globalCounter++;
	}



	~Ant() {
		counter--;
	}

	void move() {					// poruszanie siê

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

	void attackOpponent(Ant* opponent) {		// zaatakuj mrówkê przeciwnika

		// poni¿ej obliczanie mo¿liwych zadanych obra¿eñ
		float luck;
		if (opponent->belongsToPlayer == false) {	// nasza mrówka atakuje
			luck = Ant::getLuck(1.0, 1.1);		// zadawane obra¿enia s¹ mno¿one przez wartoœæ z zakresu 0.9-1.1 -> szczêœcie
		}
		else {
			luck = Ant::getLuck(0.9, 1.1);
		}

		opponent->hp -= this->damage * luck;

		//if(opponent->belongsToPlayer)
		//	std::cout << "Nasz:\n HP: " << opponent->hp << "  Otrzymany dmg: " << this->damage*luck << std::endl;
		//	else
		//	std::cout << "Wrog:\n HP: " << opponent->hp << "  Otrzymany dmg: " << this->damage*luck << std::endl;
	}

	void attackCastle(Castle* castle) {		// zaatakuj zamek przeciwnika

		float luck = Ant::getLuck(0.9, 1.1);
		castle->hp -= this->damage * luck;		// zadawane obra¿enia s¹ mno¿one przez wartoœæ z zakresu 0.9-1.1 -> szczêœcie
		std::cout << castle->hp << std::endl;
		if (castle->hp < 0) {
			castle->destroyCastle();
		}
	}

	// poni¿sz¹ funkcjê mo¿na zoptymalizowaæ

	bool checkForCollision(std::vector<Ant*>& allies, std::vector<Ant*>& opponents, Castle* castle) {		// funkcja sprawdza, czy w zasiêgu znajduj¹ siê inne mrówki

		if (this->belongsToPlayer) {					// mrówka nale¿y do gracza
			for (int i = 0; i < allies.size(); i++) {
				if (allies[i]->id < id) {			// sprawdzaj mrówki przed sob¹
					if (allies[i]->rect.getPosition().x <= rect.getPosition().x + rect.getSize().x + 0.5) {		// mrówki s¹ bardzo blisko siebie lub wrêcz stykaj¹ siê ze sob¹
						if (allies[i]->id != id) {
							return false;
						}
					}

				}
			}
			for (int i = 0; i < opponents.size(); i++) {
				if (opponents[i]->rect.getPosition().x <= rect.getPosition().x + rect.getSize().x + 0.5) {		// mrówki s¹ bardzo blisko siebie lub wrêcz stykaj¹ siê ze sob¹
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
					if (opponents[i]->rect.getPosition().x + opponents[i]->rect.getSize().x >= rect.getPosition().x - 0.5) {		// mrówki s¹ bardzo blisko siebie lub wrêcz stykaj¹ siê ze sob¹
						if (opponents[i]->id != id) {
							return false;
						}
					}

				}
			}
			for (int i = 0; i < allies.size(); i++) {
				if (allies[i]->rect.getPosition().x + allies[i]->rect.getSize().x >= rect.getPosition().x - 0.5) {		// mrówki s¹ bardzo blisko siebie lub wrêcz stykaj¹ siê ze sob¹
					return false;
				}
			}
			if (rect.getPosition().x < castle->rect.getPosition().x + castle->rect.getSize().x) {		// czy mrówka dosz³a do zamku przeciwnika
				return false;
			}
		}

		return true;
	}

	// poni¿sz¹ chyba mo¿na zoptymalizwoaæ -> tylko najstarsza mrówka mo¿e byæ martwa


	static bool checkForDead(std::vector<Ant*>& allies, std::vector<Lifebar*> antsLifebars, std::vector<Lifebar*> opponentsLifebars, std::vector<Ant*>& opponents, Player* player, Player* opponentPlayer) {		// funkcja statyczna usuwaj¹ca martwe mrówki z mapy
		bool AreDeads = false;

		for (int i = 0; i < allies.size(); i++) {
			if (allies[i]->hp < 0) {
				opponentPlayer->money += Ant::cost[allies[i]->level] + double(0.6 * Ant::cost[allies[i]->level]);
				std::cout << opponentPlayer->money << std::endl;
				allies.erase(allies.begin() + i);
				antsLifebars.erase(antsLifebars.begin() + i);
				AreDeads = true;
			}
		}
		for (int i = 0; i < opponents.size(); i++) {
			if (opponents[i]->hp < 0) {
				player->money += Ant::cost[opponents[i]->level] + double(0.6 * Ant::cost[opponents[i]->level]);
				std::cout << "Nasze jaja: " << player->money << std::endl;
				opponents.erase(opponents.begin() + i);
				opponentsLifebars.erase(opponentsLifebars.begin() + i);
				AreDeads = true;
			}
		}
		return AreDeads;
	}

	/*void showLifebar(Ant* ant) {

	}*/

	static float getLuck(float a, float b) {				// metoda losuj¹ca szczêœcie przy zadawaniu obra¿eñ; 
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
};
