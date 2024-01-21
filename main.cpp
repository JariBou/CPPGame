#include <SFML/Window.hpp>
#include <iostream>
#include "src/states/States.h"
#include <windows.h>
#include <SFML/Audio.hpp>

int main()
{
	// Initialisation

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars", sf::Style::Titlebar | sf::Style::Close);
	ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
	window.setVerticalSyncEnabled(true);
	srand(time(NULL));

	sf::Image icon;
	if (!icon.loadFromFile("../logo.jpg")) {}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Hand)) {
		window.setMouseCursor(cursor);
	}

	sf::Font MyFont;
	if (!MyFont.loadFromFile("../font/Roboto-Black.ttf"))
	{
		std::cout << "Erreur" << std::endl;
	}

	sf::Clock frameClock;
	int _previousScene = 0;
	int _scene = 0;
	int score = 0;

	sf::Music music;

	States::MenuState menuState(window, MyFont, frameClock);
	States::GameState gameState(window, MyFont, frameClock, score);
	States::DeathState deathState(window, MyFont, frameClock, score);

	while (window.isOpen())
	{
		if (_previousScene != _scene) {
			if (_previousScene == 2 || _previousScene == 0) {
				gameState.Restart(window);
				//MUSIC
				if (!music.openFromFile("../src/resources/Chop Suey [8 Bit Cover Tribute to System of a Down] - 8 Bit Universe.mp3")) {
					std::cout << "Erreur lors du chargement de la musique\n";
				}

				music.setLoop(true);
				music.play();
			}
			else {
				music.stop();
			}
			_previousScene = _scene;
		}
		if (_scene == 0) {
			window.setMouseCursorVisible(true);
			menuState.Loop(window, _scene);
		}
		else if (_scene == 1) {
			window.setMouseCursorVisible(false);
			gameState.Loop(window, _scene);
		}
		else if (_scene == 2) {
			window.setMouseCursorVisible(true);
			deathState.Loop(window, _scene);
		}
	}
	
}