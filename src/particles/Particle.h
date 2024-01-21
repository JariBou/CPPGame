#pragma once

#include <SFML/Graphics.hpp>
#include "../entities/DrawableEntity.h"

namespace SFX {

	class Particle : public Entities::DrawableEntity{

	public:
		Particle(sf::Shape& shape, float maxLifetime, sf::Vector2f direction);

		Particle(sf::Shape& shape, float maxLifetime, sf::Vector2f direction, float speed);
		/// <summary>
		/// Returns lifetime / maxLifetime of the particle (clamped to [0, 1])
		/// </summary>
		/// <returns></returns>
		float GetLifePercentage();
		bool CheckLife();
		virtual void Update(float deltaTime);

		void UpdateAlpha(float alpha);

	private:
		sf::Vector2f direction;
		float lifetime = 0;
		float maxLifetime;
		float speed = 1;
		sf::Color currColor;

	};

}
