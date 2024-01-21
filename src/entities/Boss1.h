#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Foe.h"

namespace Entities
{
	class Player;

	class Boss1 : public Foe {

	public:

		sf::Vector2f direction;
		float clock = 0;
		float changeDirectionCooldown = 2;

		Boss1(sf::Shape& shape, float speed, float health, GameManager* gameManager);

		virtual void Update(float deltaTime);
		virtual bool isDead();

		/// <summary>
		/// Function called when destroyed by PLAYER by "normal" means (i.e bullets)
		/// </summary>
		virtual void OnKilledByPlayer();

		bool IsOutOfBounds();

	private:
		float shootingClock = 0;
		float BigShotClock = 0;
		float shootingCooldown = .5;
		float BigShotCooldown = 5;

	};
}