#pragma once
#include "castle.h"
#include <cstdlib>
#include <ctime>

class Player {

public:
	int money;
	//int score;
	bool isHuman;				// czy Player to gracz, czy komputer
	Castle* castle;				// zamek gracza

	Player(bool _isHuman, Castle* _castle);    // konstruktor
	int opponentsBuyingAction(unsigned int powerOfAllies, int numberOfAllies, unsigned int powerOfOpponents, int numberOfOpponents);		// jak� mr�wk� kupi przeciwnik po tym jak my kupimy mr�wk�

	static float getLuck(float a, float b) {				// metoda losuj�ca szcz�cie przy zadawaniu obra�e�; 

		return ((b - a) * ((float)rand() / RAND_MAX)) + a;
		/*float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;*/
	}
};