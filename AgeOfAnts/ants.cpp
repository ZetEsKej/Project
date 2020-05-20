#include "ant.cpp"

class Ant_l1 : public Ant { // melee 1 

public:

	Ant_l1(Player* player) :Ant(player) {
		level = 1;
		damage = 6.05;
		hp = 2000.0;
		movementSpeed = 2.18;
		player->money -= cost[level - 1];		// zap³ata za mrówkê
		width = 149;
		height = 66;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 985 - height);
		rect.setPosition(sprite.getPosition());

	}
};


class Ant_l2 : public Ant { // melee 2 

public:

	Ant_l2(Player* player) :Ant(player) {
		level = 2;
		damage = 8.47;
		hp = 2400.0;
		movementSpeed = 1.92;
		player->money -= cost[level - 1];		// zap³ata za mrówkê
		width = 220;
		height = 94;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 995 - height);
		rect.setPosition(sprite.getPosition());
	}
};

class Ant_l3 : public Ant { // melee 3

public:

	Ant_l3(Player* player) :Ant(player) {
		level = 3;
		damage = 10.89;
		hp = 2800.0;
		movementSpeed = 1.68;
		player->money -= cost[level - 1];		// zap³ata za mrówkê
		width = 294;
		height = 112;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 990 - height);
		rect.setPosition(sprite.getPosition());

	}
};

class Ant_l4 : public Ant { // latajaca

public:

	Ant_l4(Player* player) :Ant(player) {
		level = 4;
		damage = 15.73;
		hp = 3000.0;
		movementSpeed = 2.4;
		player->money -= cost[level - 1];		// zap³ata za mrówkê
		width = 280;
		height = 235;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 835 - height);
		rect.setPosition(sprite.getPosition());

	}
};

class Ant_l5 : public Ant { // tank 1

public:

	Ant_l5(Player* player) :Ant(player) {
		level = 5;
		damage = 12.1;
		hp = 3500.0;
		movementSpeed = 1.44;
		player->money -= cost[level - 1];		// zap³ata za mrówkê
		width = 356;
		height = 103;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 995 - height);
		rect.setPosition(sprite.getPosition());
	}
};

class Ant_l6 : public Ant { // tank 2

public:

	Ant_l6(Player* player) :Ant(player) {
		level = 6;
		damage = 15.73;
		hp = 4200.0;
		movementSpeed = 1.08;
		player->money -= cost[level - 1];		// zap³ata za mrówkê
		width = 455;
		height = 201;

		rect.setSize(sf::Vector2f(width - 15, height));
		sprite.setPosition(sprite.getPosition().x, 1005 - height);
		rect.setPosition(sprite.getPosition());
	}
};