#include "States.h"
#include "../utils.h"

namespace States {

	DeathState::DeathState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score) : State(frameClock), score(score) {


		//GameTitle
		gameOverTitle.setString("Game Over");
		gameOverTitle.setCharacterSize(170);

		sf::FloatRect titleBounds = gameOverTitle.getLocalBounds();
		gameOverTitle.setPosition((window.getSize().x - titleBounds.width) / 2.0f - 450,
			(window.getSize().y - titleBounds.height) / 2.0f - 400);

		gameOvertextList.push_back(&gameOverTitle);

		//Restart Button
		restartButtonText.setString("Press to restart !");

		//button
		restartButton.setSize(sf::Vector2f(550, 100));
		restartButton.setFillColor(sf::Color::Green);
		restartButton.setPosition(300, 250);
		restartButton.setFillColor(sf::Color::Transparent);
		restartButton.setOutlineThickness(5);


		sf::FloatRect buttonBounds = restartButton.getLocalBounds();
		restartButton.setPosition((window.getSize().x - buttonBounds.width) / 2.0f + 10,
			(window.getSize().y - buttonBounds.height) / 2.0f - 25);

		sf::FloatRect restartButtonBounds = restartButtonText.getLocalBounds();
		restartButtonText.setPosition((window.getSize().x - restartButtonBounds.width) / 2.0f - 225,
			(window.getSize().y - restartButtonBounds.height) / 2.0f - 70);

		restartButtonText.setCharacterSize(60);
		gameOvertextList.push_back(&restartButtonText);

		gameOverScreenRectangle.setSize(sf::Vector2f(window.getSize().x - 100, window.getSize().y - 100));
		gameOverScreenRectangle.setOutlineColor(sf::Color::White);
		gameOverScreenRectangle.setFillColor(sf::Color::Transparent);
		gameOverScreenRectangle.setOutlineThickness(10);
		gameOverScreenRectangle.setPosition(sf::Vector2f(30, 30));

		//Menu Button
		mainMenuText.setString("Main Menu !");

		//button
		mainMenuButton.setSize(sf::Vector2f(550, 100));
		mainMenuButton.setFillColor(sf::Color::Green);
		mainMenuButton.setPosition(300, 250);
		mainMenuButton.setFillColor(sf::Color::Transparent);
		mainMenuButton.setOutlineThickness(5);


		sf::FloatRect mainMenubuttonBounds = mainMenuButton.getLocalBounds();
		mainMenuButton.setPosition((window.getSize().x - mainMenubuttonBounds.width) / 2.0f + 10,
			(window.getSize().y - mainMenubuttonBounds.height) / 2.0f + 115);

		sf::FloatRect mainMenuButtons = mainMenuText.getLocalBounds();
		mainMenuText.setPosition((window.getSize().x - mainMenuButtons.width) / 2.0f - 150,
			(window.getSize().y - mainMenuButtons.height) / 2.0f + 70);

		mainMenuText.setCharacterSize(60);
		gameOvertextList.push_back(&mainMenuText);

		//Score

		sf::FloatRect scoreTextBounds = endScoreText.getLocalBounds();
		endScoreText.setPosition((window.getSize().x - scoreTextBounds.width) / 2.0f - 125,
			(window.getSize().y - scoreTextBounds.height) / 2.0f - 170);

		endScoreText.setCharacterSize(40);
		gameOvertextList.push_back(&endScoreText);

		endScoreText.setFont(MyFont);
		endScoreText.setFillColor(sf::Color::White);
		endScoreText.setStyle(sf::Text::Bold);

		//Credit

		for (int i = 0; i < 4; i++)
		{
			sf::Text* creditText = new sf::Text;
			creditText->setCharacterSize(40);
			creditText->setString("Tome Bourdie");
			if (i == 1) creditText->setString("Volodia Bussereau");
			if (i == 2) creditText->setString("Shahine Benthanane");
			if (i == 3) creditText->setString("Pierre Lamare");

			sf::FloatRect creditBounds = creditText->getLocalBounds();
			creditText->setPosition((window.getSize().x - creditBounds.width) / 2.0f - 150,
				(window.getSize().y - creditBounds.height) / 2.0f + 200 + i * 60); // Modifiez cette valeur pour changer l'écart entre les titres

			gameOvertextList.push_back(creditText);
		}

		for (sf::Text* text : gameOvertextList)
		{
			text->setFont(MyFont);
			text->setFillColor(sf::Color::White);
			text->setStyle(sf::Text::Bold);
		}
	}

	void DeathState::Loop(sf::RenderWindow& window, int& sceneIndex) {
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

			default:
				break;
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					if (restartButton.getGlobalBounds().contains(mousePosition)) {
						sceneIndex = 1;
					}
					if (mainMenuButton.getGlobalBounds().contains(mousePosition)) {
						sceneIndex = 0;
					}
				}
			}
		}


		float deltaTime = frameClock.restart().asSeconds();
		colorClock += deltaTime;

		if (colorClock >= 0.1) {
			gameOverTitle.setFillColor(colorList[rand() % colorList.size()]);
			gameOverScreenRectangle.setOutlineColor(colorList[rand() % colorList.size()]);
			colorClock = 0;
		}

		endScoreText.setString("Your score : " + Utils::toString(score));

		// Remise au noir de toute la fenêtre
		window.clear();

		// Tout le rendu va se dérouler ici

		for (sf::Text* text : gameOvertextList)
		{
			window.draw(*text);
		}
		window.draw(gameOverScreenRectangle);
		window.draw(restartButton);
		window.draw(mainMenuButton);

		// On présente la fenêtre sur l'écran
		window.display();
	}
}

