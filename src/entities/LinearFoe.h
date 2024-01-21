#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Foe.h"


namespace Entities
{
	class Player;

	class LinearFoe : public Foe {

	public:
		
		sf::Vector2f direction;

		LinearFoe(sf::Shape& shape, float speed, GameManager* gameManager);

		virtual void Update(float deltaTime);
		virtual void SetDirection(sf::Vector2f direction);

		/// <summary>
		/// Function called when destroyed by PLAYER by "normal" means (i.e bullets)
		/// </summary>
		virtual void OnKilledByPlayer();

	private:
		float thrustTimer = 0;

	};
}