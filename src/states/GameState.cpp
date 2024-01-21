#include "States.h"
#include "../entities/Entites.h"
#include "../UpgradeBoxSpawner.h"
#include "../EnemySpawner.h"
#include "../WaveManager.h"
#include "../GameManager.h"
#include "../particles/ParticleSystem.h"
#include "../utils.h"

namespace States {
	GameState::GameState(sf::RenderWindow& window, sf::Font& MyFont, sf::Clock& frameClock, int& score) : State(frameClock), score(score)
	{
		this->gameManager = new GameManager(window, score);
		this->gameManager->SetParticleSystem(new SFX::ParticleSystem());

		scoreText.setCharacterSize(40);
		scoreText.setPosition(5, 5);
		scoreText.setFont(MyFont);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setStyle(sf::Text::Bold);

		rectangle.setSize(sf::Vector2f(64, 64));
		player = new Entities::Player(rectangle, gameManager);
		player->SetColor(sf::Color::Transparent, sf::Color::Green);
		player->SetPosition(sf::Vector2f((window.getSize().x / 2.), (window.getSize().y / 2.)));

		lifeText.setFont(MyFont);
		lifeText.setCharacterSize(50);
		lifeText.setFillColor(sf::Color::White);

		sf::FloatRect lifeBounds = lifeText.getLocalBounds();
		lifeText.setPosition((window.getSize().x - lifeBounds.width) / 2.0f + 700,
			(window.getSize().y - lifeBounds.height) / 2.0f - 520);

		this->upgradeBoxSpawner = new UpgradeBoxSpawner(upgradeBoxList, window.getSize().x, gameManager);
		this->enemySpawner = new EnemySpawner(&foeList, &window, gameManager);	

		anouncingWaveText.setCharacterSize(100);
		sf::FloatRect waveTextBounds = anouncingWaveText.getLocalBounds();
		anouncingWaveText.setPosition((window.getSize().x - waveTextBounds.width) / 2.0f - 100, (window.getSize().y - waveTextBounds.height) / 4.0f - 70);
		anouncingWaveText.setFont(MyFont);
		anouncingWaveText.setFillColor(sf::Color::White);
		anouncingWaveText.setStyle(sf::Text::Bold);

		//Power up
		//Triangle
		triangleUpgrade.setFillColor(sf::Color::Transparent);
		triangleUpgrade.setOutlineThickness(5);
		triangleUpgrade.setOutlineColor(sf::Color::Yellow);

		lvlTriangle.setCharacterSize(30);
		lvlTriangle.setFont(MyFont);
		lvlTriangle.setFillColor(sf::Color::White);
		lvlTriangle.setStyle(sf::Text::Bold);

		sf::FloatRect triangleBounds = triangleUpgrade.getLocalBounds();
		triangleUpgrade.setPosition((window.getSize().x - triangleBounds.width) / 2.0f - 880,
			(window.getSize().y - triangleBounds.height) / 2.0f - 400);

		sf::FloatRect lvlTriangleBounds = lvlTriangle.getLocalBounds();
		lvlTriangle.setPosition((window.getSize().x - lvlTriangleBounds.width) / 2.0f - 895,
			(window.getSize().y - lvlTriangleBounds.height) / 2.0f - 370);

		//Octogone
		octogonUpgrade.setFillColor(sf::Color::Transparent);
		octogonUpgrade.setOutlineThickness(5);
		octogonUpgrade.setOutlineColor(sf::Color::Blue);

		lvlOctogon.setCharacterSize(30);
		lvlOctogon.setFont(MyFont);
		lvlOctogon.setFillColor(sf::Color::White);
		lvlOctogon.setStyle(sf::Text::Bold);

		sf::FloatRect octogonBounds = octogonUpgrade.getLocalBounds();
		octogonUpgrade.setPosition((window.getSize().x - octogonBounds.width) / 2.0f - 880,
			(window.getSize().y - octogonBounds.height) / 2.0f - 270);

		sf::FloatRect lvlOctogonBounds = lvlOctogon.getLocalBounds();
		lvlOctogon.setPosition((window.getSize().x - lvlOctogonBounds.width) / 2.0f - 895,
			(window.getSize().y - lvlOctogonBounds.height) / 2.0f - 240);

		//Rectangle
		rectangleUpgrade.setFillColor(sf::Color::Transparent);
		rectangleUpgrade.setOutlineThickness(5);
		rectangleUpgrade.setOutlineColor(sf::Color::Magenta);

		lvlRectangle.setCharacterSize(30);
		lvlRectangle.setFont(MyFont);
		lvlRectangle.setFillColor(sf::Color::White);
		lvlRectangle.setStyle(sf::Text::Bold);

		sf::FloatRect rectangleBounds = rectangleUpgrade.getLocalBounds();
		rectangleUpgrade.setPosition((window.getSize().x - rectangleBounds.width) / 2.0f - 880,
			(window.getSize().y - rectangleBounds.height) / 2.0f - 150);

		sf::FloatRect lvlRectangleBounds = lvlRectangle.getLocalBounds();
		lvlRectangle.setPosition((window.getSize().x - lvlRectangleBounds.width) / 2.0f - 895,
			(window.getSize().y - lvlRectangleBounds.height) / 2.0f - 120);

		//Circle
		circleUpgrade.setFillColor(sf::Color::Transparent);
		circleUpgrade.setOutlineThickness(5);
		circleUpgrade.setOutlineColor(sf::Color::Green);

		lvlCircle.setCharacterSize(30);
		lvlCircle.setFont(MyFont);
		lvlCircle.setFillColor(sf::Color::White);
		lvlCircle.setStyle(sf::Text::Bold);

		sf::FloatRect circleBounds = circleUpgrade.getLocalBounds();
		circleUpgrade.setPosition((window.getSize().x - circleBounds.width) / 2.0f - 880,
			(window.getSize().y - circleBounds.height) / 2.0f - 20);

		sf::FloatRect lvlCircleBounds = lvlCircle.getLocalBounds();
		lvlCircle.setPosition((window.getSize().x - lvlCircleBounds.width) / 2.0f - 895,
			(window.getSize().y - lvlCircleBounds.height) / 2.0f + 10);

		this->waveManager = new WaveManager(enemySpawner, &anouncingWaveText, gameManager);
		waveManager->SetWave(0, 30);

		//GRID ACTIVATION
		grid = sf::VertexArray(sf::Lines);
		CreateNeonGrid(window.getSize().x, window.getSize().y);

		
	}

	void States::GameState::CreateNeonGrid(int windowWidth, int windowHeight)
	{
		const int numberOfLines = 15; // Nombre de lignes verticales et horizontales

		sf::Color color = sf::Color::Green;

		for (int i = 0; i < numberOfLines; ++i) {
			float thicknessFactor = static_cast<float>(i) / numberOfLines; // Facteur d'�paisseur bas� sur la distance du point de fuite

			// Lignes horizontales
			grid.append(sf::Vertex(sf::Vector2f(0, i * windowHeight / numberOfLines), color));
			grid.append(sf::Vertex(sf::Vector2f(windowWidth, i * windowHeight / numberOfLines), color));

			// Lignes verticales
			grid.append(sf::Vertex(sf::Vector2f(i * windowWidth / numberOfLines, 0), color));
			grid.append(sf::Vertex(sf::Vector2f(i * windowWidth / numberOfLines, windowHeight), color));
		}
	}

	void GameState::Restart(sf::RenderWindow& window) {
		foeList.clear();
		gameManager->Reset();

		player->lives = 3;
		player->SetPosition(sf::Vector2f((window.getSize().x / 2.), (window.getSize().y / 2.)));

		//On reset les niveaux des upgrades
		player->bulletDamageLevel = 1;
		player->bulletSpeedLevel = 1;
		player->movementSpeedLevel = 1;
		player->bulletNumberLevel = 1;

		//On reset les stats du joueur
		player->bulletCooldown = 0.5f;
		player->bulletDamage = 10;
		player->bulletSize = sf::Vector2f(10, 10);
		player->bulletClock = 0;
		player->nbBulletShot = 1;
		player->speed = 450.0;


		//On reset les vagues d'enemies
		waveManager->clock = 0;
		waveManager->waveCooldown = 3;
		waveManager->wave = 0;
		waveManager->anouncing = false;
		waveManager->SetWave(0, 10 /*30*/);

		//On reset le score
		score = 0;

		window.clear();
	}

	float gridSpeed = 1.0f;

	void GameState::Loop(sf::RenderWindow& window, int& sceneIndex)
	{
		if (!player->CheckLife()) {
			sceneIndex = 2;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			// On g�re l'�v�n�ment
			switch (event.type)
			{
			case sf::Event::Closed:
				// L'utilisateur a cliqu� sur la croix => on ferme la fen�tre
				window.close();
				break;

			default:
				break;
			}
		}

		gridSize = 25;

		for (int i = 0; i < grid.getVertexCount(); ++i) {

			if (i % 4 == 0 || i % 4 == 1) {
				// Pour les lignes horizontal, déplacez-les vers le bas
				grid[i].position.y += gridSpeed;

				if (grid[i].position.y > window.getSize().y) {
					grid[i].position.y = -gridSize; // Réinitialisation en haut de l'écran
				}
			}

		}

		float deltaTime = frameClock.restart().asSeconds();
		//std::cout << 1.f / deltaTime << " FPS" << std::endl;

		lifeText.setString("Life: " + std::to_string(player->lives));
		scoreText.setString("Score : " + Utils::toString(score));
		//std::cout<< "Score : " + Utils::toString(score);

		//upgradeBoxSpawner.TrySpawning(deltaTime);

		player->MovePlayer(deltaTime);

		player->Update(deltaTime); // This needs to change

		for (Entities::Bullet* bullet : *gameManager->GetBullets())
		{
			bullet->Update(deltaTime);
		}

		upgradeBoxSpawner->Update(deltaTime);

		for (Entities::Foe* en : *(enemySpawner->GetFoes())) {
			en->Update(deltaTime);
		}

		Utils::CheckBulletListLife(*gameManager->GetBullets());
		Utils::CheckFoeListLife(*enemySpawner->GetFoes());
		Utils::CheckUpgradeListLife(*upgradeBoxSpawner->GetUpgradeBoxList());

		enemySpawner->Update(deltaTime);
		waveManager->Update(deltaTime);
 		this->gameManager->GetParticleSystem()->Update(deltaTime);

		// Affichage

		// Remise au noir de toute la fen�tre
		window.clear();

		// Tout le rendu va se d�rouler ici
		//window.draw(rectangle);

		window.draw(scoreText);
		if (waveManager->anouncing) window.draw(anouncingWaveText);
		player->Draw(window);

		window.draw(lifeText);
		window.draw(grid);

		if (player->movementSpeedLevel <= 11)
		{
			lvlTriangle.setString(Utils::toString(player->movementSpeedLevel));
			window.draw(triangleUpgrade);
			window.draw(lvlTriangle);
		}else if (player->movementSpeedLevel == 12)
		{
			lvlTriangle.setString("MAX");
			window.draw(triangleUpgrade);
			window.draw(lvlTriangle);
		}
		if (player->bulletDamageLevel <= 7) {

			lvlOctogon.setString(Utils::toString(player->bulletDamageLevel));
			window.draw(octogonUpgrade);
			window.draw(lvlOctogon);
		}else if (player->bulletDamageLevel == 8)
		{
			lvlOctogon.setString("MAX");
			window.draw(octogonUpgrade);
			window.draw(lvlOctogon);
		}
		if (player->bulletSpeedLevel <= 9) {

			lvlRectangle.setString(Utils::toString(player->bulletSpeedLevel));
			window.draw(rectangleUpgrade);
			window.draw(lvlRectangle);
		}else if (player->bulletSpeedLevel == 10)
		{
			lvlOctogon.setString("MAX");
			window.draw(rectangleUpgrade);
			window.draw(lvlRectangle);
		}
		if (player->bulletNumberLevel <= 3) {

			lvlCircle.setString(Utils::toString(player->bulletNumberLevel));
			window.draw(circleUpgrade);
			window.draw(lvlCircle);
		}else if (player->bulletNumberLevel == 4)
		{
			lvlCircle.setString("MAX");
			window.draw(circleUpgrade);
			window.draw(lvlCircle);
		}

		for (Entities::Bullet* bullet : *gameManager->GetBullets())
		{
			bullet->Draw(window);
		}

		for (Entities::Foe* en : foeList) {
			en->Draw(window);
		}

		for (Entities::UpgradeBox* box : *upgradeBoxSpawner->GetUpgradeBoxList()) {
			box->Draw(window);
		}

		this->gameManager->GetParticleSystem()->Draw(window);

		// On pr�sente la fen�tre sur l'�cran
		window.display();
	}

}

