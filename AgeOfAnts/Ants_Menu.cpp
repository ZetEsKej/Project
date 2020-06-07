#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include "Main_menu.h"
#include "Settings.h"
#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000
using namespace std;
using namespace sf;
int page_number;
//Kolor tła
void clear(const Color& color = Color(0, 0, 0, 0)) {

}
int main() {

    bool InMenu = true;
    bool InSettings = false;
    bool InCredits = false;

    enum class State {
        Play,
        Settings,
        Credits,
        Paused,
        MainMenu,
        Game_Over
    };

    State state = State::MainMenu;
    //Zegar
    Clock clock;
    //Czas gry 
    Time gameTime;

    //audio 😮 
   // sf::SoundBuffer soMario;
    //if(!soMario.loadFromFile("Sound_Genau.wav")){}

   // sf::Sound sound; 
    //sound.setBuffer(soMario);
    //sound.play();
    //sound.setLoop(true);
    //sound.setVolume(10.f);
    //Załadowanie grafiki 
    //sf::Texture texture;
    //if (!texture.loadFromFile("pink.jpg")) {}
    //sf::Sprite sText(texture);

    //Manu
    RenderWindow window(VideoMode(SCREEN_HIGH, SCREEN_WIDTH - 200), "Age of Ants!", Style::Close);

    Main_menu menu(SCREEN_WIDTH, SCREEN_HIGH);
    Main_menu settings(SCREEN_WIDTH, SCREEN_HIGH);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            //Movin in Menu - Up&Down&Selecting start
            if (event.type == Event::KeyReleased) {
                if (InMenu == true && event.key.code == Keyboard::Up) {
                    menu.moveUP();
                    break;
                }
                if (InMenu == true && event.key.code == Keyboard::Down) {
                    menu.moveDOWN();
                    break;
                }
                if (InMenu == true && event.key.code == Keyboard::Return) {
                    switch (menu.mainMenuPressed()) {
                    case 0:
                        cout << "Play button has been pressed" << endl;
                        InMenu = false;
                        break;
                    case 1:
                        cout << "Options button has been pressed" << endl;
                        break;
                    case 2:
                        cout << "Tworcy: \nMateusz Osinski\nPawel Jakubowski\nJakub Stroinski\nKlaudiusz Rozenek\nKamil Szymkowiak\nMikolaj Sarnecki\nZ klasy 3B" << endl;
                        break;
                    case 3:
                        window.close();
                        cout << "Exit button has been pressed" << endl;
                        break;
                    }
                }
            }
            window.clear();
            if (InMenu == false) {
                window.setView(view);

                Time time = clock.getElapsedTime();
                clock.restart().asSeconds();

                window.draw(spriteBackground);		// Rysowanie sceny gry

                window.draw(spriteEggs);			// rysowanie UI
                window.draw(playersMoney);
                window.draw(castleLevel);
                window.draw(spriteMute);
                window.draw(textUpgrade);
                window.draw(textMute);

                window.draw(addAntButton_1);		// te dwie mrówki gracz mo¿e zakupiæ od samego pocz¹tku gry
                window.draw(addAntButton_2);
                window.draw(addAntButton_3);
                window.draw(addAntButton_4);
                window.draw(addAntButton_5);
                window.draw(addAntButton_6);

                window.draw(rainButton);

                window.draw(lifeBarCastle->rect);
                window.draw(lifeBarOpponentCastle->rect);

                if (ourCastle->level >= 2) {		// Poziom oblokowuje 2 kolejne mrowki
                    addAntButton_3.setTexture(textureAdd_3);
                    addAntButton_4.setTexture(textureAdd_4);
                }
                if (ourCastle->level >= 3) {		// Poziom oblokowuje 2 kolejne mrowki
                    addAntButton_5.setTexture(textureAdd_5);
                    addAntButton_6.setTexture(textureAdd_6);
                }
                if (ourCastle->level == 2) {		// Zmiana tekstury przycisku Upgrade po pierwszym ulepszeniu
                    spriteUpgrade.setTexture(textureUpgrade2);
                }
                if (ourCastle->level == 3) {		// Zmiana tekstury przycisku Upgrade po pierwszym ulepszeniu
                    spriteUpgrade.setTexture(textureUpgradeDis);
                }
                window.draw(spriteUpgrade);			// UPGRADE BUTTON

                if (isGamePaused)			//tekst paused
                    window.draw(textPause);
                //window.draw(ourCastle->rect);
                //window.draw(opponentsCastle->rect);

                if (drawAnt == true) {
                    for (int i = 0; i < ants.size(); i++) {
                        window.draw(ants[i]->sprite);				//Rysowanie mrówek
                        window.draw(antsLifebars[i]->rect);
                        //window.draw(ants[i]->rect);				//Rysowanie kolizji mrówek
                    }
                    for (int i = 0; i < opponents.size(); i++) {
                        window.draw(opponents[i]->sprite);			//Rysowanie mrówek
                        window.draw(opponentsLifebars[i]->rect);
                        //window.draw(opponents[i]->rect);			//Rysowanie kolizji mrówek
                    }
                    for (int i = 0; i < waterDrops.size(); i++) {	// rysowanie kropel wody
                        window.draw(waterDrops[i]->sprite);
                        //window.draw(waterDrops[i]->rect);
                    }

                }
            }
            //wywołanie koloru tła
            void clear(const Color & color = Color(0, 0, 0, 0));
            //Wywołanie grafiki na tło 
            //window.draw(sText);
            if (InMenu == true) {
                menu.draw(window);
            }
            else if (InMenu == false) {
                InMenu = true;
                if (event.key.code == sf::Keyboard::Escape) {

                }
            }
            window.display();
        }
    }
}
       
        
       
