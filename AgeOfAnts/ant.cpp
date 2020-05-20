#include "castle.cpp"
#include "player.cpp"
#include "audio.cpp"

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
			sprite.setPosition(7000, 800);
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
		if (opponent->belongsToPlayer == false) {	// nasza mr�wka atakuje
			luck = Ant::getLuck(1.0, 1.1);		// zadawane obra�enia s� mno�one przez warto�� z zakresu 0.9-1.1 -> szcz�cie
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
		castle->hp -= this->damage * luck;		// zadawane obra�enia s� mno�one przez warto�� z zakresu 0.9-1.1 -> szcz�cie
		std::cout << castle->hp << std::endl;
		if (castle->hp < 0) {
			castle->destroyCastle();
		}
	}

	// poni�sz� funkcj� mo�na zoptymalizowa�

	bool checkForCollision(std::vector<Ant*>& allies, std::vector<Ant*>& opponents, Castle* castle) {		// funkcja sprawdza, czy w zasi�gu znajduj� si� inne mr�wki

		if (this->belongsToPlayer) {					// mr�wka nale�y do gracza
			for (int i = 0; i < allies.size(); i++) {
				if (allies[i]->id < id) {			// sprawdzaj mr�wki przed sob�
					if (allies[i]->rect.getPosition().x <= rect.getPosition().x + rect.getSize().x + 0.5) {		// mr�wki s� bardzo blisko siebie lub wr�cz stykaj� si� ze sob�
						if (allies[i]->id != id) {
							return false;
						}
					}

				}
			}
			for (int i = 0; i < opponents.size(); i++) {
				if (opponents[i]->rect.getPosition().x <= rect.getPosition().x + rect.getSize().x + 0.5) {		// mr�wki s� bardzo blisko siebie lub wr�cz stykaj� si� ze sob�
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
					if (opponents[i]->rect.getPosition().x + opponents[i]->rect.getSize().x >= rect.getPosition().x - 0.5) {		// mr�wki s� bardzo blisko siebie lub wr�cz stykaj� si� ze sob�
						if (opponents[i]->id != id) {
							return false;
						}
					}

				}
			}
			for (int i = 0; i < allies.size(); i++) {
				if (allies[i]->rect.getPosition().x + allies[i]->rect.getSize().x >= rect.getPosition().x - 0.5) {		// mr�wki s� bardzo blisko siebie lub wr�cz stykaj� si� ze sob�
					return false;
				}
			}
			if (rect.getPosition().x < castle->rect.getPosition().x + castle->rect.getSize().x) {		// czy mr�wka dosz�a do zamku przeciwnika
				return false;
			}
		}

		return true;
	}

	// poni�sz� chyba mo�na zoptymalizwoa� -> tylko najstarsza mr�wka mo�e by� martwa


	static bool checkForDead(std::vector<Ant*>& allies, std::vector<Lifebar*> antsLifebars, std::vector<Lifebar*> opponentsLifebars, std::vector<Ant*>& opponents, Player* player, Player* opponentPlayer) {		// funkcja statyczna usuwaj�ca martwe mr�wki z mapy
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

	static float getLuck(float a, float b) {				// metoda losuj�ca szcz�cie przy zadawaniu obra�e�; 
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
};
