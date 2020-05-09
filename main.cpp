#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
	
	// Renderowanie okna gry
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Age of Ants", Style::Fullscreen);
	View view = window.getView();
	Texture textureBackground;
	//Za³adowanie pliku do tekstury
	textureBackground.loadFromFile("graphics/background.jpg");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);
	//Tworzenie sprite chmurki
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/Cloud.png");
	Sprite spriteCloud;
	spriteCloud.setTexture(textureCloud);
	spriteCloud.setPosition(0, 0);
	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::M))
		{
			view.zoom(0.5f);

		}
		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
		{
			view.move(4.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
		{
			view.move(-4.f, 0.f);
		}

		window.clear();
		//Rysowanie sceny gry tutaj - Draw Game Scene Here
		window.draw(spriteBackground);
		//Rysowanie chmury
		window.draw(spriteCloud);
		window.setView(view);
		//Pokaz wszystko co narysowaliœmy - Show everything we drew
		window.display();
	}
}

struct mruwa {
	char type;		//Typ mruwy
	int hp;			//Aktualne HP danej mruwy
	int maxhp;		//Maksymalne HP tej mruwy, zalozmy ze mrowka kazdego typu ma inne HP. Wojownik koks, robotnica na hita itd
	int strenght;	//Sila gryzacej mruwencji
	int speed;		//Predkosc poruszania sie
};
