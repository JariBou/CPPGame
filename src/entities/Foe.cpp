#include "Foe.h"
#include "Player.h"
#include "../particles/ParticleSystem.h"
#include "../GameManager.h"
#include "../Utils.h"

namespace Entities {

	Foe::Foe(sf::Shape& shape, float speed, GameManager* pGameManager) : DrawableEntity(shape), gameManager(pGameManager) {
		this->speed = speed;
		this->player = gameManager->GetPlayer();
		this->windowDimension = gameManager->GetWindowDimension();
	}
	
	
	bool Foe::isDead() {
		return this->health <= 0;
	}

	void Foe::OnDestroyed()
	{
		this->gameManager->GetParticleSystem()->CreateExplosionAt(Utils::GetShapeCenter(this->shape), this->shape.getOutlineColor(), 7.0, 20, this->shape.getLocalBounds().width/2, 15);
		// TODO
	}

	void Foe::GetHit(float value) {
		this->health -= value;
	}

	bool Foe::CheckLife() {
		if (health <= 0) {
			return false;
		}
		return !(IsCollidingWithPlayer() || IsOutOfBounds());
	}

	bool Foe::IsCollidingWithPlayer() {
		auto selfRect = this->shape.getGlobalBounds();
		auto playerRect = player->shape.getGlobalBounds();

		bool shouldDestroy = selfRect.intersects(playerRect);
		return shouldDestroy;
	}

	bool Foe::IsOutOfBounds() {
		if (shape.getPosition().y > this->windowDimension.y + shape.getGlobalBounds().height) {
			return true;
		}
		return false;
	}

}