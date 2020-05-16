#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Main_menu.h"
#define SCREEN_HIGH 1024
#define SCREEN_WIDTH 1000
using namespace std;
using namespace sf;
int page_number;
int main()
{
    RenderWindow window(VideoMode(SCREEN_HIGH, SCREEN_WIDTH), "Age of Ants!", Style::Close);
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
        }
        window.clear();
        menu.draw(window);
        window.display();
    }
}
    