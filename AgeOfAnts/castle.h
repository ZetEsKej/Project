#pragma once
#include "object.h"

class Castle : public Object {

public:
	int level;						// poziom rozbudowy zamku
	float hp;						// wytrzyma³oœæ zamku

	Castle(bool isPlayer);

	void updateCastle() {			// podniesienie poziomu zamku
		level += 1;
	}

	void destroyCastle() {			// zniszczenie zamku - koniec gry
		std::cout << "Koniec gry!" << std::endl;
		// tutaj trzeba bêdzie ogarn¹æ coœ, co siê stanie na koniec gry
	}
};
