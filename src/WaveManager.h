#pragma once

#include <SFML/Graphics.hpp>


class EnemySpawner;
class GameManager;

class WaveManager
{

public:
	EnemySpawner* enemySpawner;
	float clock = 0;
	float waveCooldown = 3;
	int wave = 0;
	bool anouncing = false;
	bool bossKilled = false;
	sf::Text* anouncingText;
	WaveManager(EnemySpawner* spawner, sf::Text* anouncingWaveText, GameManager* pGameManager);

	void SetWave(int wave, float waveCooldown);

	void Update(float deltaTime);

private:
	GameManager* gameManager;

};