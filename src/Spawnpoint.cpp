#pragma once

#include "Spawnpoint.h"

Spawnpoint::Spawnpoint(sf::Vector2f pos, int size) {
	this->position = pos;
	this->size = size;
}

std::map<EnemyType, int>* Spawnpoint::GetEnemyTypes() {
	return &enemyTypes;
}

void Spawnpoint::AddEnemyToSpawn(EnemyType enemyType, float percentageChance) {
	enemyTypes[enemyType] = percentageChance;
	possibleEnemiesTypes.push_back(enemyType);
}


