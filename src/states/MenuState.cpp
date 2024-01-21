#include "States.h"
#include <iostream>

namespace States {
	MenuState::MenuState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock)
		: State(frameClock) {

		this->gameTitle.setString("2042");
		this->gameTitle.setCharacterSize(400);
		this->gameTitle.setPosition(270, window.getSize().y / 8);
		this->textList.push_back(&this->gameTitle);

		sf::FloatRect gameTitleBounds = gameTitle.getLocalBounds();
		gameTitle.setPosition((window.getSize().x - gameTitleBounds.width) / 2.0f - 450,
			(window.getSize().y - gameTitleBounds.height) / 2.0f - 500);

		this->anyKeyText.setString("Press any key to continue !");
		this->anyKeyText.setPosition(600, window.getSize().y / 2);
		this->anyKeyText.setCharacterSize(60);
		this->textList.push_back(&this->anyKeyText);

		this->titleScreenRectangle.setSize(sf::Vector2f(window.getSize().x - 100, window.getSize().y - 100));
		this->titleScreenRectangle.setOutlineColor(sf::Color::White);
		this->titleScreenRectangle.setFillColor(sf::Color::Transparent);
		this->titleScreenRectangle.setOutlineThickness(10);
		this->titleScreenRectangle.setPosition(sf::Vector2f(30, 30));

		for (sf::Text* text : textList)
		{
			text->setFont(MyFont);
			text->setFillColor(sf::Color::White);
			text->setStyle(sf::Text::Bold);
		}
	}

	void MenuState::Loop(sf::RenderWindow& window, int& sceneIndex) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
			case sf::Event::Closed:
				// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
				window.close();
				break;

			case sf::Event::KeyPressed:
				sceneIndex = 1;
				break;
			default:
				break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();
		colorClock += deltaTime;

		if (colorClock >= 0.3) {
			gameTitle.setFillColor(colorList[rand() % colorList.size()]);
			titleScreenRectangle.setOutlineColor(colorList[rand() % colorList.size()]);
			colorClock = 0;
		}

		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici

		window.draw(this->gameTitle);
		window.draw(this->anyKeyText);
		window.draw(this->titleScreenRectangle);


		// On présente la fenêtre sur l'écran
		window.display();
	}
}
