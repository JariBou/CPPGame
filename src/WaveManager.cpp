#include "WaveManager.h"
#include <iostream>
#include <math.h>
#include "utils.h"
#include "Spawnpoint.h"
#include "EnemySpawner.h"
#include "GameManager.h"

WaveManager::WaveManager(EnemySpawner* spawner, sf::Text* anouncingWaveText, GameManager* pGameManager) : gameManager(pGameManager)
{
	enemySpawner = spawner;
	anouncingText = anouncingWaveText;
	gameManager->SetWaveManager(this);
}

void WaveManager::SetWave(int wave, float waveCooldown)
{
	this->wave = wave;
	this->waveCooldown = waveCooldown;
	std::vector<Spawnpoint*> spawnPoints;
	enemySpawner->StopClock();
	enemySpawner->bossWave = false;
	anouncingText->setString("Wave " + Utils::toString(wave));
	anouncingText->setScale(sf::Vector2f(0,0));
	anouncing = true;
	switch (wave)
	{
	case 0:
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));
		break;
	case 1:
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));
		for (size_t i = 0; i < spawnPoints.size(); i++)
		{
			spawnPoints[i]->AddEnemyToSpawn(NonLinearFoe, 20);
		}
		break;
	case 2:
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));
		for (size_t i = 0; i < spawnPoints.size(); i++)
		{
			spawnPoints[i]->AddEnemyToSpawn(NonLinearFoe, 30);
			spawnPoints[i]->AddEnemyToSpawn(LinearShootingFoe, 20);
		}
		break;
	case 3:
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));
		for (size_t i = 0; i < spawnPoints.size(); i++)
		{
			spawnPoints[i]->AddEnemyToSpawn(LinearShootingFoe, 60);
			spawnPoints[i]->AddEnemyToSpawn(NonLinearFoe, 40);
		}
		break;
	case 4:
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));
		for (size_t i = 0; i < spawnPoints.size(); i++)
		{
			spawnPoints[i]->AddEnemyToSpawn(LinearShootingFoe, 100);
			spawnPoints[i]->AddEnemyToSpawn(NonLinearFoe, 40);
		}
		break;
	default:
		if (wave % 5 == 0) {
			enemySpawner->bossWave = true;
			break;
		}
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1500, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(1000, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(700, 0), 20));
		spawnPoints.push_back(new Spawnpoint(sf::Vector2f(300, 0), 20));

		for (size_t i = 0; i < spawnPoints.size(); i++)
		{
			spawnPoints[i]->AddEnemyToSpawn(LinearShootingFoe, 70 + rand() % 30);
			spawnPoints[i]->AddEnemyToSpawn(NonLinearFoe, 30 + rand() % 40);
		}
		break;
	}
	enemySpawner->healthMultiplier = 0.5 * exp((1 / 9.5) * wave) + 0.5;
	enemySpawner->speedMultiplier = (1 / 24) * wave + 1;
	enemySpawner->maxEnemyEachSpawn = 1 + ((spawnPoints.size() - 1 < wave / 4) ? spawnPoints.size() - 1 : wave / 4);
	enemySpawner->setSpawnPoints(spawnPoints);
}

void WaveManager::Update(float deltaTime)
{
	clock += deltaTime;
	if (anouncing) {
		sf::Vector2f scale = anouncingText->getScale();
		scale.x += 0.4f * deltaTime;
		scale.y += 0.4f * deltaTime;
		anouncingText->setScale(scale);
		if (scale.x >= 1) {
			enemySpawner->StartClock();
			anouncing = false;
			clock = 0;
		}
	}
	else if (clock >= waveCooldown || enemySpawner->bossWave) {
		if (!enemySpawner->bossWave) this->SetWave(wave + 1, waveCooldown);
		else if (bossKilled) {
			bossKilled = false;
			this->SetWave(wave + 1, waveCooldown);
		}
	}
}
