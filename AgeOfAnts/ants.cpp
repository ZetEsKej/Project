#include "ant.cpp"

//class Ant_l0 : public Ant				{// l0 -> oznacza poziom mrówki (od 0 do 7)
//
//public:
//
//	Ant_l0(Player* player) :Ant(player) {			
//		level = 0;
//		damage = 1.5;
//		hp = 1500.0;
//		movementSpeed = 0.2;
//		player->money -= cost[level];		// zap³ata za mrówkê
//		width = 147;
//		height = 66;
//
//		rect.setSize(sf::Vector2f(width - 15, height));
//
//		//textureAnt.loadFromFile("graphics/ant_2.png");
//		//sprite.setTexture(textureAnt);
//	}
//};

class Ant_l1 : public Ant {

public:

	Ant_l1(Player* player) :Ant(player) {
		level = 1;
		damage = 1.5;
		hp = 1500.0;
		movementSpeed = 0.2;
		player->money -= cost[level-1];		// zap³ata za mrówkê
		width = 147;
		height = 66;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 985 - height);
		rect.setPosition(sprite.getPosition());

		//textureAnt.loadFromFile("graphics/ant_2.png");
		//sprite.setTexture(textureAnt);
	}
};


class Ant_l2 : public Ant {

public:

	Ant_l2(Player* player):Ant(player) {
		level = 2;
		damage = 1.5;
		hp = 1500.0;
		movementSpeed = 0.2;
		player->money -= cost[level-1];		// zap³ata za mrówkê
		width = 221;
		height = 94;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 985 - height);
		rect.setPosition(sprite.getPosition());

		//textureAnt.loadFromFile("graphics/ant_2.png");
		//sprite.setTexture(textureAnt);
	}
};

class Ant_l3 : public Ant {

public:

	Ant_l3(Player* player) :Ant(player) {
		level = 3;
		damage = 1.5;
		hp = 1500.0;
		movementSpeed = 0.2;
		player->money -= cost[level-1];		// zap³ata za mrówkê
		width = 260;
		height = 98;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 985 - height);
		rect.setPosition(sprite.getPosition());

		//textureAnt.loadFromFile("graphics/ant_2.png");
		//sprite.setTexture(textureAnt);
	}
};

class Ant_l4 : public Ant {

public:

	Ant_l4(Player* player) :Ant(player) {
		level = 4;
		damage = 1.5;
		hp = 1500.0;
		movementSpeed = 0.2;
		player->money -= cost[level-1];		// zap³ata za mrówkê
		width = 147;
		height = 66;
		//textureAnt.loadFromFile("graphics/ant_2.png");
		//sprite.setTexture(textureAnt);
	}
};

class Ant_l5 : public Ant {

public:

	Ant_l5(Player* player) :Ant(player) {
		level = 5;
		damage = 1.5;
		hp = 1500.0;
		movementSpeed = 0.2;
		player->money -= cost[level-1];		// zap³ata za mrówkê
		width = 147;
		height = 66;
		//textureAnt.loadFromFile("graphics/ant_2.png");
		//sprite.setTexture(textureAnt);
	}
};

class Ant_l6 : public Ant {

public:

	Ant_l6(Player* player) :Ant(player) {
		level = 6;
		damage = 1.5;
		hp = 1500.0;
		movementSpeed = 0.2;
		player->money -= cost[level-1];		// zap³ata za mrówkê
		width = 147;
		height = 66;
		//textureAnt.loadFromFile("graphics/ant_2.png");
		//sprite.setTexture(textureAnt);
	}
};

class Ant_l7 : public Ant {

public:

	Ant_l7(Player* player) :Ant(player) {
		level = 7;
		damage = 1.5;
		hp = 1500.0;
		movementSpeed = 0.2;
		player->money -= cost[level-1];		// zap³ata za mrówkê
		width = 147;
		height = 66;
		//textureAnt.loadFromFile("graphics/ant_2.png");
		//sprite.setTexture(textureAnt);
	}
};

