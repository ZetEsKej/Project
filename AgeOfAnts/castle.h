#pragma once
#include "object.h"

class Castle : public Object {

public:
	int level;						// poziom rozbudowy zamku
	float hp;						// wytrzyma�o�� zamku

	Castle(bool isPlayer);

	void updateCastle() {			// podniesienie poziomu zamku
		level += 1;
	}

	void destroyCastle() {			// zniszczenie zamku - koniec gry
		std::cout << "Koniec gry!" << std::endl;
		// tutaj trzeba b�dzie ogarn�� co�, co si� stanie na koniec gry
	}
};
