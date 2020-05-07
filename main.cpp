#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
	
	// Renderowanie okna gry
	VideoMode vm(1920, 1080);
	CreateWindow window(vm, "Age of Ants", Style::Fullscreen);
}

struct mruwa {
	char type;		//Typ mruwy
	int hp;			//Aktualne HP danej mruwy
	int maxhp;		//Maksymalne HP tej mruwy, zalozmy ze mrowka kazdego typu ma inne HP. Wojownik koks, robotnica na hita itd
	int strenght;	//Sila gryzacej mruwencji
	int speed;		//Predkosc poruszania sie
};
