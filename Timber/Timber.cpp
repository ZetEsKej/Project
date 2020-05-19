// Timber.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
	//Tworzenie objektu videomode
	VideoMode vm(1920, 1080);
	//Tworzenie i otwarcie okienka gry
	RenderWindow window(vm, "TIMBER!!!", Style::Fullscreen);
	//Przygotowanie tekstury tylniej
	Texture textureBackground;
	//Załadowanie pliku do tekstury
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
	//Czy chmurka jest aktywna
	bool cloudActive = false;
	//Prędkość chmurki
	double cloudSpeed = 0.0f;
	//Wartość do kontrolowania czasu
	Clock clock;

	while(window.isOpen())
	{
	/*
	Player input
	*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
	/*
	Aktualizacja sceny - Update Scene
	*/
		Time dt = clock.restart();
		if(!cloudActive)
		{
			//Jak szybka jest chmurka
			srand((int)time(0));
			cloudSpeed = (rand() % 200);
			
			//Jak wysoko jest chmurka
			srand((int)time(0)*10);
			float height = (rand() % 150);
			spriteCloud.setPosition(-200, height);
			cloudActive = true;
		
		}
		else 
		{
			spriteCloud.setPosition(
				spriteCloud.getPosition().x + (cloudSpeed * dt.asSeconds()),
				spriteCloud.getPosition().y);
			if(spriteCloud.getPosition().x>1920)
			{
				cloudActive = false;
			}
		}
	/*
	Rysowanie sceny - Draw Scene
	*/
	//Usuniecie wszystkiego z ostatniego frame'a - Clear from last frame
		window.clear();
	//Rysowanie sceny gry tutaj - Draw Game Scene Here
		window.draw(spriteBackground);
	//Rysowanie chmury
		window.draw(spriteCloud);
	//Pokaz wszystko co narysowaliśmy - Show everything we drew
		window.display();
	}
	return 0;
}