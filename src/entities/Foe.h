#pragma once

#include "DrawableEntity.h"

class GameManager;

namespace Entities {

	class Player;

	class Foe : public DrawableEntity {

	public:

		float health = 20;
		float speed = 5;
		Player* player;
		GameManager* gameManager;

		Foe(sf::Shape& shape, float speed, GameManager* pGameManager);

		//virtual void Update(float deltaTime);

		/// <summary>
		/// Returns true if entity was killed by "normal" means. Usually by the player firing (player collision does not count as "normal".
		/// </summary>
		/// <returns></returns>
		virtual bool isDead();

		/// <summary>
		/// Returns False if the entity should be removed
		/// </summary>
		/// <returns></returns>
		virtual bool CheckLife();
		virtual void OnKilledByPlayer() = 0;
		
		/// <summary>
		/// Called whenever the entity is Destroyed by any means
		/// </summary>
		virtual void OnDestroyed();
		virtual void GetHit(float value);
		virtual bool IsCollidingWithPlayer();
		virtual bool IsOutOfBounds();
	};

}
