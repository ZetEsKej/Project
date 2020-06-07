#pragma once

#include "rain.h"

WaterDrop::WaterDrop(int positionX, int positionY) {
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(positionX, positionY);
		sprite.setPosition(rect.getPosition());
        rect.setSize(sf::Vector2f(51, 100));
        damage = 1000.0;
        speed = 7.0;
		isActive = true;
}

void WaterDrop::move() {
        sprite.move(0, speed);
	    rect.move(0, speed);
}

void  WaterDrop::dropDamage(Ant* &ant) {
        ant->hp -= damage;
}

   