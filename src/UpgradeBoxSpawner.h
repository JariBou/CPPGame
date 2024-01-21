#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

namespace Entities {
	class DrawableEntity;
	class UpgradeBox;
	class Player;
}

class GameManager;

class UpgradeBoxSpawner {
	public :
		UpgradeBoxSpawner(std::vector<Entities::UpgradeBox*>& upgradeBoxList, int WindowWidth, GameManager* pGameManager);
		~UpgradeBoxSpawner() = default;
		virtual void SpawnUpgradeBox(sf::Shape* shape);
		std::vector<Entities::UpgradeBox*>* GetUpgradeBoxList();
		std::vector<Entities::DrawableEntity*>& GetUpgradeBoxEntities();
		int windowWidth; 
		Entities::Player* player;
		void Update(float deltaTime);
		float spawnCooldown = 2;
		float spawnTimer = 0;

	private:
		GameManager* gameManager;
		std::vector<Entities::UpgradeBox*> upgradeBoxList;

};