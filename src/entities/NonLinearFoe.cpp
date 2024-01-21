#include "NonLinearFoe.h"
#include "../UpgradeBoxSpawner.h"
#include "Player.h"
#include "../GameManager.h"
#include "../particles/ParticleSystem.h"
#include "../utils.h"

namespace Entities
{
	NonLinearFoe::NonLinearFoe(sf::Shape& shape, float speed, GameManager* pGameManager) : Foe(shape, speed, pGameManager) {
	}

	void NonLinearFoe::Update(float deltaTime) {
		this->Move(direction * speed, deltaTime);
		sf::Vector2f pos = shape.getPosition();
		if (pos.y > this->windowDimension.x + shape.getGlobalBounds().height) {
			/*player->GetHit(1);*/
		}
		if (IsCollidingWithPlayer()) {
			player->GetHit(1);
		}
		clock += deltaTime;
		if (clock >= changeDirectionCooldown || pos.x < 0 || pos.x>windowDimension.x) {
			direction.x *= -1;
			clock = 0;
		}
		thrustTimer += deltaTime;
		if (thrustTimer >= 0.05) {
			int randGen = rand() % 5 + 3;
			gameManager->GetParticleSystem()->CreateDirectedExplosionAt(sf::Vector2f(Utils::GetShapeXCenter(this->shape), Utils::GetShapeYCenter(this->shape) - this->shape.getLocalBounds().height / 2),
				sf::Color::Yellow, 80, 275, 2.2, randGen, 3, 60);
			thrustTimer = 0;
		}
	}

	bool NonLinearFoe::isDead() {
		return this->health <= 0;

	}

	void NonLinearFoe::SetDirection(sf::Vector2f direction) {
		this->direction = direction;
	}

	void NonLinearFoe::OnKilledByPlayer() {
		this->gameManager->GetUpgradeBoxSpawner()->SpawnUpgradeBox(&shape);
		this->gameManager->score++;
	}

	//TODO
	bool NonLinearFoe::IsOutOfBounds() {
		if (shape.getPosition().y > this->windowDimension.y + shape.getGlobalBounds().height) {
			return true;
		}
		return false;
	}
}