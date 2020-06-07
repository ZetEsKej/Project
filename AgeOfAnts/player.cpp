#pragma once
#include "player.h"



	Player::Player(bool _isHuman, Castle* _castle) {		// konstruktor
		isHuman = _isHuman;
		money = 100;
		castle = _castle;
		//score = 0;
	}

	int Player::opponentsBuyingAction(unsigned int powerOfAllies, int numberOfAllies, unsigned int powerOfOpponents, int numberOfOpponents) {		// jak¹ mrówkê kupi przeciwnik po tym jak my kupimy mrówkê

		// analiza sytuacji na mapie i finansów (jeszcze nie wp³ywa na nic - work in progress)

		int situation = 0;												// jeœli situation jest > 0, przeciwnik jest na korzystnej pozycji
		situation += powerOfOpponents - powerOfAllies;
		situation += numberOfOpponents - numberOfAllies;

		if(money < 40) return 10;				// przeciwnik pasuje - nie kupuje mrówki
		else {										// przeciwnik kupuje mrówkê
			// analiza, któr¹ mrówkê kupiæ
			
			float luck = 5.0;					// element losowoœci -> czy aby na pewno kupiæ tê du¿¹ mrówkê (jeœli jest ma³o kasy, to mniejsza szansa na zakup)

			if (money < 500)
				luck = Player::getLuck(float(money / 100), 5.0 + float(situation/10));
			
			if (castle->level >= 3) {

				if (luck > 4.0) return 5;
				if (luck > 3.5) return 4;
			}
			if (castle->level >= 2) {
				if (luck > 3.0) return 3;
				if (luck > 2.5) return 2;
			}
			if (luck > 2.0) return 1;
			
			return 0;

		}
	}