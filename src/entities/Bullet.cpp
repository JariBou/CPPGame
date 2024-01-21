#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Player.h"
#include "Foe.h"
#include "../EnemySpawner.h"
#include "../GameManager.h"
#include "../particles/ParticleSystem.h"
#include <iostream>

namespace Entities {

	/*Bullet::Bullet(sf::Shape& shape, Player& player) : DrawableEntity(shape), player(player) {
		speed = 300.0f;
		damage = 10;
		//std::cout << "Bullet created" << std::endl;
		std::cout << shape.getPosition().y << std::endl;
	}*/

	Bullet::Bullet(sf::Shape& shape, GameManager* pGameManager, int damage, float speed, sf::Vector2f Direction, int WindowWidth) : DrawableEntity(shape), gameManager(pGameManager){
		this->damage = damage;
		this->speed = speed;
		//std::cout << "Bullet created" << std::endl;
		//std::cout << shape.getPosition().y << std::endl;
		direction = Direction;
		player = gameManager->GetPlayer();
		windowWidth = WindowWidth;
	}

	bool Bullet::MoveBullet(float deltaTime) {
		Move(sf::Vector2f(direction) * speed, deltaTime);
		return true;
	}

	void Bullet::Update(float deltaTime) {
		MoveBullet(deltaTime);
		CheckHit();
	}	

	bool Bullet::CheckLife() {
		if (this->shouldDestroy) return false;

		sf::Vector2f windowDimension = gameManager->GetWindowDimension();

		if (shape.getPosition().x < 0 - shape.getLocalBounds().width || shape.getPosition().y < 0 - shape.getLocalBounds().height 
			|| shape.getPosition().x > windowDimension.x + shape.getLocalBounds().width || shape.getPosition().y > windowDimension.y + shape.getLocalBounds().height){
			return false;
		}
		return true;
	}

	bool Bullet::CheckHit() {

		auto selfRect = this->shape.getGlobalBounds();

		if (shotByPlayer) {
			EnemySpawner* spawner = gameManager->GetEnemySpawner();

			for (Foe* foe : *(spawner->GetFoes())) {

				auto enemyRect = foe->shape.getGlobalBounds();

				if (enemyRect.intersects(selfRect)) {
					foe->GetHit(this->damage);
					this->gameManager->GetParticleSystem()->CreateExplosionAt(shape.getPosition(), foe->shape.getOutlineColor(), 5., 12);
					shouldDestroy = true;
					return true;
				}

			}
		}
		else {
			if (player->shape.getGlobalBounds().intersects(selfRect)) {
				player->GetHit(this->damage);
				this->gameManager->GetParticleSystem()->CreateExplosionAt(shape.getPosition(), player->shape.getOutlineColor(), 5., 12);
				shouldDestroy = true;
				return true;
			}
		}
		
		return false;
	}


}