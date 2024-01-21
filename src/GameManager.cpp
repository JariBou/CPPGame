#include "GameManager.h"
#include "Particles/ParticleSystem.h"

GameManager::GameManager(sf::RenderWindow& window, int& score) : score(score)
{
	windowDimension = sf::Vector2f(window.getSize().x,window.getSize().y);
}

void GameManager::Reset()
{
	bulletList.clear();
	particleSystem->Reset();
}

void GameManager::AddBullet(Entities::Bullet* bullet)
{
	bulletList.push_back(bullet);
}
