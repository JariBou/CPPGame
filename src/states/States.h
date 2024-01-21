#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace Entities{
	class Foe;
	class UpgradeBox;
	class Player;
}

class UpgradeBoxSpawner;
class EnemySpawner;
class WaveManager;
class GameManager;

namespace States {

	class State {
	public:
		State(sf::Clock& frameClock) : frameClock(frameClock){}

		virtual void Loop(sf::RenderWindow& window, int& sceneIndex) = 0;
		sf::Clock& frameClock;
	};


	class MenuState : public State{
	public:

		MenuState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock);

		void Loop(sf::RenderWindow& window, int& sceneIndex);
	private:
		std::vector<sf::Color> colorList = { sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Magenta };

		std::vector<sf::Text*> textList;
		float colorClock = 0;
		sf::Text gameTitle;
		sf::Text anyKeyText;
		sf::RectangleShape titleScreenRectangle;
	};

	class DeathState : public State{
	public:

		DeathState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score);

		void Loop(sf::RenderWindow& window, int& sceneIndex);
		std::vector<sf::Text*> gameOvertextList;

	private:
		std::vector<sf::Color> colorList = { sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Magenta };


		sf::Text gameOverTitle;
		sf::Text restartButtonText;
		sf::Text menuButtonText;
		sf::Text endScoreText;
		sf::Text mainMenuText;
		sf::RectangleShape mainMenuButton;
		sf::RectangleShape restartButton;
		sf::RectangleShape menuButton;
		sf::RectangleShape gameOverScreenRectangle;

		float colorClock = 0;
		int& score;
	};

	class GameState : public State{

	public:
		std::vector<Entities::Foe*> foeList;
		std::vector<Entities::UpgradeBox*> upgradeBoxList;

		// Using pointers so that we dont get include problems for now, maybe change later idk
		UpgradeBoxSpawner* upgradeBoxSpawner;
		EnemySpawner* enemySpawner;
		WaveManager* waveManager;
		GameManager* gameManager;
		Entities::Player* player;
		sf::Text anouncingWaveText;

		GameState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score);

		void CreateNeonGrid(int windowWidth, int windowHeight);

		void Loop(sf::RenderWindow& window, int& sceneIndex);

		void Restart(sf::RenderWindow& window);

	private:
		sf::Text scoreText;
		sf::RectangleShape rectangle;
		sf::Text lifeText;
		sf::VertexArray grid;
		int& score;
		int gridSize = 150;

		sf::CircleShape triangleUpgrade = sf::CircleShape(40, 3);
		sf::Text lvlTriangle;

		sf::CircleShape octogonUpgrade = sf::CircleShape(30, 8);
		sf::Text lvlOctogon;

		sf::RectangleShape rectangleUpgrade = sf::RectangleShape(sf::Vector2f(50, 50));
		sf::Text lvlRectangle;

		sf::CircleShape circleUpgrade = sf::CircleShape(30.f);
		sf::Text lvlCircle;

	};
}

