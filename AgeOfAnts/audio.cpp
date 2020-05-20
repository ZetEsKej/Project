#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Sounds {

public:

	void backgroundPlay() {
		Music backgroundMusic;
		backgroundMusic.openFromFile("audio/backgroundMusic.wav");
		backgroundMusic.setLoop(true);
		backgroundMusic.setVolume(30.f);
	}

	void hitPlay() {
		SoundBuffer hitBuffer;
		hitBuffer.loadFromFile("audio/hitSound.wav");
		Sound hitSound;
		hitSound.setBuffer(hitBuffer);
		hitSound.setLoop(true);
		hitSound.setVolume(120.f);
	}

	static void deathPlay() {
		SoundBuffer deathBuffer;
		deathBuffer.loadFromFile("audio/deathSound.wav");
		Sound deathSound;
		deathSound.setBuffer(deathBuffer);
		deathSound.setVolume(120.f);
		deathSound.play();
	}
};