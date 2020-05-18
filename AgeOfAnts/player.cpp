class Player {

public:
	int money;
	//int score;
	bool isHuman;		// czy Player to gracz, czy komputer

	Player(bool _isHuman) {
		isHuman = _isHuman;
		money = 100;
		//score = 0;
	}
};