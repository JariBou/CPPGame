#include "LinearFoe.h"
#include "../UpgradeBoxSpawner.h"
#include "Player.h"
#include "../GameManager.h"
#include "../particles/ParticleSystem.h"
#include "../utils.h"


namespace Entities
{
	LinearFoe::LinearFoe(sf::Shape& shape, float speed, GameManager* pGameManager) : Foe(shape, speed, pGameManager) {
	}

	void LinearFoe::Update(float deltaTime) {
		this->Move(direction * speed, deltaTime);
		thrustTimer += deltaTime;
		sf::Vector2f pos = shape.getPosition();
		if (pos.y > this->windowDimension.y + shape.getGlobalBounds().height) {
			/*player->GetHit(1);*/
		}
		if (IsCollidingWithPlayer()) {
			player->GetHit(1);
		}
		if (thrustTimer >= 0.05) {
			int randGen = rand() % 5 + 3;
			gameManager->GetParticleSystem()->CreateDirectedExplosionAt(sf::Vector2f(Utils::GetShapeXCenter(this->shape), Utils::GetShapeYCenter(this->shape) - this->shape.getLocalBounds().height / 2),
				sf::Color::Yellow, 80, 275, 2.2, randGen, 3, 60);
			thrustTimer = 0;
		}
	}

	void LinearFoe::SetDirection(sf::Vector2f direction) {
		this->direction = direction;
	}

	void LinearFoe::OnKilledByPlayer() {
		this->gameManager->GetUpgradeBoxSpawner()->SpawnUpgradeBox(&shape);
		this->gameManager->score++;
	}
}