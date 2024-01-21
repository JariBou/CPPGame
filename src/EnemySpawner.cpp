#include "EnemySpawner.h"
#include "entities/Entites.h"
#include "Spawnpoint.h"
#include "GameManager.h"
#include "WaveManager.h"
#include <cmath>



EnemySpawner::EnemySpawner(std::vector<Entities::Foe*>* foeList, sf::RenderWindow* window, GameManager* pGameManager) : gameManager(pGameManager) {
	this->foeList = foeList;
	this->window = window;
	gameManager->SetEnemySpawner(this);
	this->player = gameManager->GetPlayer();
}

// Yeah so mb We'll have to live with this one being a pointer 'till someone changes it
std::vector<Entities::Foe*>* EnemySpawner::GetFoes() {
	return this->foeList;
}

std::vector<Entities::DrawableEntity*>& EnemySpawner::GetFoeEntities()
{
	std::vector<Entities::DrawableEntity*> vec;
	for (Entities::Foe* foe : *foeList) {
		vec.push_back(foe);
	}
	return vec;
}

void EnemySpawner::SetValuesFromWaves(float speedMultiplier, float healthMultiplier, int maxEnemyEachSpawn)
{
	this->speedMultiplier = speedMultiplier;
	this->healthMultiplier = healthMultiplier;
	this->maxEnemyEachSpawn = maxEnemyEachSpawn;
}

void EnemySpawner::Update(float deltaTime) {
	if (doClock) {
		if (bossWave) {
			SpawnBoss(sf::Vector2f(gameManager->GetWindowDimension().x / 2, 20));
			StopClock();
		}
		clock += deltaTime;
		if (clock >= timeBetweenSpawns) {
			if (bossWave) {

			}
			std::vector<int> spawnpointsUsed;
			int nbEnemySpawned = 1 + rand() % maxEnemyEachSpawn;
			for (size_t i = 0; i < nbEnemySpawned; i++)
			{
				EnemyType enemyType = LinearFoe;
				bool isIn = true;
				int spawnpointIndex;
				while (isIn)
				{
					spawnpointIndex = std::rand() % spawnPoints.size();
					isIn = std::find(spawnpointsUsed.begin(), spawnpointsUsed.end(), spawnpointIndex) != spawnpointsUsed.end();
				}
				spawnpointsUsed.push_back(spawnpointIndex);
				for (EnemyType type : spawnPoints[spawnpointIndex]->possibleEnemiesTypes) {
					if (rand() % 101 < spawnPoints[spawnpointIndex]->enemyTypes[type]) {
						enemyType = type;
						if (spawnPoints[spawnpointIndex]->enemyTypes[type]!=100) break;
					}
				}
				sf::Vector2f pos = spawnPoints[spawnpointIndex]->position;
				pos.x += rand() % spawnPoints[spawnpointIndex]->size + spawnPoints[spawnpointIndex]->size / 2;
				SpawnEnemy(pos, enemyType);
			}
			ResetClock();
		}
	}
}


void EnemySpawner::SpawnEnemy() {
	sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
	Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, 1, this->gameManager);
	enemy->SetPosition(sf::Vector2f(128, 0));
	enemy->SetDirection(sf::Vector2f(0, 1));
	enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
	rectangleEnemy->setSize(sf::Vector2f(64, 64));
	foeList->push_back(enemy);
}

void EnemySpawner::SpawnBoss(sf::Vector2f pos) {
	sf::RectangleShape* rectangleBoss = new sf::RectangleShape(sf::Vector2f(200, 200));
	Entities::Boss1* bossFoe = new Entities::Boss1(*rectangleBoss, 0, 200, this->gameManager);
	bossFoe->SetPosition(pos);
	Entities::Foe* enemy = bossFoe;
	enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
	enemy->health* (1 + gameManager->GetWaveManager()->wave / 5);
	foeList->push_back(enemy);
}

void EnemySpawner::SpawnEnemy(int i) {
	sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
	Entities::LinearFoe* enemy = new Entities::LinearFoe(*rectangleEnemy, i+1, this->gameManager);
	enemy->SetPosition(sf::Vector2f(64+64*i, 0));
	enemy->SetDirection(sf::Vector2f(0, 1));
	enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
	rectangleEnemy->setSize(sf::Vector2f(64, 64));
	foeList->push_back(enemy);
}

void EnemySpawner::SpawnEnemy(sf::Vector2f position, EnemyType enemySpawnedType) {
	Entities::Foe* enemy = nullptr;
	switch (enemySpawnedType)
	{
	case LinearShootingFoe: {
		sf::RectangleShape* rectangleEnemy = new sf::RectangleShape();
		Entities::LinearFoe* linearshootFoe = new Entities::LinearShootingFoe(*rectangleEnemy, 50 + rand() % 100, this->gameManager);
		linearshootFoe->SetPosition(sf::Vector2f(position.x, position.y));
		linearshootFoe->SetDirection(sf::Vector2f(0, 1));
		rectangleEnemy->setSize(sf::Vector2f(64, 64));
		enemy = linearshootFoe;
		break;
	}
	case LinearFoe: {
		sf::CircleShape* triangleShape = new sf::CircleShape(48,3);
		Entities::LinearFoe* linearFoe = new Entities::LinearFoe(*triangleShape, 50 + rand() % 100, this->gameManager);
		linearFoe->SetPosition(sf::Vector2f(position.x, position.y));
		linearFoe->SetDirection(sf::Vector2f(0, 1));
		triangleShape->setRadius(48);
		//triangleShape->setRotation(triangleShape->getRotation() + 180);
		enemy = linearFoe;
		break;
	}
	case NonLinearFoe: {
		sf::CircleShape* octogonalShape = new sf::CircleShape(48,8);
		Entities::NonLinearFoe* nonlinearFoe = new Entities::NonLinearFoe(*octogonalShape, 50 + rand() % 100, this->gameManager);
		nonlinearFoe->SetPosition(sf::Vector2f(position.x, position.y));
		nonlinearFoe->SetDirection(sf::Vector2f(rand() % 2 == 0 ? -1 : 1, 1));
		octogonalShape->setRadius(48);
		enemy = nonlinearFoe;
		break;
	}
	default:
		break;
	}
	if (enemy != nullptr) {
		enemy->SetColor(sf::Color::Transparent, sf::Color::Red);
		enemy->health* healthMultiplier;
		enemy->speed* speedMultiplier;
		foeList->push_back(enemy);
	}


}

