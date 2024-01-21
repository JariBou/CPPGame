#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "LinearFoe.h"


namespace Entities
{
	class Bullet;
	class Player;

	class LinearShootingFoe : public LinearFoe {

	private:
		float shootingClock = 0;
		float shootingCooldown = 1.5;
		std::vector<Bullet*> bullets;

	public:

		LinearShootingFoe(sf::Shape& shape, float speed, GameManager* pGameManager);

		virtual void Update(float deltaTime);
		virtual void Draw(sf::RenderWindow& window);

	};
}