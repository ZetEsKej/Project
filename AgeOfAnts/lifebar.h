#pragma once
#include "ants.cpp"

class Lifebar : public Object
{

public:
	int maxHp;														// maksymalne hp mrówki (potrzebne do obliczania d³ugoœci lifebarów)
	Ant* ant;
	Lifebar(Ant* ant);
	Lifebar(Castle* castle);
	~Lifebar();													//destruktor

	void updateLifebar(); 								//aktualzacja paska zdrowia

	void updateLifebar(Castle* castle); 							//aktualzacja paska zdrowia
};