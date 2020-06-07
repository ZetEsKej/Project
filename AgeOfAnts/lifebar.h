#pragma once
#include "ants.cpp"

class Lifebar : public Object
{

public:
	int maxHp;														// maksymalne hp mr�wki (potrzebne do obliczania d�ugo�ci lifebar�w)
	Ant* ant;
	Lifebar(Ant* ant);
	Lifebar(Castle* castle);
	~Lifebar();													//destruktor

	void updateLifebar(); 								//aktualzacja paska zdrowia

	void updateLifebar(Castle* castle); 							//aktualzacja paska zdrowia
};