#pragma once

#include <SFML/Graphics.hpp>
#include "enum.h"

class Spawnpoint
{
public:
	sf::Vector2f position;
	int size;
	std::map<EnemyType, int> enemyTypes;
	std::vector<EnemyType> possibleEnemiesTypes;
	
	Spawnpoint(sf::Vector2f position, int size);

	std::map<EnemyType, int>* GetEnemyTypes();

	void AddEnemyToSpawn(EnemyType enemyType, float percentageChance);

};
