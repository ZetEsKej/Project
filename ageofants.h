#ifndef AGEOFANTS_H
#define AGEOFANTS_H

#include"State.h"

class ageofants
{
private:
	//Zmienne
	sf::RenderWindow *okno;
	sf::Event zdarzenie;

	sf::Clock deltaZegar;
	float deltaczas;

	//Inicjalizacja
	void initwindow();

public:
	ageofants();
	virtual ~ageofants();

	//functions
	void updatedt();
	void updateSFMLevents();
	void update();
	void render();
	void run();
};

#endif

