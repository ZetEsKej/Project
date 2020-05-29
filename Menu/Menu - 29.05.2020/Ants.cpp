#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Main_menu.h"
#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000
using namespace std;
using namespace sf;
int page_number;
int main() {
    sf::Texture texture;
    if (!texture.loadFromFile("pink.jpg")) {}
    sf::Sprite sText(texture);
    RenderWindow window(VideoMode(SCREEN_HIGH, SCREEN_WIDTH-200), "Age of Ants!", Style::Close);
    Main_menu menu(SCREEN_WIDTH, SCREEN_HIGH);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            //Movin in Menu - Up&Down&Selecting start
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) {
                    menu.moveUP();
                    break;
                }
                if (event.key.code == Keyboard::Down) {
                    menu.moveDOWN();
                    break;
                }
                if (event.key.code == Keyboard::Return) {
                    switch (menu.mainMenuPressed()) {
                    case 0:
                        cout << "Play button has been pressed" << endl;
                        break;
                    case 1:
                        cout << "Options button has been pressed" << endl;
                        break;
                    case 2:
                        window.close();
                        cout << "Exit button has been pressed" << endl;
                        break;
                    }
                }
            }
            window.clear();
            window.draw(sText);
            menu.draw(window);
            window.display();
        }
    }
}
