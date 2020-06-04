#pragma once

#include "ant.cpp"

class WaterDrop : public Object {
    
public:
    float damage;
    float speed;
    bool isActive;

    WaterDrop(int positionX, int positionY) {
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(positionX, positionY);
        rect.setSize(sf::Vector2f(50, 100));
        damage = 1000.0;
        speed = 7.0;
		isActive = true;
    }

    void move() {
        //sprite.move(0, -speed);
	    rect.move(0, speed);
    }

    void dropDamage(Ant* &ant) {
        ant->hp -= damage;
    }

    static void rainCheckForCollision(std::vector<Ant*> &ants, std::vector<WaterDrop*> &waterDrops) {
        
        for (int i = 0; i < waterDrops.size(); i++) {
			
			int leftBottomOfDrop[2] = { waterDrops[i]->rect.getPosition().x, waterDrops[i]->rect.getPosition().y + waterDrops[i]->rect.getSize().y };     // [x, y]
			int rightBottomOfDrop[2] = { waterDrops[i]->rect.getPosition().x + waterDrops[i]->rect.getSize().x, waterDrops[i]->rect.getPosition().y + waterDrops[i]->rect.getSize().y }; // [x, y]

            for (int j = 0; j < ants.size(); j++) {

				int leftTopOfAnt[2] = { ants[j]->rect.getPosition().x + 20, ants[j]->rect.getPosition().y + 7 };     // [x, y]
				int rightTopOfAnt[2] = { ants[j]->rect.getPosition().x + ants[j]->rect.getSize().x - 20, ants[j]->rect.getPosition().y + 7 }; // [x, y]

                if (leftBottomOfDrop[0] > leftTopOfAnt[0] && leftBottomOfDrop[0] < rightTopOfAnt[0] && leftBottomOfDrop[1] > leftTopOfAnt[1] && leftBottomOfDrop[1]) {
                    waterDrops[i]->dropDamage(ants[j]);
                    waterDrops[i]->isActive = false;
					std::cout << "DMGGGG" << std::endl;

                }
                else if (rightBottomOfDrop[0] > leftTopOfAnt[0] && rightBottomOfDrop[0] < rightTopOfAnt[0] && rightBottomOfDrop[1] > leftTopOfAnt[1]) {
                    waterDrops[i]->dropDamage(ants[j]);
                    waterDrops[i]->isActive = false;
					std::cout << "DMGGGG" << std::endl;

                }
            }
			if (leftBottomOfDrop[1] >= 1000)								// kropla doleciała do ziemi
				waterDrops[i]->isActive = false;
        }
    }

    static void checkForInactive(std::vector<WaterDrop*> &waterDrops) {

        for (int i = 0; i < waterDrops.size(); i++) {
            if(waterDrops[i]->isActive == false) {
                waterDrops.erase(waterDrops.begin()+i);
                i--;
            }
        }
    }




	// main
	//
	//std::vector<WaterDrop*> waterDrops;
	//
	////// przycisk dodania deszczu
	////Texture rainButtonTexture;										// jajeczko przy walucie
	////rainTexture.loadFromFile("graphics/UI/jajco.png");
	////Sprite rainButton;
	////rainButton.setTexture(rainButtonTexture);
	////rainButton.setPosition(500, 44);
	////
	//
	//WaterDrop::checkForInactive(waterDrops);                        // sprawdzenie, czy jakieś krople spadły na ziemię
	//
	//
	//for(int i = 0; i < waterDrops.size(); i++)						// poruszanie kropel wody
	//    waterDrops[i].move();
	//
	//if(waterDrops.size() > 0)
	//    WaterDrop::rainCheckForCollision(opponents, waterDrops);        // sprawdzenie kolizji mrówek z kroplami wody i ew. zadanie obrażeń
	//
	////// rysowanie kropel wody
	////for(int i = 0; i < waterDrops.size(); i++) {            
	////    window.draw(waterDrops[i].sprite);
	////    window.draw(waterDrops[i].rect);
	////}
	//

};